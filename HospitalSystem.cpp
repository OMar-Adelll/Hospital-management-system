#include "HospitalSystem.h"

// ================= CONSTRUCTOR & DESTRUCTOR =================

HospitalSystem::HospitalSystem()
{
    // Initialize the specialized lists for each department
    // This prevents "Segmentation Faults" when accessing specific majors
    doctorsByMajor[GENERAL] = new DoctorList();
    doctorsByMajor[EMERGENCY] = new DoctorList();
    doctorsByMajor[ICU] = new DoctorList();
    doctorsByMajor[PEDIATRIC] = new DoctorList();
    doctorsByMajor[SURGICAL] = new DoctorList();
}

HospitalSystem::~HospitalSystem()
{
    cout << "System shutting down... Cleaning up memory." << endl;
    // Iterate through the map and delete every DoctorList to prevent memory leaks
    for (auto const &[key, listPtr] : doctorsByMajor)
    {
        delete listPtr;
    }
}

// ================= PATIENT MANAGEMENT =================

void HospitalSystem::addPatient()
{
    cout << "\n=== REGISTER NEW PATIENT ===" << endl;
    
    cout << "Enter ID: ";
    int id = safe_input_int(1, 999999);
    
    cout << "Enter Name: ";
    string name;
    cin.ignore();
    getline(cin, name);
    
    cout << "Enter Age: ";
    int age = safe_input_int(0, 120);

    cout << "Select Case Type:\n0:General, 1:Emergency, 2:ICU, 3:Pediatric, 4:Surgical\nChoice: ";
    int type = safe_input_int(0, 4);

    // Create patient and add to Global Waiting Room
    Patient p(id, name, age, (CaseType)type);
    patientQueue.enqueue(p);
    
    cout << "Success: Patient " << name << " added to Waiting Room." << endl;
}

void HospitalSystem::deletePatient()
{
    if (patientQueue.isEmpty()) {
        cout << "Waiting room is empty." << endl;
        return;
    }

    cout << "Enter Patient ID to remove from Waiting Room: ";
    int id = safe_input_int(1, 999999);
    
    // Note: This relies on the removeById(id) function in PatientQueue.h
    Patient p = patientQueue.removeById(id);
    
    if (p.getId() != 0) {
        cout << "Patient " << p.getName() << " removed successfully." << endl;
    }
}

void HospitalSystem::showWaitingRoom()
{
    cout << "\n=== WAITING ROOM STATUS ===" << endl;
    patientQueue.display();
}

// ================= DOCTOR MANAGEMENT =================

void HospitalSystem::addDoctor()
{
    cout << "\n=== HIRE NEW DOCTOR ===" << endl;

    cout << "Enter ID: ";
    int id = safe_input_int(1, 999999);

    cout << "Enter Name: ";
    string name;
    cin.ignore();
    getline(cin, name);

    cout << "Enter Age: ";
    int age = safe_input_int(22, 100);

    cout << "Select Specialization:\n0:General, 1:Emergency, 2:ICU, 3:Pediatric, 4:Surgical\nChoice: ";
    int type = safe_input_int(0, 4);
    CaseType major = (CaseType)type;

    Doctor d(id, name, age, major);
    
    // Add to the correct department list
    doctorsByMajor[major]->addDoctor(d);
    cout << "Doctor " << name << " assigned to " << type << " department." << endl;
}

void HospitalSystem::showDoctors()
{
    cout << "Select Department to View:\n0:General, 1:Emergency, 2:ICU, 3:Pediatric, 4:Surgical\nChoice: ";
    int type = safe_input_int(0, 4);
    
    cout << "\n--- DOCTOR LIST (" << type << ") ---" << endl;
    doctorsByMajor[(CaseType)type]->display();
}

// ================= CORE WORKFLOW (TRIAGE & TREATMENT) =================

void HospitalSystem::assignPatient()
{
    if (patientQueue.isEmpty()) {
        cout << "No patients in the waiting room." << endl;
        return;
    }

    // 1. Peek at the next patient to see what they need
    Patient nextP = patientQueue.next();
    CaseType neededMajor = nextP.getCaseType();

    cout << "\n=== ASSIGN PATIENT TO DOCTOR ===" << endl;
    cout << "Patient: " << nextP.getName() << " (Needs Dept: " << neededMajor << ")" << endl;

    DoctorList* deptList = doctorsByMajor[neededMajor];

    if (deptList->isEmpty()) {
        cout << "CRITICAL: No doctors available in this department!" << endl;
        return;
    }

    // 2. Show compatible doctors
    cout << "Available Doctors in this Department:" << endl;
    deptList->display();

    cout << "Enter Doctor ID to assign: ";
    int docId = safe_input_int(1, 999999);

    // 3. Find the specific queue for that doctor
    PatientQueue* docQueue = deptList->SearchById(docId);

    if (docQueue != nullptr) {
        // Move the patient: Dequeue from Waiting Room -> Enqueue to Doctor
        Patient p = patientQueue.dequeue();
        docQueue->enqueue(p);
        cout << "Success: Patient transferred to Dr. ID " << docId << endl;
    } else {
        cout << "Error: Invalid Doctor ID." << endl;
    }
}

void HospitalSystem::treatPatient()
{
    cout << "\n=== DOCTOR TREATMENT PORTAL ===" << endl;
    
    cout << "Select Department:\n0:General, 1:Emergency, 2:ICU, 3:Pediatric, 4:Surgical\nChoice: ";
    int type = safe_input_int(0, 4);

    DoctorList* list = doctorsByMajor[(CaseType)type];

    if (list->isEmpty()) {
        cout << "No doctors in this department." << endl;
        return;
    }

    list->display();

    cout << "Enter Doctor ID performing the treatment: ";
    int docId = safe_input_int(1, 999999);

    // Note: This relies on the treatPatient(id) function in DoctorList.h
    list->treatPatient(docId);
}

// ================= MAIN MENU LOOP =================

void HospitalSystem::printMainMenu()
{
    cout << "\n==========================================" << endl;
    cout << "           HOSPITAL MANAGEMENT SYSTEM     " << endl;
    cout << "==========================================" << endl;
    cout << " 1. Register Patient (Add to Waiting Room)" << endl;
    cout << " 2. Hire Doctor" << endl;
    cout << " 3. ASSIGN Patient (Waiting Room -> Doctor)" << endl;
    cout << " 4. TREAT Patient (Discharge)" << endl;
    cout << " 5. View Waiting Room" << endl;
    cout << " 6. View Doctors by Department" << endl;
    cout << " 7. Delete Patient (From Waiting Room)" << endl;
    cout << " 0. Exit" << endl;
    cout << "==========================================" << endl;
    cout << " Select Option: ";
}

void HospitalSystem::run()
{
    int choice;
    while (true)
    {
        printMainMenu();
        choice = safe_input_int(0, 7);

        switch (choice)
        {
        case 1: addPatient(); break;
        case 2: addDoctor(); break;
        case 3: assignPatient(); break;
        case 4: treatPatient(); break;
        case 5: showWaitingRoom(); break;
        case 6: showDoctors(); break;
        case 7: deletePatient(); break;
        case 0: return;
        default: cout << "Invalid option." << endl;
        }
    }
}
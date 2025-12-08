#include <iostream>
#include <queue>
#include <string>
#include "Patient.h"
#include "PatientQueue.h"
#include "Doctor.h"
#include "DoctorList.h"

using namespace std;
class HospitalSystem
{
private:
    map<CaseType, DoctorList *> doctorsByMajor;
    PatientQueue patientQueue;

public:
    HospitalSystem() {}

    // ========= DOCTOR FUNCTIONS ============
    void addDoctor();
    void deleteDoctor();
    void EditDoctor();
    void getDoctorInfo();

    // ========= PATIENT FUNCTIONS =========== ->>>DONE
    void Addpatient(const Patient &p)
    {
        patientQueue.enqueue(p);
        cout << "Patient added: " << p.getName() << endl;
    };
    void deletePatient(int id)
    {
        Patient removedPatient = patientQueue.dequeue();
        if (removedPatient.getId() != 0)
        {
            cout << "Patient removed: " << removedPatient.getName() << endl;
        }
        else
        {
            cout << "No patient to remove." << endl;
        }
    };
    void SearchById(int id)
    {
        Patient p = patientQueue.searchPatient(id);
        if (p.getId() != 0)
        {
            cout << "Patient found: " << p.getName() << endl;
            p.display();
        }
        else
        {
            cout << "Patient not found." << endl;
        }
    };
    void SearchByPatient(const Patient &p)
    {
        Patient foundPatient = patientQueue.searchPatient(p);
        if (foundPatient.getName() != "")
        {
            cout << "Patient found: " << foundPatient.getName() << endl;
            foundPatient.display();
        }
        else
        {
            cout << "Patient not found." << endl;
        }
    };
    void patientsCount()
    {
        cout << "Total patients in queue: " << patientQueue.getQueueCount() << endl;
    };
    void displayPatients()
    {
        patientQueue.display();
    };
    void showNext()
    {
        if (!patientQueue.isEmpty())
        {
            Patient p = patientQueue.next();
            cout << "Next patient: " << p.getName()
                 << ", Age: " << p.getAge() << endl;
            p.display();
        }
        else
        {
            cout << "No patients in queue." << endl;
        }
    };

    // ========= MENUS =======================
    void doctorMenu();
    void patientMenu();
    void Menus();
    void Welcome();
    void exitSystem();
};

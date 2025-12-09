#ifndef HOSPITALSYSTEM_H
#define HOSPITALSYSTEM_H

#include <iostream>
#include <map>
#include <string>
#include "Patient.h"
#include "PatientQueue.h"
#include "Doctor.h"
#include "DoctorList.h"
#include "SafeInput.h" // Ensure this file is in your directory

using namespace std;

class HospitalSystem
{
private:
    // 1. Database of Doctors organized by Department
    map<CaseType, DoctorList *> doctorsByMajor;

    // 2. The "Waiting Room" (Global Queue for new arrivals)
    PatientQueue patientQueue;

public:
    // Constructor & Destructor
    HospitalSystem();
    ~HospitalSystem();

    // Main Application Loop
    void run(); 

    // --- Patient Management ---
    void addPatient();       // Register new patient to Waiting Room
    void deletePatient();    // Remove patient from Waiting Room (by ID)
    void showWaitingRoom();  // View all unassigned patients

    // --- Doctor Management ---
    void addDoctor();        // Hire new doctor
    void showDoctors();      // View doctors in a specific department

    // --- The Core Workflow ---
    void assignPatient();    // Move Patient: Waiting Room -> Doctor's Queue
    void treatPatient();     // Doctor treats patient (Removes from system)
    
    // --- Helper ---
    void printMainMenu();
};

#endif
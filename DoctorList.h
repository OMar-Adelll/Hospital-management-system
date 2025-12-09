#ifndef DOCTORLIST_H
#define DOCTORLIST_H

#include <bits/stdc++.h>
#include "PatientQueue.h"
using namespace std;

class ListNode
{
public:
    Doctor doctor;         // Doctor object
    PatientQueue Patients; // Queue of patients for this doctor
    ListNode *next;        // pointer to next node

    ListNode(const Doctor &d) : doctor(d), next(nullptr) {}
};

class DoctorList
{
private:
    ListNode *head;
    ListNode *tail;
    int DoctorsCount; // number of doctors

public:
    DoctorList() : head(nullptr), tail(nullptr), DoctorsCount(0) {}
    ~DoctorList()
    {
        clear();
    }

    void addDoctor(const Doctor &doctor)
    {
        ListNode *newNode = new ListNode(doctor);
        if (head == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        DoctorsCount++;
    }

    PatientQueue *SearchById(int DoctorId)
    {
        ListNode *Start = head;

        while (Start != nullptr)
        {
            if (Start->doctor.getId() == DoctorId)
            {
                return &Start->Patients; // return POINTER to the queue
            }
            Start = Start->next;
        }

        cout << "Doctor Id not found!\n";
        return nullptr;
    }

    Doctor dequeue() // This function deletes a doctor.
    {
        if (isEmpty())
        {
            cout << "There is no Doctor " << nl;
            return Doctor();
        }
        else
        {
            if (head == tail)
            {
                Doctor temp = head->doctor;
                delete head;
                head = tail = nullptr;
                DoctorsCount--;
                return temp;
            }
            else
            {
                Doctor temp1 = head->doctor;
                ListNode *temp = head;
                head = head->next;
                delete temp;
                DoctorsCount--;
                return temp1;
            }
        }
    }
    void display() // This function display doctors queue
    {
        if (isEmpty())
        {
            cout << "There is no Doctor " << nl;
            return;
        }
        else
        {
            ListNode *curr = head;
            while (curr != nullptr)
            {
                cout << "Doctor ID" << curr->doctor.getId() << endl;
                cout << "Doctor Name" << curr->doctor.getName() << endl;
                cout << "==================================" << endl;
                curr = curr->next;
            }
        }
    }

    bool isEmpty() const
    {
        return head == nullptr;
    }

    int count() const
    {
        return DoctorsCount;
    }

    bool treatPatient(int doctorId)
    {
        ListNode *curr = head;
        while (curr != nullptr)
        {
            if (curr->doctor.getId() == doctorId)
            {
                if (curr->Patients.isEmpty())
                {
                    cout << "Dr. " << curr->doctor.getName() << " has no patients waiting!" << endl;
                    return false;
                }

                // 1. Remove patient from this doctor's specific queue
                Patient p = curr->Patients.dequeue();

                // 2. (Optional) Increment a 'patientsTreated' counter in the Doctor object
                // curr->doctor.incrementTreatedCount();

                cout << "Dr. " << curr->doctor.getName() << " has successfully treated patient: "
                     << p.getName() << nl;
                return true;
            }
            curr = curr->next;
        }
        cout << "Doctor ID not found!" << nl;
        return false;
    }

    void clear()
    {
        while (head != nullptr)
        {
            ListNode *temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        DoctorsCount = 0;
    }
};

#endif
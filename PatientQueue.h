// بسم الله الرحمن الرحيم
// "وَأَنْ لَيْسَ لِلْإِنسَانِ إِلَّا مَا سَعَىٰ"
// Free Palestine

#ifndef PATIENTQUEUE_H
#define PATIENTQUEUE_H
#include <bits/stdc++.h>
#include "Patient.h"
using namespace std;

#define nl '\n'
// QueueNode class
class QueueNode
{
public:
    Patient patient;
    QueueNode *next;
    // Constructors
    QueueNode() {}
    QueueNode(Patient &p) : patient(p), next(nullptr) {}
};

// PatientQueue class
class PatientQueue
{
private:
    QueueNode *head;
    QueueNode *tail;
    int patientCount;

public:
    // Default constructor
    PatientQueue() : head(nullptr), tail(nullptr), patientCount(0) {};
    ~PatientQueue() { clear(); }

    // Cheack if the queue is empty or not.
    bool isEmpty()
    {
        return (head == nullptr);
    }
    int getQueueCount()
    {
        return patientCount;
    }

    QueueNode *getHead()
    {
        return head;
    }
    void MoveHead()
    {
        head = head->next ;
    }
    void SetTailToNull()
    {
        tail = nullptr ;
    }

    // Enqueue to add patient(-MoRa-)
    void enqueue(Patient patient)
    {
        QueueNode *newPatient = new QueueNode(patient);
        if (isEmpty())
        {
            head = tail = newPatient;
        }
        else
        {
            tail->next = newPatient;
            tail = newPatient;
        }
        patientCount++;
    }

    // Dequeue to delete patient(-MoRa-)
    Patient dequeue()
    {
        if (isEmpty())
        {
            cout << "There are no patients available." << nl;
            return Patient();
        }

        patientCount--;
        if (head == tail)
        {
            Patient tempVal = head->patient;
            delete head;
            head = tail = nullptr;
            return tempVal;
        }

        Patient tempVal = head->patient;
        QueueNode *temp = head;
        head = head->next;
        delete temp;
        return tempVal;
    }

    // peek to get current patinet which on the top
    Patient next()
    {
        if (isEmpty())
        {
            cout << "There are no patients available." << nl;
            return Patient();
        }

        return head->patient;
    }

    Patient searchPatient(const Patient &other)
    {
        if (isEmpty())
        {
            cout << "There are no patients available." << nl;
            return Patient();
        }

        int id = other.getId();
        QueueNode *trav = head;

        while (trav != nullptr)
        {
            if (trav->patient.getId() == id)
                return trav->patient;

            trav = trav->next;
        }

        cout << "This patient is not in this queue!" << nl;
        return Patient();
    }

    Patient searchPatient(int id) // overloaded function to search directly by id
    {
        if (isEmpty())
        {
            cout << "There are no patients available." << nl;
            return Patient();
        }

        QueueNode *trav = head;

        while (trav != nullptr)
        {
            if (trav->patient.getId() == id)
                return trav->patient;

            trav = trav->next;
        }

        cout << "This patient is not in this queue!" << nl;
        return Patient();
    }
    bool searchPatientbool(int id) // overloaded function to search directly by id
    {
        if (isEmpty())
        {
            return 0 ;
        }

        QueueNode *trav = head;

        while (trav != nullptr)
        {
            if (trav->patient.getId() == id)
                return 1 ;

            trav = trav->next;
        }

        return 0 ;
    }

    // Add this inside class PatientQueue in PatientQueue.h

    Patient removeById(int id)
    {
        if (isEmpty())
        {
            cout << "Queue is empty. Cannot remove patient." << nl;
            return Patient(); // Return empty patient
        }

        // SCENARIO 1: The patient to remove is at the HEAD
        if (head->patient.getId() == id)
        {
            QueueNode *temp = head;
            Patient removedData = head->patient;

            head = head->next; // Move head forward

            // If the queue becomes empty, update tail to null
            if (head == nullptr)
            {
                tail = nullptr;
            }

            delete temp;
            patientCount--;
            return removedData;
        }

        // SCENARIO 2: The patient is somewhere else (Middle or Tail)
        QueueNode *prev = head;
        QueueNode *curr = head->next;

        while (curr != nullptr)
        {
            if (curr->patient.getId() == id)
            {
                Patient removedData = curr->patient;

                // Link previous node to the next node (skipping current)
                prev->next = curr->next;

                // If we are removing the TAIL, update tail to point to prev
                if (curr == tail)
                {
                    tail = prev;
                }

                delete curr;
                patientCount--;
                return removedData;
            }

            // Move pointers forward
            prev = curr;
            curr = curr->next;
        }

        // SCENARIO 3: Patient ID was not found
        cout << "Patient with ID " << id << " not found in the queue." << nl;
        return Patient();
    }

    // display out patinets queue
    void display()
    {
        if (isEmpty())
            return void(cout << "there are no patinets in the queue." << nl);

        cout << "==================================" << nl;
        cout << "      PATIENT QUEUE SUMMARY       " << nl;
        cout << "==================================" << nl;
        cout << "Total Patients: " << patientCount << nl;
        cout << "----------------------------------" << nl;

        QueueNode *trav = head;
        int index = 1;

        while (trav != nullptr)
        {
            cout << "Patient #" << index << nl;
            trav->patient.display();

            trav = trav->next;
            index++;
        }

        cout << "========== END OF QUEUE ==========" << nl;
    }

    // save memory leak
    void clear()
    {
        while (!isEmpty())
            dequeue();
    }
    PatientQueue(const PatientQueue &) = delete;
    PatientQueue &operator=(const PatientQueue &) = delete;
};

#endif
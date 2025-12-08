// بسم الله الرحمن الرحيم
// "وَأَنْ لَيْسَ لِلْإِنسَانِ إِلَّا مَا سَعَىٰ"
// Free Palestine

#ifndef PERSON_H
#define PERSON_H

#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

// Enum defined here for convenience
enum CaseType
{
    GENERAL,
    EMERGENCY,
    ICU,
    PEDIATRIC,
    SURGICAL
};

class Person
{
protected:
    int id;
    string name;
    int age;
    CaseType caseType;

public:
    // 1. Empty Constructor
    Person()
    {
        id = 0;
        name = "";
        age = 0;
        caseType = GENERAL;
    }

    // 2. Parameterized Constructor
    Person(int pId, string pName, int pAge, CaseType pCaseType)
    {
        id = pId;
        name = pName;
        age = pAge;
        caseType = pCaseType;
    }

    // 3. Copy Constructor
    Person(const Person &other)
    {
        id = other.id;
        name = other.name;
        age = other.age;
        caseType = other.caseType;
    }

    // Virtual Display function
    virtual void display() const
    {
        string caseTypeStr;
        switch (caseType)
        {
        case GENERAL:
            caseTypeStr = "GENERAL";
            break;
        case EMERGENCY:
            caseTypeStr = "EMERGENCY";
            break;
        case ICU:
            caseTypeStr = "ICU";
            break;
        case PEDIATRIC:
            caseTypeStr = "PEDIATRIC";
            break;
        case SURGICAL:
            caseTypeStr = "SURGICAL";
            break;
        default:
            caseTypeStr = "UNKNOWN";
        }

        cout << "ID: " << id << nl;
        cout << "Name: " << name << nl;
        cout << "Age: " << age << nl;
        cout << "Case Type: " << caseTypeStr << nl;
    }

    // --- Getters ---
    int getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    CaseType getCaseType() const { return caseType; }

    // --- Setters ---
    void setName(const string &newName)
    {
        name = newName;
    }

    void setAge(int newAge)
    {
        if (newAge >= 0)
        {
            age = newAge;
        }
        else
        {
            cout << "Error: Age cannot be negative!" << endl;
        }
    }

    void setCaseType(CaseType newCaseType)
    {
        caseType = newCaseType;
    }
};

#endif
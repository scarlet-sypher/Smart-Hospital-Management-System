#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <iostream>
using namespace std;

class Patient {
private:
    int patientId;
    string name;
    int age;
    string condition;
    int bedNumber;
    bool isAdmitted;

public:
    Patient();
    Patient(int id, string name, int age, string condition);
    
    // Getters
    int getPatientId() const;
    string getName() const;
    int getAge() const;
    string getCondition() const;
    int getBedNumber() const;
    bool getIsAdmitted() const;
    
    // Setters
    void setBedNumber(int bedNum);
    void setIsAdmitted(bool admitted);
    
    // Display
    void displayPatient() const;
    
    // File I/O
    string toFileString() const;
    static Patient fromFileString(const string& line);
};

#endif

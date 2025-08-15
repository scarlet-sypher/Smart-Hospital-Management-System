#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
#include <iostream>
using namespace std;

class Doctor {
private:
    int doctorId;
    string name;
    string specialization;
    bool isAvailable;

public:
    Doctor();
    Doctor(int id, string name, string specialization);
    
    // Getters
    int getDoctorId() const;
    string getName() const;
    string getSpecialization() const;
    bool getIsAvailable() const;
    
    // Setters
    void setIsAvailable(bool available);
    
    // Display
    void displayDoctor() const;
    
    // File I/O
    string toFileString() const;
    static Doctor fromFileString(const string& line);
};

#endif
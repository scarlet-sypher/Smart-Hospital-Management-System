#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "Patient.h"
#include "Doctor.h"
#include "Surgery.h"
#include "Ward.h"
#include <vector>
#include <queue>
#include <string>
using namespace std;

class Hospital {
private:
    string hospitalName;
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Ward> wards;
    queue<Patient> waitingQueue;
    priority_queue<Surgery> surgeryQueue;
    
    int nextPatientId;
    int nextDoctorId;
    int nextSurgeryId;

public:
    Hospital(string name);
    
    // Patient operations
    void admitPatient();
    void dischargePatient();
    void displayPatients();
    
    // Doctor operations
    void addDoctor();
    void displayDoctors();
    
    // Surgery operations
    void scheduleSurgery();
    void displaySurgeries();
    
    // Ward operations
    void displayWardStatus();
    void initializeWards();
    
    // Dashboard
    void displayDashboard();
    
    // File operations
    void saveData();
    void loadData();
    
    // Utility
    void displayMenu();
    void printHeader(const string& title);
    void printSeparator();
    Patient* findPatientById(int id);
    Doctor* findDoctorById(int id);
};

#endif
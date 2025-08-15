#ifndef SURGERY_H
#define SURGERY_H

#include <string>
#include <iostream>
using namespace std;

enum class Priority {
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3,
    CRITICAL = 4
};

class Surgery {
private:
    int surgeryId;
    int patientId;
    int doctorId;
    string surgeryType;
    Priority priority;
    string scheduledTime;

public:
    Surgery();
    Surgery(int sId, int pId, int dId, string type, Priority prio, string time);
    
    // Getters
    int getSurgeryId() const;
    int getPatientId() const;
    int getDoctorId() const;
    string getSurgeryType() const;
    Priority getPriority() const;
    string getScheduledTime() const;
    
    // Display
    void displaySurgery() const;
    string getPriorityString() const;
    
    // For priority queue comparison
    bool operator<(const Surgery& other) const;
    
    // File I/O
    string toFileString() const;
    static Surgery fromFileString(const string& line);
};

#endif
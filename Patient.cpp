#include "Patient.h"
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
  // For stoi (optional)

Patient::Patient() : patientId(0), name(""), age(0), condition(""), bedNumber(-1), isAdmitted(false) {}

Patient::Patient(int id, string n, int a, string cond) 
    : patientId(id), name(n), age(a), condition(cond), bedNumber(-1), isAdmitted(false) {}

int Patient::getPatientId() const { return patientId; }
string Patient::getName() const { return name; }
int Patient::getAge() const { return age; }
string Patient::getCondition() const { return condition; }
int Patient::getBedNumber() const { return bedNumber; }
bool Patient::getIsAdmitted() const { return isAdmitted; }

void Patient::setBedNumber(int bedNum) { bedNumber = bedNum; }
void Patient::setIsAdmitted(bool admitted) { isAdmitted = admitted; }

void Patient::displayPatient() const {
    cout << "| " << patientId << " | " << name;
    for(int i = name.length(); i < 15; i++) cout << " ";
    cout << "| " << age;
    for(int i = to_string(age).length(); i < 3; i++) cout << " ";
    cout << "| " << condition;
    for(int i = condition.length(); i < 15; i++) cout << " ";
    cout << "| ";
    if(bedNumber != -1) {
        cout << bedNumber;
        for(int i = to_string(bedNumber).length(); i < 3; i++) cout << " ";
    } else {
        cout << "N/A ";
    }
    cout << "| " << (isAdmitted ? "Yes" : "No") << " |" << endl;
}

string Patient::toFileString() const {
    return to_string(patientId) + "," + name + "," + to_string(age) + "," + 
           condition + "," + to_string(bedNumber) + "," + (isAdmitted ? "1" : "0");
}

Patient Patient::fromFileString(const string& line) {
    stringstream ss(line);
    string item;
    vector<string> tokens;
    
    while(getline(ss, item, ',')) {
        tokens.push_back(item);
    }
    
    if(tokens.size() >= 6) {
        Patient p(stoi(tokens[0]), tokens[1], stoi(tokens[2]), tokens[3]);
        p.setBedNumber(stoi(tokens[4]));
        p.setIsAdmitted(tokens[5] == "1");
        return p;
    }
    return Patient();
}

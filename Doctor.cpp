#include "Doctor.h"
#include <sstream>
#include <vector>

Doctor::Doctor() : doctorId(0), name(""), specialization(""), isAvailable(true) {}

Doctor::Doctor(int id, string n, string spec) 
    : doctorId(id), name(n), specialization(spec), isAvailable(true) {}

int Doctor::getDoctorId() const { return doctorId; }
string Doctor::getName() const { return name; }
string Doctor::getSpecialization() const { return specialization; }
bool Doctor::getIsAvailable() const { return isAvailable; }

void Doctor::setIsAvailable(bool available) { isAvailable = available; }

void Doctor::displayDoctor() const {
    cout << "| " << doctorId << " | " << name;
    for(int i = name.length(); i < 15; i++) cout << " ";
    cout << "| " << specialization;
    for(int i = specialization.length(); i < 15; i++) cout << " ";
    cout << "| " << (isAvailable ? "Available" : "Busy     ") << " |" << endl;
}

string Doctor::toFileString() const {
    return to_string(doctorId) + "," + name + "," + specialization + "," + 
           (isAvailable ? "1" : "0");
}

Doctor Doctor::fromFileString(const string& line) {
    stringstream ss(line);
    string item;
    vector<string> tokens;
    
    while(getline(ss, item, ',')) {
        tokens.push_back(item);
    }
    
    if(tokens.size() >= 4) {
        Doctor d(stoi(tokens[0]), tokens[1], tokens[2]);
        d.setIsAvailable(tokens[3] == "1");
        return d;
    }
    return Doctor();
}

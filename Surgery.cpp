#include "Surgery.h"
#include <sstream>
#include <vector>

Surgery::Surgery() : surgeryId(0), patientId(0), doctorId(0), surgeryType(""), 
                     priority(Priority::LOW), scheduledTime("") {}

Surgery::Surgery(int sId, int pId, int dId, string type, Priority prio, string time)
    : surgeryId(sId), patientId(pId), doctorId(dId), surgeryType(type), 
      priority(prio), scheduledTime(time) {}

int Surgery::getSurgeryId() const { return surgeryId; }
int Surgery::getPatientId() const { return patientId; }
int Surgery::getDoctorId() const { return doctorId; }
string Surgery::getSurgeryType() const { return surgeryType; }
Priority Surgery::getPriority() const { return priority; }
string Surgery::getScheduledTime() const { return scheduledTime; }

string Surgery::getPriorityString() const {
    switch(priority) {
        case Priority::LOW: return "Low";
        case Priority::MEDIUM: return "Medium";
        case Priority::HIGH: return "High";
        case Priority::CRITICAL: return "Critical";
        default: return "Unknown";
    }
}

bool Surgery::operator<(const Surgery& other) const {
    return static_cast<int>(priority) < static_cast<int>(other.priority);
}

void Surgery::displaySurgery() const {
    cout << "| " << surgeryId << " | " << patientId << " | " << doctorId << " | ";
    cout << surgeryType;
    for(int i = surgeryType.length(); i < 12; i++) cout << " ";
    cout << "| " << getPriorityString();
    for(int i = getPriorityString().length(); i < 8; i++) cout << " ";
    cout << "| " << scheduledTime;
    for(int i = scheduledTime.length(); i < 10; i++) cout << " ";
    cout << "|" << endl;
}

string Surgery::toFileString() const {
    return to_string(surgeryId) + "," + to_string(patientId) + "," + 
           to_string(doctorId) + "," + surgeryType + "," + 
           to_string(static_cast<int>(priority)) + "," + scheduledTime;
}

Surgery Surgery::fromFileString(const string& line) {
    stringstream ss(line);
    string item;
    vector<string> tokens;
    
    while(getline(ss, item, ',')) {
        tokens.push_back(item);
    }
    
    if(tokens.size() >= 6) {
        return Surgery(stoi(tokens[0]), stoi(tokens[1]), stoi(tokens[2]), 
                      tokens[3], static_cast<Priority>(stoi(tokens[4])), tokens[5]);
    }
    return Surgery();
}

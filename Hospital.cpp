#include "Hospital.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

Hospital::Hospital(string name) : hospitalName(name), nextPatientId(1), 
                                  nextDoctorId(1), nextSurgeryId(1) {
    initializeWards();
    loadData();
}

void Hospital::initializeWards() {
    wards.push_back(Ward(1, "General Ward", 10));
    wards.push_back(Ward(2, "ICU", 5));
    wards.push_back(Ward(3, "Pediatric", 8));
    wards.push_back(Ward(4, "Surgical", 6));
}

void Hospital::printHeader(const string& title) {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║" << setw(33 + title.length()/2) << title 
         << setw(33 - title.length()/2) << "║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n";
}

void Hospital::printSeparator() {
    cout << "────────────────────────────────────────────────────────────────\n";
}

void Hospital::displayMenu() {
    cout << "\n╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║               🏥 " << hospitalName << " 🏥                ║\n";
    cout << "║                Smart Hospital Management System              ║\n";
    cout << "╠══════════════════════════════════════════════════════════════╣\n";
    cout << "║  1. 👤 Admit Patient                                        ║\n";
    cout << "║  2. 🚪 Discharge Patient                                     ║\n";
    cout << "║  3. 👨‍⚕️ Add Doctor                                          ║\n";
    cout << "║  4. ⚕️ Schedule Surgery                                      ║\n";
    cout << "║  5. 📋 View All Patients                                     ║\n";
    cout << "║  6. 👩‍⚕️ View All Doctors                                     ║\n";
    cout << "║  7. 🏥 View Ward Status                                      ║\n";
    cout << "║  8. 🩺 View Surgery Schedule                                 ║\n";
    cout << "║  9. 📊 Hospital Dashboard                                    ║\n";
    cout << "║  10. 💾 Save & Exit                                         ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n";
    cout << "Enter your choice (1-10): ";
}

void Hospital::admitPatient() {
    printHeader("ADMIT PATIENT");
    
    string name, condition;
    int age;
    
    cout << "Enter patient name: ";
    cin.ignore();
    getline(cin, name);
    
    cout << "Enter patient age: ";
    cin >> age;
    
    cout << "Enter medical condition: ";
    cin.ignore();
    getline(cin, condition);
    
    Patient newPatient(nextPatientId++, name, age, condition);
    
    // Try to assign a bed
    bool bedAssigned = false;
    for(auto& ward : wards) {
        int bedNumber = ward.assignBed();
        if(bedNumber != -1) {
            newPatient.setBedNumber(bedNumber);
            newPatient.setIsAdmitted(true);
            patients.push_back(newPatient);
            bedAssigned = true;
            
            cout << "\n✅ Patient admitted successfully!\n";
            cout << "   Patient ID: " << newPatient.getPatientId() << "\n";
            cout << "   Assigned to: " << ward.getWardName() 
                 << ", Bed #" << bedNumber << "\n";
            break;
        }
    }
    
    if(!bedAssigned) {
        waitingQueue.push(newPatient);
        patients.push_back(newPatient);
        cout << "\n⏳ No beds available. Patient added to waiting queue.\n";
        cout << "   Position in queue: " << waitingQueue.size() << "\n";
    }
}

void Hospital::dischargePatient() {
    printHeader("DISCHARGE PATIENT");
    
    if(patients.empty()) {
        cout << "No patients to discharge.\n";
        return;
    }
    
    displayPatients();
    
    int patientId;
    cout << "\nEnter Patient ID to discharge: ";
    cin >> patientId;
    
    auto it = find_if(patients.begin(), patients.end(),
                      [patientId](const Patient& p) {
                          return p.getPatientId() == patientId && p.getIsAdmitted();
                      });
    
    if(it != patients.end()) {
        // Free the bed
        int bedNumber = it->getBedNumber();
        for(auto& ward : wards) {
            if(ward.isBedOccupied(bedNumber)) {
                ward.freeBed(bedNumber);
                break;
            }
        }
        
        cout << "\n✅ Patient " << it->getName() << " discharged successfully!\n";
        patients.erase(it);
        
        // Check if there's a waiting patient
        if(!waitingQueue.empty()) {
            Patient waitingPatient = waitingQueue.front();
            waitingQueue.pop();
            
            // Assign bed to waiting patient
            for(auto& ward : wards) {
                int newBedNumber = ward.assignBed();
                if(newBedNumber != -1) {
                    // Update the patient in the vector
                    auto waitingIt = find_if(patients.begin(), patients.end(),
                                           [&waitingPatient](Patient& p) {
                                               return p.getPatientId() == waitingPatient.getPatientId();
                                           });
                    if(waitingIt != patients.end()) {
                        waitingIt->setBedNumber(newBedNumber);
                        waitingIt->setIsAdmitted(true);
                        
                        cout << "🔄 Waiting patient " << waitingPatient.getName() 
                             << " has been automatically admitted!\n";
                        cout << "   Assigned to: " << ward.getWardName() 
                             << ", Bed #" << newBedNumber << "\n";
                    }
                    break;
                }
            }
        }
    } else {
        cout << "\n❌ Patient not found or not admitted.\n";
    }
}

void Hospital::addDoctor() {
    printHeader("ADD DOCTOR");
    
    string name, specialization;
    
    cout << "Enter doctor name: ";
    cin.ignore();
    getline(cin, name);
    
    cout << "Enter specialization: ";
    getline(cin, specialization);
    
    Doctor newDoctor(nextDoctorId++, name, specialization);
    doctors.push_back(newDoctor);
    
    cout << "\n✅ Doctor added successfully!\n";
    cout << "   Doctor ID: " << newDoctor.getDoctorId() << "\n";
    cout << "   Name: " << name << "\n";
    cout << "   Specialization: " << specialization << "\n";
}

void Hospital::scheduleSurgery() {
    printHeader("SCHEDULE SURGERY");
    
    if(patients.empty() || doctors.empty()) {
        cout << "❌ Need at least one patient and one doctor to schedule surgery.\n";
        return;
    }
    
    displayPatients();
    cout << "\nEnter Patient ID for surgery: ";
    int patientId;
    cin >> patientId;
    
    Patient* patient = findPatientById(patientId);
    if(!patient) {
        cout << "❌ Patient not found.\n";
        return;
    }
    
    displayDoctors();
    cout << "\nEnter Doctor ID: ";
    int doctorId;
    cin >> doctorId;
    
    Doctor* doctor = findDoctorById(doctorId);
    if(!doctor) {
        cout << "❌ Doctor not found.\n";
        return;
    }
    
    string surgeryType, scheduledTime;
    int priorityChoice;
    
    cout << "Enter surgery type: ";
    cin.ignore();
    getline(cin, surgeryType);
    
    cout << "Enter scheduled time (e.g., 14:00): ";
    getline(cin, scheduledTime);
    
    cout << "\nSelect Priority:\n";
    cout << "1. Low\n2. Medium\n3. High\n4. Critical\n";
    cout << "Enter choice (1-4): ";
    cin >> priorityChoice;
    
    Priority priority = static_cast<Priority>(priorityChoice);
    
    Surgery newSurgery(nextSurgeryId++, patientId, doctorId, surgeryType, priority, scheduledTime);
    surgeryQueue.push(newSurgery);
    
    cout << "\n✅ Surgery scheduled successfully!\n";
    cout << "   Surgery ID: " << newSurgery.getSurgeryId() << "\n";
    cout << "   Priority: " << newSurgery.getPriorityString() << "\n";
}

void Hospital::displayPatients() {
    printHeader("PATIENT LIST");
    
    if(patients.empty()) {
        cout << "No patients registered.\n";
        return;
    }
    
    // Sort patients by ID
    vector<Patient> sortedPatients = patients;
    sort(sortedPatients.begin(), sortedPatients.end(),
         [](const Patient& a, const Patient& b) {
             return a.getPatientId() < b.getPatientId();
         });
    
    cout << "┌─────┬─────────────────┬─────┬─────────────────┬─────┬─────────┐\n";
    cout << "│ ID  │ Name            │ Age │ Condition       │ Bed │ Status  │\n";
    cout << "├─────┼─────────────────┼─────┼─────────────────┼─────┼─────────┤\n";
    
    for(const auto& patient : sortedPatients) {
        patient.displayPatient();
    }
    
    cout << "└─────┴─────────────────┴─────┴─────────────────┴─────┴─────────┘\n";
    
    if(!waitingQueue.empty()) {
        cout << "\n⏳ Patients in waiting queue: " << waitingQueue.size() << "\n";
    }
}

void Hospital::displayDoctors() {
    printHeader("DOCTOR LIST");
    
    if(doctors.empty()) {
        cout << "No doctors registered.\n";
        return;
    }
    
    // Sort doctors by name
    vector<Doctor> sortedDoctors = doctors;
    sort(sortedDoctors.begin(), sortedDoctors.end(),
         [](const Doctor& a, const Doctor& b) {
             return a.getName() < b.getName();
         });
    
    cout << "┌─────┬─────────────────┬─────────────────┬───────────┐\n";
    cout << "│ ID  │ Name            │ Specialization  │ Status    │\n";
    cout << "├─────┼─────────────────┼─────────────────┼───────────┤\n";
    
    for(const auto& doctor : sortedDoctors) {
        doctor.displayDoctor();
    }
    
    cout << "└─────┴─────────────────┴─────────────────┴───────────┘\n";
}

void Hospital::displayWardStatus() {
    printHeader("WARD STATUS");
    
    cout << "┌─────┬─────────────────┬───────┬─────────┬───────────┐\n";
    cout << "│ ID  │ Ward Name       │ Total │ Occupied│ Available │\n";
    cout << "├─────┼─────────────────┼───────┼─────────┼───────────┤\n";
    
    for(const auto& ward : wards) {
        ward.displayWardStatus();
    }
    
    cout << "└─────┴─────────────────┴───────┴─────────┴───────────┘\n";
}

void Hospital::displaySurgeries() {
    printHeader("SURGERY SCHEDULE");
    
    if(surgeryQueue.empty()) {
        cout << "No surgeries scheduled.\n";
        return;
    }
    
    // Create a copy to display without destroying the queue
    priority_queue<Surgery> tempQueue = surgeryQueue;
    vector<Surgery> surgeries;
    
    while(!tempQueue.empty()) {
        surgeries.push_back(tempQueue.top());
        tempQueue.pop();
    }
    
    cout << "┌─────┬─────┬─────┬──────────────┬──────────┬────────────┐\n";
    cout << "│ S.ID│ P.ID│ D.ID│ Surgery Type │ Priority │ Time       │\n";
    cout << "├─────┼─────┼─────┼──────────────┼──────────┼────────────┤\n";
    
    for(const auto& surgery : surgeries) {
        surgery.displaySurgery();
    }
    
    cout << "└─────┴─────┴─────┴──────────────┴──────────┴────────────┘\n";
}

void Hospital::displayDashboard() {
    printHeader("HOSPITAL DASHBOARD");
    
    int totalPatients = patients.size();
    int admittedPatients = 0;
    int totalBeds = 0, occupiedBeds = 0;
    
    for(const auto& patient : patients) {
        if(patient.getIsAdmitted()) admittedPatients++;
    }
    
    for(const auto& ward : wards) {
        totalBeds += ward.getTotalBeds();
        occupiedBeds += ward.getOccupiedBeds();
    }
    
    cout << "┌────────────────────────────────────────────────────────────┐\n";
    cout << "│                        STATISTICS                          │\n";
    cout << "├────────────────────────────────────────────────────────────┤\n";
    cout << "│ Total Patients Registered: " << setw(31) << totalPatients << " │\n";
    cout << "│ Currently Admitted:        " << setw(31) << admittedPatients << " │\n";
    cout << "│ Patients in Waiting Queue: " << setw(31) << waitingQueue.size() << " │\n";
    cout << "│ Total Doctors:             " << setw(31) << doctors.size() << " │\n";
    cout << "│ Total Beds:                " << setw(31) << totalBeds << " │\n";
    cout << "│ Occupied Beds:             " << setw(31) << occupiedBeds << " │\n";
    cout << "│ Available Beds:            " << setw(31) << (totalBeds - occupiedBeds) << " │\n";
    cout << "│ Surgeries Scheduled:       " << setw(31) << surgeryQueue.size() << " │\n";
    cout << "└────────────────────────────────────────────────────────────┘\n";
    
    // Bed occupancy rate
    double occupancyRate = (totalBeds > 0) ? (double)occupiedBeds / totalBeds * 100 : 0;
    cout << "\n📊 Bed Occupancy Rate: " << fixed << setprecision(1) << occupancyRate << "%\n";
    
    if(occupancyRate > 80) {
        cout << "⚠️  High occupancy - Consider expanding capacity\n";
    } else if(occupancyRate < 30) {
        cout << "ℹ️  Low occupancy - Good availability\n";
    } else {
        cout << "✅ Normal occupancy levels\n";
    }
}

Patient* Hospital::findPatientById(int id) {
    auto it = find_if(patients.begin(), patients.end(),
                      [id](const Patient& p) { return p.getPatientId() == id; });
    return (it != patients.end()) ? &(*it) : nullptr;
}

Doctor* Hospital::findDoctorById(int id) {
    auto it = find_if(doctors.begin(), doctors.end(),
                      [id](const Doctor& d) { return d.getDoctorId() == id; });
    return (it != doctors.end()) ? &(*it) : nullptr;
}

void Hospital::saveData() {
    // Save patients
    ofstream patientFile("patients.txt");
    for(const auto& patient : patients) {
        patientFile << patient.toFileString() << "\n";
    }
    patientFile.close();
    
    // Save doctors
    ofstream doctorFile("doctors.txt");
    for(const auto& doctor : doctors) {
        doctorFile << doctor.toFileString() << "\n";
    }
    doctorFile.close();
    
    // Save surgeries
    ofstream surgeryFile("surgeries.txt");
    priority_queue<Surgery> tempQueue = surgeryQueue;
    while(!tempQueue.empty()) {
        surgeryFile << tempQueue.top().toFileString() << "\n";
        tempQueue.pop();
    }
    surgeryFile.close();
    
    // Save waiting queue
    ofstream waitingFile("waiting.txt");
    queue<Patient> tempWaitingQueue = waitingQueue;
    while(!tempWaitingQueue.empty()) {
        waitingFile << tempWaitingQueue.front().toFileString() << "\n";
        tempWaitingQueue.pop();
    }
    waitingFile.close();
    
    // Save counters
    ofstream counterFile("counters.txt");
    counterFile << nextPatientId << "\n" << nextDoctorId << "\n" << nextSurgeryId << "\n";
    counterFile.close();
    
    cout << "\n💾 Data saved successfully!\n";
}

void Hospital::loadData() {
    // Load patients
    ifstream patientFile("patients.txt");
    string line;
    while(getline(patientFile, line) && !line.empty()) {
        patients.push_back(Patient::fromFileString(line));
    }
    patientFile.close();
    
    // Load doctors
    ifstream doctorFile("doctors.txt");
    while(getline(doctorFile, line) && !line.empty()) {
        doctors.push_back(Doctor::fromFileString(line));
    }
    doctorFile.close();
    
    // Load surgeries
    ifstream surgeryFile("surgeries.txt");
    while(getline(surgeryFile, line) && !line.empty()) {
        surgeryQueue.push(Surgery::fromFileString(line));
    }
    surgeryFile.close();
    
    // Load waiting queue
    ifstream waitingFile("waiting.txt");
    while(getline(waitingFile, line) && !line.empty()) {
        Patient waitingPatient = Patient::fromFileString(line);
        if(!waitingPatient.getIsAdmitted()) {
            waitingQueue.push(waitingPatient);
        }
    }
    waitingFile.close();
    
    // Load counters
    ifstream counterFile("counters.txt");
    if(counterFile.is_open()) {
        counterFile >> nextPatientId >> nextDoctorId >> nextSurgeryId;
        counterFile.close();
    }
    
    // Update ward bed status based on admitted patients
    for(const auto& patient : patients) {
        if(patient.getIsAdmitted() && patient.getBedNumber() != -1) {
            for(auto& ward : wards) {
                if(patient.getBedNumber() <= ward.getTotalBeds()) {
                    // This is a simplified approach - in a real system, 
                    // you'd track which ward each bed belongs to
                    break;
                }
            }
        }
    }
}
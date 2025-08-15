#include "Ward.h"
#include <iostream>

Ward::Ward() : wardId(0), wardName(""), totalBeds(0) {}

Ward::Ward(int id, string name, int beds) 
    : wardId(id), wardName(name), totalBeds(beds) {
    bedStatus.resize(beds, false); // Initialize all beds as available
}

int Ward::getWardId() const { return wardId; }
string Ward::getWardName() const { return wardName; }
int Ward::getTotalBeds() const { return totalBeds; }

int Ward::getAvailableBeds() const {
    int available = 0;
    for(bool status : bedStatus) {
        if(!status) available++;
    }
    return available;
}

int Ward::getOccupiedBeds() const {
    return totalBeds - getAvailableBeds();
}

int Ward::assignBed() {
    for(int i = 0; i < totalBeds; i++) {
        if(!bedStatus[i]) {
            bedStatus[i] = true;
            return i + 1; // Bed numbers start from 1
        }
    }
    return -1; // No bed available
}

void Ward::freeBed(int bedNumber) {
    if(bedNumber >= 1 && bedNumber <= totalBeds) {
        bedStatus[bedNumber - 1] = false;
    }
}

bool Ward::isBedOccupied(int bedNumber) const {
    if(bedNumber >= 1 && bedNumber <= totalBeds) {
        return bedStatus[bedNumber - 1];
    }
    return false;
}

void Ward::displayWardStatus() const {
    cout << "| " << wardId << " | " << wardName;
    for(int i = wardName.length(); i < 15; i++) cout << " ";
    cout << "| " << totalBeds << " | " << getOccupiedBeds() << " | " 
         << getAvailableBeds() << " |" << endl;
}

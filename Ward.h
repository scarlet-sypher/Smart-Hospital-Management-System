#ifndef WARD_H
#define WARD_H

#include <vector>
#include <string>
using namespace std;

class Ward {
private:
    int wardId;
    string wardName;
    int totalBeds;
    vector<bool> bedStatus; // true = occupied, false = available

public:
    Ward();
    Ward(int id, string name, int beds);
    
    // Getters
    int getWardId() const;
    string getWardName() const;
    int getTotalBeds() const;
    int getAvailableBeds() const;
    int getOccupiedBeds() const;
    
    // Bed operations
    int assignBed(); // returns bed number or -1 if no bed available
    void freeBed(int bedNumber);
    bool isBedOccupied(int bedNumber) const;
    
    // Display
    void displayWardStatus() const;
};

#endif
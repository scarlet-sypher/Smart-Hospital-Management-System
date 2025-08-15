#include "Hospital.h"
#include <iostream>
#include <limits>

using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseSystem() {
    cout << "\nPress Enter to continue...\nType exit to exit: ";
    cin.ignore();
    cin.get();
}

int main() {
    Hospital hospital("City General Hospital");
    
    cout << "🏥 Welcome to the Smart Hospital Management System! 🏥\n";
    cout << "Loading data...\n";
    
    int choice;
    
    while(true) {
        clearScreen();
        hospital.displayMenu();
        
        // Input validation
        while(!(cin >> choice) || choice < 1 || choice > 10) {
            cout << "❌ Invalid input! Please enter a number between 1-10: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        switch(choice) {
            case 1:
                clearScreen();
                hospital.admitPatient();
                pauseSystem();
                break;
                
            case 2:
                clearScreen();
                hospital.dischargePatient();
                pauseSystem();
                break;
                
            case 3:
                clearScreen();
                hospital.addDoctor();
                pauseSystem();
                break;
                
            case 4:
                clearScreen();
                hospital.scheduleSurgery();
                pauseSystem();
                break;
                
            case 5:
                clearScreen();
                hospital.displayPatients();
                pauseSystem();
                break;
                
            case 6:
                clearScreen();
                hospital.displayDoctors();
                pauseSystem();
                break;
                
            case 7:
                clearScreen();
                hospital.displayWardStatus();
                pauseSystem();
                break;
                
            case 8:
                clearScreen();
                hospital.displaySurgeries();
                pauseSystem();
                break;
                
            case 9:
                clearScreen();
                hospital.displayDashboard();
                pauseSystem();
                break;
                
            case 10:
                clearScreen();
                hospital.saveData();
                cout << "\n🏥 Thank you for using the Hospital Management System!\n";
                cout << "👋 Goodbye!\n";
                return 0;
                
            default:
                cout << "❌ Invalid choice! Please try again.\n";
                pauseSystem();
        }
    }
    
    return 0;
}
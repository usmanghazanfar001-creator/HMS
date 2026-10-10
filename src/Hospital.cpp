#include "Hospital.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>  // for system()

using namespace std;

Hospital::Hospital() 
    : appointmentManager(&patientManager, &doctorManager) {
    floors = 3;
    roomsPerFloor = 10;
    initializeWards();
}

Hospital::~Hospital() {
    cleanupWards();
}

void Hospital::initializeWards() {
    // Allocate memory for floors (using double pointer)
    wards = new char**[floors];
    
    for (int i = 0; i < floors; i++) {
        // Allocate memory for rooms on each floor
        wards[i] = new char*[roomsPerFloor];
        
        for (int j = 0; j < roomsPerFloor; j++) {
            // Initialize each room as empty
            wards[i][j] = new char[50];
            strcpy(wards[i][j], "Empty");
        }
    }
}

void Hospital::cleanupWards() {
    for (int i = 0; i < floors; i++) {
        for (int j = 0; j < roomsPerFloor; j++) {
            delete[] wards[i][j];
        }
        delete[] wards[i];
    }
    delete[] wards;
}

void Hospital::run() {
    int choice;

    do {
        Utils::clearScreen();   // <-- Clear the screen

        showMainMenu();
        
        choice = Utils::getValidatedInt("Enter your choice: ", 0, 7);

        switch (choice) {
            case 1:
                Utils::clearScreen();
                showDashboard();
                Utils::pauseScreen();
                break;

            case 2:
                Utils::clearScreen();
                patientManagementMenu();
                break;

            case 3:
                Utils::clearScreen();
                doctorManagementMenu();
                break;

            case 4:
                Utils::clearScreen();
                roomManagementMenu();
                break;

            case 5:
                Utils::clearScreen();
                appointmentManagementMenu();
                break;

            case 6:
                Utils::clearScreen();
                billingMenu();
                break;

            case 7:
                Utils::clearScreen();
                cout << "\nThank you for using Hospital Management System!\n";
                break;

            default:
                cout << "Invalid choice!\n";
                Utils::pauseScreen();
        }

    } while (choice != 7);
}

void Hospital::showMainMenu() {
    Utils::printHeader("HOSPITAL MANAGEMENT SYSTEM");
    cout << "1. Dashboard\n";
    cout << "2. Patient Management\n";
    cout << "3. Doctor Management\n";
    cout << "4. Room Management\n";
    cout << "5. Appointment Management\n";
    cout << "6. Billing\n";
    cout << "7. Exit\n";
    Utils::printSeparator('=', 80);
}

void Hospital::showDashboard() {
    Utils::printHeader("DASHBOARD");
    
    cout << "Total Patients: " << patientManager.getPatientCount() << endl;
    cout << "Total Doctors: " << doctorManager.getDoctorCount() << endl;
    
    // Calculate room statistics
    int occupiedRooms = 0;
    int totalRooms = floors * roomsPerFloor;
    
    for (int i = 0; i < floors; i++) {
        for (int j = 0; j < roomsPerFloor; j++) {
            if (strcmp(wards[i][j], "Empty") != 0) {
                occupiedRooms++;
            }
        }
    }
    
    cout << "Total Rooms: " << totalRooms << endl;
    cout << "Occupied Rooms: " << occupiedRooms << endl;
    cout << "Available Rooms: " << (totalRooms - occupiedRooms) << endl;
    cout << "Total Appointments: " << appointmentManager.getAppointmentCount() << endl;
    
    Utils::printSeparator('=', 80);
    system("pause");
}

void Hospital::patientManagementMenu() {
    int choice;
    do {
        Utils::printHeader("PATIENT MANAGEMENT");
        cout << "1. Add Patient\n";
        cout << "2. Display All Patients\n";
        cout << "3. Search Patient by ID\n";
        cout << "4. Update Patient\n";
        cout << "5. Delete Patient\n";
        cout << "6. Add Patient Note (Jagged Array Demo)\n";
        cout << "7. Back to Main Menu\n";
        Utils::printSeparator('-', 80);
        
        choice = Utils::getValidatedInt("Enter your choice: ", 1, 7);
        
        switch (choice) {
            case 1:
                patientManager.addPatient();
                break;
            case 2:
                patientManager.displayAllPatients();
                break;
            case 3:
                patientManager.searchPatient();
                break;
            case 4:
                patientManager.updatePatient();
                break;
            case 5:
                patientManager.deletePatient();
                break;
            case 6:
                patientManager.addPatientNote();
                break;
            case 7:
                cout << "Returning to main menu...\n";
                break;
        }
        
        if (choice != 7) {
            system("pause");
        }
    } while (choice != 7);
}

void Hospital::doctorManagementMenu() {
    int choice;
    do {
        Utils::printHeader("DOCTOR MANAGEMENT");
        cout << "1. Add Doctor\n";
        cout << "2. Display All Doctors\n";
        cout << "3. Search Doctor by ID\n";
        cout << "4. Update Doctor\n";
        cout << "5. Delete Doctor\n";
        cout << "6. Back to Main Menu\n";
        Utils::printSeparator('-', 80);
        
        choice = Utils::getValidatedInt("Enter your choice: ", 1, 6);
        
        switch (choice) {
            case 1:
                doctorManager.addDoctor();
                break;
            case 2:
                doctorManager.displayAllDoctors();
                break;
            case 3:
                doctorManager.searchDoctor();
                break;
            case 4:
                doctorManager.updateDoctor();
                break;
            case 5:
                doctorManager.deleteDoctor();
                break;
            case 6:
                cout << "Returning to main menu...\n";
                break;
        }
        
        if (choice != 6) {
            system("pause");
        }
    } while (choice != 6);
}

void Hospital::roomManagementMenu() {
    int choice;
    do {
        Utils::printHeader("ROOM MANAGEMENT");
        cout << "1. Show Rooms\n";
        cout << "2. Allocate Room\n";
        cout << "3. Release Room\n";
        cout << "4. Back to Main Menu\n";
        Utils::printSeparator('-', 80);
        
        choice = Utils::getValidatedInt("Enter your choice: ", 1, 4);
        
        switch (choice) {
            case 1:
                showRooms();
                break;
            case 2:
                allocateRoom();
                break;
            case 3:
                releaseRoom();
                break;
            case 4:
                cout << "Returning to main menu...\n";
                break;
        }
        
        if (choice != 4) {
            system("pause");
        }
    } while (choice != 4);
}

void Hospital::showRooms() {
    Utils::printHeader("HOSPITAL ROOMS");
    
    cout << "Legend: [Floor - Room] Patient Name\n";
    Utils::printSeparator('-', 80);
    
    for (int i = 0; i < floors; i++) {
        cout << "\nFloor " << (i + 1) << ":\n";
        for (int j = 0; j < roomsPerFloor; j++) {
            cout << "  Room " << (j + 1) << ": ";
            if (strcmp(wards[i][j], "Empty") == 0) {
                cout << "[Available]";
            } else {
                cout << wards[i][j];
            }
            cout << endl;
        }
        Utils::printSeparator('-', 40);
    }
}

void Hospital::allocateRoom() {
    // First display available rooms
    cout << "\nAvailable Rooms:\n";
    for (int i = 0; i < floors; i++) {
        for (int j = 0; j < roomsPerFloor; j++) {
            if (strcmp(wards[i][j], "Empty") == 0) {
                cout << "Floor " << (i + 1) << ", Room " << (j + 1) << endl;
            }
        }
    }
    
    int floor = Utils::getValidatedInt("Enter Floor (1-3): ", 1, floors) - 1;
    int room = Utils::getValidatedInt("Enter Room (1-10): ", 1, roomsPerFloor) - 1;
    
    if (strcmp(wards[floor][room], "Empty") != 0) {
        cout << "Room is already occupied!\n";
        return;
    }
    
    char patientName[50];
    Utils::getValidatedString("Enter Patient Name: ", patientName, 50);
    strcpy(wards[floor][room], patientName);
    
    cout << "Room allocated successfully to " << patientName << endl;
}

void Hospital::releaseRoom() {
    int floor = Utils::getValidatedInt("Enter Floor (1-3): ", 1, floors) - 1;
    int room = Utils::getValidatedInt("Enter Room (1-10): ", 1, roomsPerFloor) - 1;
    
    if (strcmp(wards[floor][room], "Empty") == 0) {
        cout << "Room is already empty!\n";
        return;
    }
    
    cout << "Releasing room occupied by: " << wards[floor][room] << endl;
    strcpy(wards[floor][room], "Empty");
    cout << "Room released successfully!\n";
}

void Hospital::appointmentManagementMenu() {
    int choice;
    do {
        Utils::printHeader("APPOINTMENT MANAGEMENT");
        cout << "1. Book Appointment\n";
        cout << "2. Cancel Appointment\n";
        cout << "3. Display All Appointments\n";
        cout << "4. Back to Main Menu\n";
        Utils::printSeparator('-', 80);
        
        choice = Utils::getValidatedInt("Enter your choice: ", 1, 4);
        
        switch (choice) {
            case 1:
                appointmentManager.bookAppointment();
                break;
            case 2:
                appointmentManager.cancelAppointment();
                break;
            case 3:
                appointmentManager.displayAllAppointments();
                break;
            case 4:
                cout << "Returning to main menu...\n";
                break;
        }
        
        if (choice != 4) {
            system("pause");
        }
    } while (choice != 4);
}

void Hospital::billingMenu() {
    int choice;
    do {
        Utils::printHeader("BILLING");
        cout << "1. Create Bill\n";
        cout << "2. Display All Bills\n";
        cout << "3. Display Bill by ID\n";
        cout << "4. Mark Bill as Paid\n";
        cout << "5. Generate Summary\n";
        cout << "6. Back to Main Menu\n";
        Utils::printSeparator('-', 80);
        
        choice = Utils::getValidatedInt("Enter your choice: ", 1, 6);
        
        switch (choice) {
            case 1:
                billingManager.createBill();
                break;
            case 2:
                billingManager.displayAllBills();
                break;
            case 3: {
                int id = Utils::getValidatedInt("Enter Bill ID: ", 4000, 9999);
                billingManager.displayBill(id);
                break;
            }
            case 4:
                billingManager.markAsPaid();
                break;
            case 5:
                billingManager.generateBillSummary();
                break;
            case 6:
                cout << "Returning to main menu...\n";
                break;
        }
        
        if (choice != 6) {
            system("pause");
        }
    } while (choice != 6);
}
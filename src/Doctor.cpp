#include "Doctor.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

DoctorManager::DoctorManager() {
    capacity = 3;
    doctors = new Doctor[capacity];
    doctorCount = 0;
}

DoctorManager::~DoctorManager() {
    delete[] doctors;
}

void DoctorManager::resizeDoctorArray() {
    capacity *= 2;
    Doctor* newDoctors = new Doctor[capacity];
    
    for (int i = 0; i < doctorCount; i++) {
        newDoctors[i] = doctors[i];
    }
    
    delete[] doctors;
    doctors = newDoctors;
}

int DoctorManager::findDoctorIndex(int id) const {
    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].doctorId == id && doctors[i].isActive) {
            return i;
        }
    }
    return -1;
}

void DoctorManager::initializeDoctor(Doctor& d, int id) {
    d.doctorId = id;
    d.isActive = true;
    
    Utils::getValidatedString("Enter Doctor Name: ", d.name, 50);
    Utils::getValidatedString("Enter Specialization: ", d.specialization, 50);
    
    int availability = Utils::getValidatedInt("Is Doctor Available? (1-Yes, 0-No): ", 0, 1);
    d.isAvailable = (availability == 1);
}

void DoctorManager::addDoctor() {
    if (doctorCount >= capacity) {
        resizeDoctorArray();
    }
    
    int id = 2000 + doctorCount + 1;
    initializeDoctor(doctors[doctorCount], id);
    doctorCount++;
    cout << "\nDoctor added successfully! ID: " << id << endl;
}

void DoctorManager::displayDoctor(const Doctor& d) const {
    cout << left
         << setw(10) << d.doctorId
         << setw(25) << d.name
         << setw(25) << d.specialization
         << setw(15) << (d.isAvailable ? "Available" : "Unavailable")
         << endl;
}

void DoctorManager::displayAllDoctors() const {
    if (doctorCount == 0) {
        cout << "\nNo doctors registered.\n";
        return;
    }
    
    Utils::printHeader("DOCTOR LIST");
    cout << left
         << setw(10) << "ID"
         << setw(25) << "Name"
         << setw(25) << "Specialization"
         << setw(15) << "Availability"
         << endl;
    Utils::printSeparator('-', 75);
    
    bool found = false;
    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].isActive) {
            displayDoctor(doctors[i]);
            found = true;
        }
    }
    
    if (!found) {
        cout << "No active doctors found.\n";
    }
}

void DoctorManager::searchDoctor() const {
    if (doctorCount == 0) {
        cout << "\nNo doctors registered.\n";
        return;
    }
    
    int id = Utils::getValidatedInt("Enter Doctor ID to search: ", 2000, 9999);
    int index = findDoctorIndex(id);
    
    if (index == -1) {
        cout << "Doctor not found.\n";
        return;
    }
    
    Utils::printHeader("DOCTOR DETAILS");
    cout << left
         << setw(10) << "ID"
         << setw(25) << "Name"
         << setw(25) << "Specialization"
         << setw(15) << "Availability"
         << endl;
    Utils::printSeparator('-', 75);
    displayDoctor(doctors[index]);
}

void DoctorManager::updateDoctor() {
    if (doctorCount == 0) {
        cout << "\nNo doctors registered.\n";
        return;
    }
    
    int id = Utils::getValidatedInt("Enter Doctor ID to update: ", 2000, 9999);
    int index = findDoctorIndex(id);
    
    if (index == -1) {
        cout << "Doctor not found.\n";
        return;
    }
    
    cout << "\nUpdating doctor: " << doctors[index].name << endl;
    cout << "Leave blank to keep current value.\n";
    
    char temp[50];
    
    cout << "Current Name: " << doctors[index].name << "\nNew Name: ";
    cin.getline(temp, 50);
    if (strlen(temp) > 0) {
        strcpy(doctors[index].name, temp);
    }
    
    // Update specialization and availability similarly...
    cout << "Doctor updated successfully!\n";
}

void DoctorManager::deleteDoctor() {
    if (doctorCount == 0) {
        cout << "\nNo doctors registered.\n";
        return;
    }
    
    int id = Utils::getValidatedInt("Enter Doctor ID to delete: ", 2000, 9999);
    int index = findDoctorIndex(id);
    
    if (index == -1) {
        cout << "Doctor not found.\n";
        return;
    }
    
    cout << "Are you sure you want to delete doctor: " << doctors[index].name << "? (Y/N): ";
    char confirm;
    cin >> confirm;
    Utils::clearInputBuffer();
    
    if (toupper(confirm) == 'Y') {
        doctors[index].isActive = false;
        cout << "Doctor deleted successfully!\n";
    } else {
        cout << "Delete cancelled.\n";
    }
}

bool DoctorManager::isDoctorAvailable(int id) const {
    int index = findDoctorIndex(id);
    if (index == -1) return false;
    return doctors[index].isAvailable;
}
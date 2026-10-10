#include "Appointment.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

AppointmentManager::AppointmentManager(PatientManager* pMgr, DoctorManager* dMgr) {
    capacity = 5;
    appointments = new Appointment[capacity];
    appointmentCount = 0;
    patientManager = pMgr;
    doctorManager = dMgr;
}

AppointmentManager::~AppointmentManager() {
    delete[] appointments;
}

void AppointmentManager::resizeAppointmentArray() {
    capacity *= 2;
    Appointment* newAppointments = new Appointment[capacity];
    
    for (int i = 0; i < appointmentCount; i++) {
        newAppointments[i] = appointments[i];
    }
    
    delete[] appointments;
    appointments = newAppointments;
}

int AppointmentManager::findAppointmentIndex(int id) const {
    for (int i = 0; i < appointmentCount; i++) {
        if (appointments[i].appointmentId == id && appointments[i].isActive) {
            return i;
        }
    }
    return -1;
}

bool AppointmentManager::isValidAppointment(int patientId, int doctorId) const {
    // Check if patient exists
    const Patient* patients = patientManager->getPatients();
    bool patientExists = false;
    for (int i = 0; i < patientManager->getPatientCount(); i++) {
        if (patients[i].patientId == patientId && patients[i].isActive) {
            patientExists = true;
            break;
        }
    }
    
    if (!patientExists) {
        cout << "Patient not found.\n";
        return false;
    }
    
    // Check if doctor exists and is available
    if (!doctorManager->isDoctorAvailable(doctorId)) {
        cout << "Doctor not found or not available.\n";
        return false;
    }
    
    return true;
}

void AppointmentManager::initializeAppointment(Appointment& a, int id) {
    a.appointmentId = id;
    a.isActive = true;
    
    // Display available doctors
    cout << "\nAvailable Doctors:\n";
    doctorManager->displayAllDoctors();
    
    a.doctorId = Utils::getValidatedInt("Enter Doctor ID: ", 2000, 9999);
    
    // Display patients
    cout << "\nRegistered Patients:\n";
    patientManager->displayAllPatients();
    
    a.patientId = Utils::getValidatedInt("Enter Patient ID: ", 1000, 9999);
    
    if (!isValidAppointment(a.patientId, a.doctorId)) {
        a.isActive = false;
        return;
    }
    
    Utils::getValidatedString("Enter Date (DD/MM/YYYY): ", a.date, 20);
    Utils::getValidatedString("Enter Time (HH:MM): ", a.time, 10);
}

void AppointmentManager::bookAppointment() {
    if (appointmentCount >= capacity) {
        resizeAppointmentArray();
    }
    
    int id = 3000 + appointmentCount + 1;
    initializeAppointment(appointments[appointmentCount], id);
    
    if (appointments[appointmentCount].isActive) {
        appointmentCount++;
        cout << "\nAppointment booked successfully! ID: " << id << endl;
    } else {
        cout << "\nFailed to book appointment.\n";
    }
}

void AppointmentManager::cancelAppointment() {
    if (appointmentCount == 0) {
        cout << "\nNo appointments found.\n";
        return;
    }
    
    int id = Utils::getValidatedInt("Enter Appointment ID to cancel: ", 3000, 9999);
    int index = findAppointmentIndex(id);
    
    if (index == -1) {
        cout << "Appointment not found.\n";
        return;
    }
    
    cout << "Are you sure you want to cancel appointment? (Y/N): ";
    char confirm;
    cin >> confirm;
    Utils::clearInputBuffer();
    
    if (toupper(confirm) == 'Y') {
        appointments[index].isActive = false;
        cout << "Appointment cancelled successfully!\n";
    } else {
        cout << "Cancellation aborted.\n";
    }
}

void AppointmentManager::displayAllAppointments() const {
    if (appointmentCount == 0) {
        cout << "\nNo appointments.\n";
        return;
    }
    
    Utils::printHeader("APPOINTMENT LIST");
    cout << left
         << setw(15) << "Appt ID"
         << setw(15) << "Patient ID"
         << setw(15) << "Doctor ID"
         << setw(20) << "Date"
         << setw(10) << "Time"
         << setw(15) << "Status"
         << endl;
    Utils::printSeparator('-', 90);
    
    bool found = false;
    for (int i = 0; i < appointmentCount; i++) {
        if (appointments[i].isActive) {
            cout << left
                 << setw(15) << appointments[i].appointmentId
                 << setw(15) << appointments[i].patientId
                 << setw(15) << appointments[i].doctorId
                 << setw(20) << appointments[i].date
                 << setw(10) << appointments[i].time
                 << setw(15) << "Active"
                 << endl;
            found = true;
        }
    }
    
    if (!found) {
        cout << "No active appointments.\n";
    }
}
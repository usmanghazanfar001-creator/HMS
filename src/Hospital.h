#pragma once
#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include "Billing.h"

class Hospital
{
private:
    PatientManager patientManager;
    DoctorManager doctorManager;
    AppointmentManager appointmentManager;
    BillingManager billingManager;

    // Double pointer demonstration: 3D array for hospital wards
    char ***wards; // floors -> rooms -> patient names
    int floors;
    int roomsPerFloor;

    void initializeWards();
    void cleanupWards();
    void displayWardStatus() const;

public:
    Hospital();
    ~Hospital();

    // Main menu functions
    void run();
    void showMainMenu();
    void showDashboard();
    void patientManagementMenu();
    void doctorManagementMenu();
    void roomManagementMenu();
    void appointmentManagementMenu();
    void billingMenu();

    // Room management functions using 2D array
    void showRooms();
    void allocateRoom();
    void releaseRoom();

    // Getters for other modules
    PatientManager *getPatientManager() { return &patientManager; }
    DoctorManager *getDoctorManager() { return &doctorManager; }
};
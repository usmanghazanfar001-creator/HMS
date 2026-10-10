#pragma once
#include "Utils.h"
#include "Patient.h"
#include "Doctor.h"

struct Appointment {
    int appointmentId;
    int patientId;
    int doctorId;
    char date[20];
    char time[10];
    bool isActive;
};

class AppointmentManager {
private:
    Appointment* appointments;
    int appointmentCount;
    int capacity;
    PatientManager* patientManager;  // Pointer to patient manager
    DoctorManager* doctorManager;    // Pointer to doctor manager
    
    void resizeAppointmentArray();
    int findAppointmentIndex(int id) const;
    void initializeAppointment(Appointment& a, int id);
    bool isValidAppointment(int patientId, int doctorId) const;
    
public:
    AppointmentManager(PatientManager* pMgr, DoctorManager* dMgr);
    ~AppointmentManager();
    
    void bookAppointment();
    void cancelAppointment();
    void displayAllAppointments() const;
    
    int getAppointmentCount() const { return appointmentCount; }
};
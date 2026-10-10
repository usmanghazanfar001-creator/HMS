#pragma once
#include "Utils.h"

struct Doctor {
    int doctorId;
    char name[50];
    char specialization[50];
    bool isAvailable;
    bool isActive;
};

class DoctorManager {
private:
    Doctor* doctors;
    int doctorCount;
    int capacity;
    
    void resizeDoctorArray();
    int findDoctorIndex(int id) const;
    void initializeDoctor(Doctor& d, int id);
    
public:
    DoctorManager();
    ~DoctorManager();
    
    void addDoctor();
    void displayAllDoctors() const;
    void searchDoctor() const;
    void updateDoctor();
    void deleteDoctor();
    
    int getDoctorCount() const { return doctorCount; }
    const Doctor* getDoctors() const { return doctors; }
    bool isDoctorAvailable(int id) const;
    void displayDoctor(const Doctor& d) const;
};
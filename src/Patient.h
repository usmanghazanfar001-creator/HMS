#pragma once
#include "Utils.h"

// Patient structure with all required fields
struct Patient {
    int patientId;
    char name[50];
    int age;
    char gender;
    char disease[100];
    char phone[15];
    char assignedDoctor[50];
    int roomNumber;
    bool isActive;  // For soft delete
};

// Node structure for jagged array (patient notes)
struct NoteNode {
    char* note;         // Dynamic note text
    NoteNode* next;     // Pointer to next note
};

// Patient class for managing patient operations
class PatientManager {
private:
    Patient* patients;          // Dynamic array of patients
    int patientCount;           // Current number of patients
    int capacity;               // Current capacity
    
    // Jagged array for patient notes (using double pointers)
    NoteNode** patientNotes;    // Array of note linked lists
    int notesCapacity;          // Capacity of notes array
    
    // Private helper methods
    void resizePatientArray();
    void resizeNotesArray();
    void initializePatient(Patient& p, int id);
    int findPatientIndex(int id) const;
    void addNoteToList(int patientIndex, const char* note);
    void freeNoteList(NoteNode* head);
    
public:
    PatientManager();
    ~PatientManager();
    
    // Patient CRUD operations
    void addPatient();
    void displayAllPatients() const;
    void searchPatient() const;
    void updatePatient();
    void deletePatient();
    void addPatientNote();  // Demonstrates jagged array usage
    
    // Getters
    int getPatientCount() const { return patientCount; }
    const Patient* getPatients() const { return patients; }
    
    // Display a single patient
    void displayPatient(const Patient& p) const;
    void displayPatientHeader() const;
};
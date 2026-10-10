#include "Patient.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

PatientManager::PatientManager()
{
    // Initialize dynamic array with initial capacity
    capacity = 5;
    patients = new Patient[capacity];
    patientCount = 0;

    // Initialize jagged array for notes
    notesCapacity = 10;
    patientNotes = new NoteNode *[notesCapacity];
    for (int i = 0; i < notesCapacity; i++)
    {
        patientNotes[i] = nullptr;
    }
}

PatientManager::~PatientManager()
{
    // Clean up dynamic arrays
    delete[] patients;

    // Clean up jagged array
    for (int i = 0; i < patientCount && i < notesCapacity; i++)
    {
        freeNoteList(patientNotes[i]);
    }
    delete[] patientNotes;
}

void PatientManager::resizePatientArray()
{
    capacity *= 2; // Double the capacity - demonstrates auto-growing array
    Patient *newPatients = new Patient[capacity];

    // Copy old data to new array
    for (int i = 0; i < patientCount; i++)
    {
        newPatients[i] = patients[i];
    }

    delete[] patients;
    patients = newPatients;
}

void PatientManager::resizeNotesArray()
{
    int newNotesCapacity = notesCapacity * 2;
    NoteNode **newNotes = new NoteNode *[newNotesCapacity];

    // Copy existing note pointers
    for (int i = 0; i < notesCapacity && i < patientCount; i++)
    {
        newNotes[i] = patientNotes[i];
    }
    // Initialize new slots
    for (int i = notesCapacity; i < newNotesCapacity; i++)
    {
        newNotes[i] = nullptr;
    }

    delete[] patientNotes;
    patientNotes = newNotes;
    notesCapacity = newNotesCapacity;
}

void PatientManager::freeNoteList(NoteNode *head)
{
    NoteNode *current = head;
    while (current != nullptr)
    {
        NoteNode *temp = current;
        current = current->next;
        delete[] temp->note; // Delete dynamic note text
        delete temp;         // Delete node
    }
}

void PatientManager::addNoteToList(int patientIndex, const char *note)
{
    if (patientIndex >= notesCapacity)
    {
        resizeNotesArray();
    }

    // Create new note node
    NoteNode *newNode = new NoteNode;
    newNode->note = new char[strlen(note) + 1];
    strcpy(newNode->note, note);
    newNode->next = nullptr;

    // Add to linked list (at end)
    if (patientNotes[patientIndex] == nullptr)
    {
        patientNotes[patientIndex] = newNode;
    }
    else
    {
        NoteNode *current = patientNotes[patientIndex];
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

void PatientManager::initializePatient(Patient &p, int id)
{
    p.patientId = id;
    p.isActive = true;

    Utils::getValidatedString("Enter Patient Name: ", p.name, 50);
    p.age = Utils::getValidatedInt("Enter Age: ", 0, 150);

    // Gender validation
    do
    {
        cout << "Enter Gender (M/F): ";
        cin >> p.gender;
        p.gender = toupper(p.gender);
        Utils::clearInputBuffer();
        if (!Utils::isValidGender(p.gender))
        {
            cout << "Invalid gender. Please enter M or F.\n";
        }
    } while (!Utils::isValidGender(p.gender));

    Utils::getValidatedString("Enter Disease: ", p.disease, 100);

    // Phone validation
    do
    {
        Utils::getValidatedString("Enter Phone Number: ", p.phone, 15);
        if (!Utils::isValidPhone(p.phone))
        {
            cout << "Invalid phone number. Must be 10-15 digits.\n";
        }
    } while (!Utils::isValidPhone(p.phone));

    Utils::getValidatedString("Enter Assigned Doctor: ", p.assignedDoctor, 50);
    p.roomNumber = Utils::getValidatedInt("Enter Room Number: ", 100, 999);
}

int PatientManager::findPatientIndex(int id) const
{
    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].patientId == id && patients[i].isActive)
        {
            return i;
        }
    }
    return -1;
}

void PatientManager::addPatient()
{
    if (patientCount >= capacity)
    {
        resizePatientArray();
    }

    int id = 1000 + patientCount + 1; // Auto-generate ID
    initializePatient(patients[patientCount], id);

    // Initialize notes for this patient
    if (patientCount >= notesCapacity)
    {
        resizeNotesArray();
    }
    patientNotes[patientCount] = nullptr;

    patientCount++;
    cout << "\nPatient added successfully! ID: " << id << endl;
}

void PatientManager::displayPatientHeader() const
{
    cout << left
         << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(5) << "Age"
         << setw(8) << "Gender"
         << setw(20) << "Disease"
         << setw(15) << "Phone"
         << setw(20) << "Doctor"
         << setw(10) << "Room"
         << endl;
    Utils::printSeparator('-', 108);
}

void PatientManager::displayPatient(const Patient &p) const
{
    cout << left
         << setw(10) << p.patientId
         << setw(20) << p.name
         << setw(5) << p.age
         << setw(8) << p.gender
         << setw(20) << p.disease
         << setw(15) << p.phone
         << setw(20) << p.assignedDoctor
         << setw(10) << p.roomNumber
         << endl;
}

void PatientManager::displayAllPatients() const
{
    if (patientCount == 0)
    {
        cout << "\nNo patients registered.\n";
        return;
    }

    Utils::printHeader("PATIENT LIST");
    displayPatientHeader();

    bool found = false;
    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].isActive)
        {
            displayPatient(patients[i]);
            found = true;

            // Display notes if any (demonstrates jagged array)
            if (patientNotes[i] != nullptr)
            {
                cout << "  Notes: ";
                NoteNode *current = patientNotes[i];
                while (current != nullptr)
                {
                    cout << current->note;
                    if (current->next != nullptr)
                        cout << " | ";
                    current = current->next;
                }
                cout << endl;
            }
        }
    }

    if (!found)
    {
        cout << "No active patients found.\n";
    }
}

void PatientManager::searchPatient() const
{
    if (patientCount == 0)
    {
        cout << "\nNo patients registered.\n";
        return;
    }

    int id = Utils::getValidatedInt("Enter Patient ID to search: ", 1000, 9999);
    int index = findPatientIndex(id);

    if (index == -1)
    {
        cout << "Patient not found.\n";
        return;
    }

    Utils::printHeader("PATIENT DETAILS");
    displayPatientHeader();
    displayPatient(patients[index]);
}

void PatientManager::updatePatient()
{
    if (patientCount == 0)
    {
        cout << "\nNo patients registered.\n";
        return;
    }

    int id = Utils::getValidatedInt("Enter Patient ID to update: ", 1000, 9999);
    int index = findPatientIndex(id);

    if (index == -1)
    {
        cout << "Patient not found.\n";
        return;
    }

    cout << "\nUpdating patient: " << patients[index].name << endl;
    cout << "Leave blank to keep current value.\n";

    char temp[100];

    cout << "Current Name: " << patients[index].name << "\nNew Name: ";
    cin.getline(temp, 100);
    if (strlen(temp) > 0)
    {
        strcpy(patients[index].name, temp);
    }

    cout << "Current Age: " << patients[index].age << "\nNew Age: ";
    int newAge;
    cin >> newAge;
    if (cin.fail())
    {
        cin.clear();
        Utils::clearInputBuffer();
    }
    else if (newAge >= 0 && newAge <= 150)
    {
        patients[index].age = newAge;
    }
    Utils::clearInputBuffer();

    // Update other fields similarly...
    cout << "Patient updated successfully!\n";
}

void PatientManager::deletePatient()
{
    if (patientCount == 0)
    {
        cout << "\nNo patients registered.\n";
        return;
    }

    int id = Utils::getValidatedInt("Enter Patient ID to delete: ", 1000, 9999);
    int index = findPatientIndex(id);

    if (index == -1)
    {
        cout << "Patient not found.\n";
        return;
    }

    cout << "Are you sure you want to delete patient: " << patients[index].name << "? (Y/N): ";
    char confirm;
    cin >> confirm;
    Utils::clearInputBuffer();

    if (toupper(confirm) == 'Y')
    {
        patients[index].isActive = false; // Soft delete
        cout << "Patient deleted successfully!\n";
    }
    else
    {
        cout << "Delete cancelled.\n";
    }
}

void PatientManager::addPatientNote()
{
    if (patientCount == 0)
    {
        cout << "\nNo patients registered.\n";
        return;
    }

    int id = Utils::getValidatedInt("Enter Patient ID to add note: ", 1000, 9999);
    int index = findPatientIndex(id);

    if (index == -1)
    {
        cout << "Patient not found.\n";
        return;
    }

    char note[200];
    Utils::getValidatedString("Enter note for patient: ", note, 200);
    addNoteToList(index, note);
    cout << "Note added successfully!\n";
}
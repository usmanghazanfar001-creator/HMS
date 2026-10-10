#include "Billing.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

BillingManager::BillingManager() {
    capacity = 5;
    bills = new Bill[capacity];
    billCount = 0;
}

BillingManager::~BillingManager() {
    delete[] bills;
}

void BillingManager::resizeBillArray() {
    capacity *= 2;
    Bill* newBills = new Bill[capacity];
    
    for (int i = 0; i < billCount; i++) {
        newBills[i] = bills[i];
    }
    
    delete[] bills;
    bills = newBills;
}

int BillingManager::findBillIndex(int id) const {
    for (int i = 0; i < billCount; i++) {
        if (bills[i].billId == id) {
            return i;
        }
    }
    return -1;
}

double BillingManager::calculateTotal(const Bill& b) const {
    return b.doctorFee + b.roomCharges + b.medicineCharges;
}

void BillingManager::initializeBill(Bill& b, int id) {
    b.billId = id;
    b.isPaid = false;
    
    b.patientId = Utils::getValidatedInt("Enter Patient ID: ", 1000, 9999);
    
    cout << "\n--- Enter Charges ---\n";
    b.doctorFee = Utils::getValidatedInt("Doctor Fee: ", 0, 10000);
    b.roomCharges = Utils::getValidatedInt("Room Charges: ", 0, 50000);
    b.medicineCharges = Utils::getValidatedInt("Medicine Charges: ", 0, 20000);
    
    b.total = calculateTotal(b);
}

void BillingManager::createBill() {
    if (billCount >= capacity) {
        resizeBillArray();
    }
    
    int id = 4000 + billCount + 1;
    initializeBill(bills[billCount], id);
    billCount++;
    
    cout << "\nBill created successfully! ID: " << id << endl;
    cout << "Total Amount: $" << fixed << setprecision(2) << bills[billCount - 1].total << endl;
}

void BillingManager::displayBill(int billId) const {
    int index = findBillIndex(billId);
    if (index == -1) {
        cout << "Bill not found.\n";
        return;
    }
    
    const Bill& b = bills[index];
    Utils::printHeader("BILL DETAILS");
    cout << "Bill ID: " << b.billId << endl;
    cout << "Patient ID: " << b.patientId << endl;
    cout << "Doctor Fee: $" << fixed << setprecision(2) << b.doctorFee << endl;
    cout << "Room Charges: $" << b.roomCharges << endl;
    cout << "Medicine Charges: $" << b.medicineCharges << endl;
    Utils::printSeparator('-', 40);
    cout << "Total: $" << b.total << endl;
    cout << "Status: " << (b.isPaid ? "PAID" : "UNPAID") << endl;
}

void BillingManager::displayAllBills() const {
    if (billCount == 0) {
        cout << "\nNo bills generated.\n";
        return;
    }
    
    Utils::printHeader("BILL LIST");
    cout << left
         << setw(10) << "Bill ID"
         << setw(15) << "Patient ID"
         << setw(15) << "Doctor Fee"
         << setw(15) << "Room Charges"
         << setw(15) << "Medicine"
         << setw(15) << "Total"
         << setw(15) << "Status"
         << endl;
    Utils::printSeparator('-', 100);
    
    for (int i = 0; i < billCount; i++) {
        const Bill& b = bills[i];
        cout << left
             << setw(10) << b.billId
             << setw(15) << b.patientId
             << setw(15) << "$" << fixed << setprecision(2) << b.doctorFee
             << setw(15) << "$" << b.roomCharges
             << setw(15) << "$" << b.medicineCharges
             << setw(15) << "$" << b.total
             << setw(15) << (b.isPaid ? "PAID" : "UNPAID")
             << endl;
    }
}

void BillingManager::markAsPaid() {
    if (billCount == 0) {
        cout << "\nNo bills found.\n";
        return;
    }
    
    int id = Utils::getValidatedInt("Enter Bill ID to mark as paid: ", 4000, 9999);
    int index = findBillIndex(id);
    
    if (index == -1) {
        cout << "Bill not found.\n";
        return;
    }
    
    if (bills[index].isPaid) {
        cout << "Bill is already paid.\n";
        return;
    }
    
    bills[index].isPaid = true;
    cout << "Bill marked as paid successfully!\n";
}

void BillingManager::generateBillSummary() const {
    if (billCount == 0) {
        cout << "\nNo bills to summarize.\n";
        return;
    }
    
    Utils::printHeader("BILLING SUMMARY");
    double totalRevenue = 0;
    int paidCount = 0;
    int unpaidCount = 0;
    
    for (int i = 0; i < billCount; i++) {
        if (bills[i].isPaid) {
            totalRevenue += bills[i].total;
            paidCount++;
        } else {
            unpaidCount++;
        }
    }
    
    cout << "Total Bills: " << billCount << endl;
    cout << "Paid Bills: " << paidCount << endl;
    cout << "Unpaid Bills: " << unpaidCount << endl;
    cout << "Total Revenue: $" << fixed << setprecision(2) << totalRevenue << endl;
    cout << "Average Bill Amount: $";
    if (billCount > 0) {
        double avg = totalRevenue / billCount;
        cout << fixed << setprecision(2) << avg << endl;
    } else {
        cout << "0.00" << endl;
    }
}
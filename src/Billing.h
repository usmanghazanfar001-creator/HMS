#pragma once
#include "Utils.h"

struct Bill {
    int billId;
    int patientId;
    double doctorFee;
    double roomCharges;
    double medicineCharges;
    double total;
    bool isPaid;
};

class BillingManager {
private:
    Bill* bills;
    int billCount;
    int capacity;
    
    void resizeBillArray();
    int findBillIndex(int id) const;
    void initializeBill(Bill& b, int id);
    
public:
    BillingManager();
    ~BillingManager();
    
    void createBill();
    void displayAllBills() const;
    void displayBill(int billId) const;
    void markAsPaid();
    double calculateTotal(const Bill& b) const;
    void generateBillSummary() const;
};
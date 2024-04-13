#include "Deposit.h"  // Include the header to get the class definition
#include <iostream>
#include <fstream>
#include <mutex>

using namespace std;

// Implement the constructor defined in the header
Deposit::Deposit(vector<string> transactionDetails, void* sharedMemory) {
    if (transactionDetails.size() < 3) {
        cerr << "Invalid transaction details for deposit." << endl;
        return;
    }

    string accountNumber = transactionDetails[0];
    double amount = stod(transactionDetails[2]);

    depositAmount(accountNumber, amount);
}

// Implement the private member function
void Deposit::depositAmount(string accNum, double amount) {
    // Assuming each Deposit object is handled by a separate process, mutex is illustrative here
    static mutex mtx;  // Made static to ensure it's shared across function calls

    // Locking to ensure thread-safe access to the file
    lock_guard<mutex> guard(mtx);

    // File path
    string filePath = "Accounts/" + accNum;
    
    // Attempt to open the account file
    fstream accountFile(filePath, ios::in | ios::out | ios::binary);
    
    if (!accountFile.is_open()) {
        cerr << "Account file " << accNum << " could not be opened for deposit." << endl;
        return;
    }
    
    double currentBalance = 0.0;
    
    // Read current balance
    accountFile >> currentBalance;
    
    // Calculate new balance
    currentBalance += amount;
    
    // Move the cursor to the beginning of the file to overwrite the balance
    accountFile.seekp(0, ios::beg);
    
    // Write the new balance
    accountFile << currentBalance;
    
    cout << "Deposit of " << amount << " to account " << accNum << " successful. New balance: " << currentBalance << endl;
    
    // Close the file
    accountFile.close();
}
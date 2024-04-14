#include "Deposit.h"  // Include the header to get the class definition
#include <iostream>
#include <fstream>
#include <mutex>
#include <vector>
#include <string>
#include <iomanip> 

using namespace std;
mutex Deposit::mtx;

Deposit::Deposit(vector<string> transactionDetails, void* sharedMemory) {
    if (transactionDetails.size() < 3) {
        cerr << "Invalid transaction details for deposit." << endl;
        return;
    }

    string accountNumber = transactionDetails[0];
    double amount = stod(transactionDetails[2]);

    depositAmount(accountNumber, amount);
}

void Deposit::depositAmount(string accNum, double amount) {
    lock_guard<mutex> guard(mtx);  // Ensures thread-safe access

    string filePath = "Accounts/" + accNum;
    fstream accountFile(filePath, ios::in | ios::out);

    if (!accountFile.is_open()) {
        cerr << "Account file " << accNum << " could not be opened for deposit." << endl;
        return;
    }

    double currentBalance = 0.0;
    accountFile >> currentBalance;

    // Clear errors and prepare for writing
    accountFile.clear(); 
    accountFile.seekp(0, ios::beg);

    currentBalance += amount;

    // Write the new balance with fixed precision
    accountFile << fixed << setprecision(2) << currentBalance;
    accountFile.flush();  // Flush the changes immediately

    if (accountFile.fail()) {
        cerr << "Failed to write the new balance to the account file " << accNum << "." << endl;
    } else {
        cout << "Deposit of " << amount << " to account " << accNum << " successful. New balance: " << currentBalance << endl;
    }

    accountFile.close();  // Ensure the file is closed after operations
}

#include "Inquiry.h"
#include <iostream>
#include <fstream>

using namespace std;

Inquiry::Inquiry(const vector<string>& transactionDetails, void* sharedMemory) {
    if (transactionDetails.size() < 1) {
        cerr << "Invalid transaction details for inquiry." << endl;
        return;
    }

    string accountNumber = transactionDetails[0];
    inquireBalance(accountNumber); // Now correctly declared in Inquiry.h
}

void Inquiry::inquireBalance(const string accNum) {
    string filePath = "Accounts/" + accNum;

    ifstream accountFile(filePath);
    if (!accountFile.is_open()) {
        cerr << "Could not open account file for " << accNum << " to inquire balance." << endl;
        return;
    }

    double balance;
    accountFile >> balance;

    cout << "Account " << accNum << " has balance: $" << balance << endl;
}

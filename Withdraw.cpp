// Author: Katie Pinell
// Date: 4/14/2024
// Description: This file withdraws a given amount from an account.

#include "Withdraw.h"
#include <iostream>
#include <fstream>
#include <mutex>

using namespace std;

Withdraw::Withdraw(vector<string> transactionDetails, void* sharedMemory) {
    if (transactionDetails.size() < 2) {
        cerr << "Invalid transaction details for withdrawal." << endl;
        return;
    }

    string withdrawAccount = transactionDetails[0];
    double amount = stod(transactionDetails[2]);

    WithdrawAmount(withdrawAccount, amount);
}

void Withdraw::WithdrawAmount(string withdrawAccount, double amount) {
    static mutex mtx;
    lock_guard<mutex> guard(mtx);

    string filePath = "Accounts/" + withdrawAccount;
    fstream withdrawAccountFile(filePath, ios::in | ios::out | ios::binary);

    if (!withdrawAccountFile.is_open()) {
        cerr << "Account file " << withdrawAccount << " could not be opened for withdraw." << endl;
        return;
    }

    double withdrawAccountBalance = 0.0;
    withdrawAccountFile >> withdrawAccountBalance;

    if (withdrawAccountBalance < amount) {
        withdrawAccountFile.close();
        cerr << withdrawAccount << " has insufficient funds for withdrawal." << endl;
        return;
    }
    else {
        withdrawAccountBalance -= amount;
        withdrawAccountFile.seekp(0, ios::beg);
        withdrawAccountFile << withdrawAccountBalance;
    }

    cout << "Withdrawal of " << amount << " from account " << withdrawAccount << " successful." << endl;
    cout << "New balance of " << withdrawAccount << ": " << withdrawAccountBalance << endl;

    withdrawAccountFile.close();
}
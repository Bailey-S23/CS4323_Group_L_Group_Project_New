// Author: Caleb Sullard
// Date: 4/14/2024
// Description: This file moves money from account to another account

#include <iostream>
#include <fstream>
#include <mutex>
#include "TransferTo.h"


using namespace std;

TransferTo::TransferTo(vector<string> transactionDetails, void *sharedMemory)
{
    if (transactionDetails.size() < 4)
    {
        cerr << "Invalid transaction details for transfer." << endl;
        return;
    }

    string withdrawAccount = transactionDetails[0];
    double amount = stod(transactionDetails[2]);
    string depositAccount = transactionDetails[3];

    transferAmount(withdrawAccount, amount, depositAccount);
}

void TransferTo::transferAmount(string withdrawAccount, double amount, string depositAccount)
{

    static mutex mtx;
    lock_guard<mutex> guard(mtx);

    string filePath = "Accounts/" + withdrawAccount;
    fstream withdrawAccountFile(filePath, ios::in | ios::out | ios::binary);
    if (!withdrawAccountFile.is_open())
    {
        cerr << "Account " << withdrawAccount << " could not be opened for withdraw." << endl;
        return;
    }

    fstream depositAccountFile(filePath, ios::in | ios::out | ios::binary);
    if (!depositAccountFile.is_open())
    {
        withdrawAccountFile.close();
        cerr << "Account " << depositAccount << " could not be opened for deposit." << endl;
        return;
    }

    double withdrawAccountBalance = 0.0;
    withdrawAccountFile >> withdrawAccountBalance;

    double depositAccountBalance = 0.0;
    depositAccountFile >> depositAccountBalance;

    if (withdrawAccountBalance < amount)
    {
        withdrawAccountFile.close();
        depositAccountFile.close();
        cerr << withdrawAccount << " has insufficent funds for withdrawal." << endl;
        return;
    }
    else
    {
        withdrawAccountBalance -= amount;
        depositAccountBalance += amount;
        withdrawAccountFile.seekp(0, ios::beg);
        depositAccountFile.seekp(0, ios::beg);
        withdrawAccountFile << withdrawAccountBalance;
        depositAccountFile << depositAccountBalance;
    }

    cout << "Transfer of " << amount << " from account " << withdrawAccount << " to account " << depositAccount << " successful." << endl;
    cout << "New balance of " << withdrawAccount << ": " << withdrawAccountBalance << endl;
    cout << "New balance of " << depositAccount << ": " << depositAccountBalance << endl;

    withdrawAccountFile.close();
    depositAccountFile.close();
}
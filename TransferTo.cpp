// Group L
// Caleb Sullard
// caleb.sullard@okstate.edu
// 4/21/2024
// Description: This file moves money from account to another account

#include "TransferTo.h"  // Include the header to get the class
#include <iostream>
#include <fstream>
#include <mutex>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <unistd.h>

using namespace std;
mutex TransferTo::mtx;

TransferTo::TransferTo(vector<string> transactionDetails, void* sharedMemory) {
    // If input does not have all necessary values:
    // Account to withdraw from, amount to transfer, account to deposit to
    // Then process will not execute
    if (transactionDetails.size() < 4)
    {
        cerr << "Invalid transaction details for transfer." << endl;
        return;
    }
    else
    {
        // A0000000 Transfer 40 A0000001
        //     0       1      2     3
        string withdrawAccount = transactionDetails[0];
        double amount = stod(transactionDetails[2]);
        string depositAccount = transactionDetails[3];
        
        withdrawAmount(withdrawAccount, amount, depositAccount, sharedMemory); // This is the start of the transfer process
    }
}

string TransferTo::returnCurrentTimeAndDate()
{
    auto currentTime = chrono::system_clock::now();
    auto currentTime_t = chrono::system_clock::to_time_t(currentTime);

    stringstream ss;
    ss << std::put_time(localtime(&currentTime_t), "%Y-%m-%d %X");
    return ss.str();
}

// This method withdraws the specified amount of money from the first account
void TransferTo::withdrawAmount(string withdrawAccount, double amount, string depositAccount, void* sharedMemory)
{
    mtx.lock();
    string filePath = "Accounts/" + withdrawAccount;
    fstream withdrawAccountFile(filePath, ios::in | ios::out);

    if (!withdrawAccountFile.is_open())
    {
        cerr << "Account file " << withdrawAccount << " could not be opened for withdrawing." << endl;

        mtx.unlock();

        return;
    }

    double currentBalance = 0.0;
    withdrawAccountFile >> currentBalance; // currentBalance now represents the value of the account

    // If account does not have enough money, then we cannot transfer any money
    if (currentBalance < amount)
    {
        // Log the failed process
        string time = returnCurrentTimeAndDate();
        string writeToFile = "Transaction type: Transfer " + withdrawAccount + " " + to_string(amount) + " " + depositAccount + " FAILURE " + time + "\n";
        char *readInCreate = (char *)sharedMemory;
        char *writeInLog = writeToFile.data();
        strcat((char *)sharedMemory, writeInLog);

        cerr << "Account file " << withdrawAccount << " has insufficient funds." << endl;

        mtx.unlock();

        return;
    }
    // If the account does have enough money, then we take that money out and call the deposit method
    else
    {
        withdrawAccountFile.clear();
        withdrawAccountFile.seekp(0, ios::beg);

        currentBalance -= amount; // Subtract the specified amount from the account

        withdrawAccountFile << fixed << setprecision(2) << currentBalance;
        withdrawAccountFile.flush();
        withdrawAccountFile.close();

        depositAmount(withdrawAccount, amount, depositAccount, sharedMemory); // Call deposit
    }
}

// This method deposits the specified amount of money into the second account
void TransferTo::depositAmount(string withdrawAccount, double amount, string depositAccount, void* sharedMemory)
{
    string filePath = "Accounts/" + depositAccount;
    fstream depositAccountFile(filePath, ios::in | ios::out);

    if (!depositAccountFile.is_open())
    {
        // Log the failed process
        string time = returnCurrentTimeAndDate();
        string writeToFile = "Transaction type: Transfer " + withdrawAccount + " " + to_string(amount) + " " + depositAccount + " " + " FAILURE " + time + "\n";
        cerr << "Account file " << depositAccount << " could not be opened for deposit." << endl;
        
        mtx.unlock();

        return;
    }
    else
    {
        double currentBalance = 0.0;
        depositAccountFile >> currentBalance;

        depositAccountFile.clear(); 
        depositAccountFile.seekp(0, ios::beg);

        currentBalance += amount; // Add the specified amount to the account

        depositAccountFile << fixed << setprecision(2) << currentBalance;
        depositAccountFile.flush();

        // Log the successful process
        string time = returnCurrentTimeAndDate();
        string writeToFile = "Transaction type: Transfer " + withdrawAccount + " " + to_string(amount) + " " + depositAccount + " " + " SUCCESS " + time + "\n";
        char *writeInLog = writeToFile.data();
        strcat((char *)sharedMemory, writeInLog);

        mtx.unlock();
    }
    depositAccountFile.close();
}
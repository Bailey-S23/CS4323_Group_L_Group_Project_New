/* Author Name: Zach  Wilson
    Email: stealth.wilson@okstate.edu
    Date: 04/14/2024
    Deposit function to deposit money into account*/

#include "Deposit.h" // Include the header to get the class definition
#include <iostream>
#include <fstream>
#include <mutex>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

mutex Deposit::mtx;

Deposit::Deposit(vector<string> transactionDetails, void *sharedMemory)
{
    if (transactionDetails.size() < 3)
    {
        cerr << "Invalid transaction details for deposit." << endl;
        return;
    }

    string accountNumber = transactionDetails[0];
    double amount = stod(transactionDetails[2]);

    depositAmount(accountNumber, amount, sharedMemory);
}

/************************************* BELOW THIS LINE ADDED FOR SHARED MEMORY *************************************/
string Deposit::returnCurrentTimeAndDate()
{
    auto currentTime = chrono::system_clock::now();
    auto currentTime_t = chrono::system_clock::to_time_t(currentTime);

    stringstream sstream;
    sstream << std::put_time(localtime(&currentTime_t), "%Y-%m-%d %X");
    return sstream.str();
}
/************************************* ABOVE THIS LINE ADDED FOR SHARED MEMORY *************************************/

void Deposit::depositAmount(string accNum, double amount, void *sharedMemory)
{
    lock_guard<mutex> guard(mtx); // Ensures thread-safe access

    string filePath = "Accounts/" + accNum;
    fstream accountFile(filePath, ios::in | ios::out);

    if (!accountFile.is_open())
    {
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
    accountFile.flush(); // Flush the changes immediately

    if (accountFile.fail())
    {
        cerr << "Failed to write the new balance to the account file " << accNum << "." << endl;

        /************************************* BELOW THIS LINE ADDED FOR SHARED MEMORY *************************************/
        string depositLog = to_string(amount);
        string time = returnCurrentTimeAndDate();
        string writeToFile = "Transaction type: Deposit " + accNum + " " + depositLog + " FAILURE " + time + "\n";
        char *readInCreate = (char *)sharedMemory;
        char *writeInLog = writeToFile.data();
        strcat((char *)sharedMemory, writeInLog);
        /************************************* ABOVE THIS LINE ADDED FOR SHARED MEMORY *************************************/
    }
    else
    {
        cout << "Deposit of " << amount << " to account " << accNum << " successful. New balance: " << currentBalance << endl;

        /************************************* BELOW THIS LINE ADDED FOR SHARED MEMORY *************************************/
        string depositLog = to_string(amount);
        string time = returnCurrentTimeAndDate();
        string writeToFile = "Transaction type: Deposit " + accNum + " " + depositLog + " SUCCESS " + time + "\n";
        char *writeInLog = writeToFile.data();
        strcat((char *)sharedMemory, writeInLog);
        /************************************* ABOVE THIS LINE ADDED FOR SHARED MEMORY *************************************/
    }

    accountFile.close(); // Ensure the file is closed after operations
}

/* Author Name: Katie Pinell
    Email: katie.pinell@okstate.edu
    Date: 04/21/2024
    Withdraw function to withdraw money into account*/

#include "Withdraw.h"
#include <iostream>
#include <fstream>
#include <mutex>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

mutex Withdraw::mtx;

Withdraw::Withdraw(vector<string> transactionDetails, void *sharedMemory)
{
    if (transactionDetails.size() < 3)
    {
        cerr << "Invalid transaction details for Withdraw." << endl;
        return;
    }

    string accountNumber = transactionDetails[0];
    double amount = stod(transactionDetails[2]);

    WithdrawAmount(accountNumber, amount, sharedMemory);
}

/************************************* BELOW THIS LINE ADDED FOR SHARED MEMORY *************************************/
string Withdraw::returnCurrentTimeAndDate()
{
    auto currentTime = chrono::system_clock::now();
    auto currentTime_t = chrono::system_clock::to_time_t(currentTime);

    stringstream ss;
    ss << std::put_time(localtime(&currentTime_t), "%Y-%m-%d %X");
    return ss.str();
}
/************************************* ABOVE THIS LINE ADDED FOR SHARED MEMORY *************************************/

void Withdraw::WithdrawAmount(string accNum, double amount, void *sharedMemory)
{
    lock_guard<mutex> guard(mtx);

    string filePath = "Accounts/" + accNum;
    fstream accountFile(filePath, ios::in | ios::out);

    if (!accountFile.is_open())
    {
        cerr << "Account file " << accNum << " could not be opened for Withdraw." << endl;

        /************************************* BELOW THIS LINE ADDED FOR SHARED MEMORY *************************************/
        string WithdrawLog = to_string(amount);
        string time = returnCurrentTimeAndDate();
        string writeToFile = "Transaction type: Withdraw " + accNum + " " + WithdrawLog + " FAILURE " + time + "\n";
        char *readInCreate = (char *)sharedMemory;
        char *writeInLog = writeToFile.data();
        strcat((char *)sharedMemory, writeInLog);
        /************************************* ABOVE THIS LINE ADDED FOR SHARED MEMORY *************************************/

        return;
    }

    double currentBalance = 0.0;
    accountFile >> currentBalance;

    accountFile.clear();
    accountFile.seekp(0, ios::beg);

    currentBalance -= amount;

    accountFile << fixed << setprecision(2) << currentBalance;
    accountFile.flush();

    string WithdrawLog = to_string(amount);

    if (accountFile.fail())
    {
        /************************************* BELOW THIS LINE ADDED FOR SHARED MEMORY *************************************/
        string time = returnCurrentTimeAndDate();
        string writeToFile = "Transaction type: Withdraw " + accNum + " " + WithdrawLog + " FAILURE " + time + "\n";
        char *readInCreate = (char *)sharedMemory;
        char *writeInLog = writeToFile.data();
        strcat((char *)sharedMemory, writeInLog);
        /************************************* ABOVE THIS LINE ADDED FOR SHARED MEMORY *************************************/
    }
    else
    {
        /************************************* ABOVE THIS LINE ADDED FOR SHARED MEMORY *************************************/
        string time = returnCurrentTimeAndDate();
        string writeToFile = "Transaction type: Withdraw " + accNum + " " + WithdrawLog + " SUCCESS " + time + "\n";
        char *writeInLog = writeToFile.data();
        strcat((char *)sharedMemory, writeInLog);
        /************************************* ABOVE THIS LINE ADDED FOR SHARED MEMORY *************************************/
    }

    accountFile.close();
}

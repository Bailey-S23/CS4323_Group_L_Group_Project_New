/* Author Name: Zach  Wilson
    Email: stealth.wilson@okstate.edu
    Date: 04/14/2024
    Inquire function to read current value of acccounts*/

#include "Inquiry.h"
#include <iostream>
#include <fstream>

using namespace std;

Inquiry::Inquiry(const vector<string> &transactionDetails, void *sharedMemory)
{
    if (transactionDetails.size() < 1)
    {
        cerr << "Invalid transaction details for inquiry." << endl;
        return;
    }

    string accountNumber = transactionDetails[0];
    inquireBalance(accountNumber, sharedMemory); // Now correctly declared in Inquiry.h
}

/************************************* BELOW THIS LINE ADDED FOR SHARED MEMORY *************************************/
string Inquiry::returnCurrentTimeAndDate()
{
    auto currentTime = chrono::system_clock::now();
    auto currentTime_t = chrono::system_clock::to_time_t(currentTime);

    stringstream sstream;
    sstream << std::put_time(localtime(&currentTime_t), "%Y-%m-%d %X");
    return sstream.str();
}
/************************************* ABOVE THIS LINE ADDED FOR SHARED MEMORY *************************************/

void Inquiry::inquireBalance(const string accNum, void *sharedMemory)
{
    string filePath = "Accounts/" + accNum;

    ifstream accountFile(filePath);
    if (!accountFile.is_open())
    {
        cerr << "Could not open account file for " << accNum << " to inquire balance." << endl;

        /************************************* BELOW THIS LINE ADDED FOR SHARED MEMORY *************************************/
        string time = returnCurrentTimeAndDate();
        string writeToFile = "Transaction type: Inquiry " + accNum + " FAILURE " + time + "\n";
        char *writeInLog = writeToFile.data();
        strcat((char *)sharedMemory, writeInLog);
        /************************************* ABOVE THIS LINE ADDED FOR SHARED MEMORY *************************************/

        return;
    }
    else
    {
        double balance;
        accountFile >> balance;

        /************************************* BELOW THIS LINE ADDED FOR SHARED MEMORY *************************************/
        string balanceForLog = to_string(balance);
        string time = returnCurrentTimeAndDate();
        string writeToFile = "Transaction type: Inquiry " + accNum + " " + balanceForLog + " SUCCESS " + time + "\n";
        char *writeInLog = writeToFile.data();
        strcat((char *)sharedMemory, writeInLog);
        /************************************* ABOVE THIS LINE ADDED FOR SHARED MEMORY *************************************/

        cout << "Account " << accNum << " has balance: $" << balance << endl;
    }
}

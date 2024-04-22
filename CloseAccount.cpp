// Author: Katie Pinell
// Date: 4/14/2024
// Description: This file closes an account by deleting the corresponding file.

#include "CloseAccount.h"
#include <iostream>
#include <unistd.h>
#include <cstdio>

using namespace std;




/************************************* BELOW THIS LINE ADDED FOR SHARED MEMORY *************************************/
string CloseAccount::returnCurrentTimeAndDate()
{
    auto currentTime = chrono::system_clock::now();
    auto currentTime_t = chrono::system_clock::to_time_t(currentTime);

    stringstream sstream;
    sstream << std::put_time(localtime(&currentTime_t), "%Y-%m-%d %X");
    return sstream.str();
}
/************************************* ABOVE THIS LINE ADDED FOR SHARED MEMORY *************************************/




CloseAccount::CloseAccount(vector<string> accountInfo, void* sharedMemory, Monitor& monitor)
{
    monitor.acquire();
    // Get the account name from the account info
    string accName = accountInfo[0];

    // The file path is Accounts/account
    string filePath = "Accounts/" + accName;

    // Delete the account file and store the outcome
    int accountDeleted = remove(filePath.c_str());

    // Check if there was an error deleting the account
    if (accountDeleted != 0)
    {
        cout << "Error deleting account: " + accName << endl;


        /************************************* BELOW THIS LINE ADDED FOR SHARED MEMORY *************************************/
        string time = returnCurrentTimeAndDate();
        string writeToFile = "Transaction type: Close " + accName +  + " FAILURE " + time + "\n";
        char *readInCreate = (char *)sharedMemory;
        char *writeInLog = writeToFile.data();
        strcat((char *)sharedMemory, writeInLog);
        /************************************* ABOVE THIS LINE ADDED FOR SHARED MEMORY *************************************/
    }
    else // The account was successfully deleted
    {
        cout << "Account deleted: " + accName << endl;


        /************************************* BELOW THIS LINE ADDED FOR SHARED MEMORY *************************************/
        string time = returnCurrentTimeAndDate();
        string writeToFile = "Transaction type: Close " + accName +  + " SUCCESS " + time + "\n";
        char *readInCreate = (char *)sharedMemory;
        char *writeInLog = writeToFile.data();
        strcat((char *)sharedMemory, writeInLog);
        /************************************* ABOVE THIS LINE ADDED FOR SHARED MEMORY *************************************/

    }
    monitor.release();
}
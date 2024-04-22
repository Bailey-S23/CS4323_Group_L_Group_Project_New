// Author: Bailey Schultz

#include "CreateAccount.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fstream>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

bool CreateAccount::accExists(string accountNumber)
{

    ifstream file;

    file.open("Accounts/" + accountNumber);

    bool exists = false;

    if (file)
    {
        exists = true;
    }
    else
    {
        exists = false;
    }

    return exists;
}
/************************************* BELOW THIS LINE ADDED FOR SHARED MEMORY *************************************/
string CreateAccount::returnCurrentTimeAndDate()
{
    auto currentTime = chrono::system_clock::now();
    auto currentTime_t = chrono::system_clock::to_time_t(currentTime);
    stringstream sstream;
    sstream << std::put_time(localtime(&currentTime_t), "%Y-%m-%d %X");
    return sstream.str();
}
/************************************* ABOVE THIS LINE ADDED FOR SHARED MEMORY *************************************/

// Constructor that creates new account files
CreateAccount::CreateAccount(vector<string> accountInfo, void *sharedMemory)
{
    accBalance = stoi(accountInfo[2].data());
    string accName = accountInfo[0];

    if (accBalance >= 0)
    {

        string temp = "Accounts/" + accountInfo[0];

        struct stat sb;

        ofstream outfile("Accounts/" + accName);
        outfile << accBalance;

        outfile.close();
    }

    //------------------------------------------

    if (accExists(accountInfo[0]))
    {

        cout << "Account " + accName + " Created" << endl;

        /************************************* BELOW THIS LINE ADDED FOR SHARED MEMORY *************************************/
        string time = returnCurrentTimeAndDate();
        string writeToFile = "Transaction type: Create " + accName + " " + accountInfo[2] + " SUCCESS " + time + "\n";
        char *writeInLog = writeToFile.data();
        strcat((char *)sharedMemory, writeInLog);
        /************************************* ABOVE THIS LINE ADDED FOR SHARED MEMORY *************************************/
    }
    else
    {
        cout << "Account " + accName + " Failed to be Created" << endl;

        /************************************* BELOW THIS LINE ADDED FOR SHARED MEMORY *************************************/
        string time = returnCurrentTimeAndDate();
        string writeToFile = "Transaction type: Create " + accName + " " + accountInfo[2] + " FAILURE " + time + "\n";
        char *readInCreate = (char *)sharedMemory;
        char *writeInLog = writeToFile.data();
        strcat((char *)sharedMemory, writeInLog);
        /************************************* ABOVE THIS LINE ADDED FOR SHARED MEMORY *************************************/
    }
}

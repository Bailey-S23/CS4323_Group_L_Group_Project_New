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
        cout << "File " + accountNumber + " exists" << endl;
        exists = true;
    }
    else
    {
        cout << "File " + accountNumber + " does not exist" << endl;

        exists = false;
    }

    return exists;
}

string CreateAccount::returnCurrentTimeAndDate()
{
    auto currentTime = chrono::system_clock::now();
    auto currentTime_t = chrono::system_clock::to_time_t(currentTime);

    stringstream sstream;
    sstream << std::put_time(localtime(&currentTime_t), "%Y-%m-%d %X");
    return sstream.str();
}

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
        string time = returnCurrentTimeAndDate();
        string writeToFile = "Transaction type: Create " + accName + " " + accountInfo[2] + " SUCCESS " + time + "\n";
        char *writeInLog = writeToFile.data();
        strcat((char *)sharedMemory, writeInLog);
    }
    else
    {
        string time = returnCurrentTimeAndDate();
        string writeToFile = "Transaction type: Create " + accName + " " + accountInfo[2] + " FAILURE " + time+ "\n";

        char *readInCreate = (char *)sharedMemory;

        char *writeInLog = writeToFile.data();

        strcat((char *)sharedMemory, writeInLog);
    }
}

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
#include "Monitor.h"

// this function checks to see if an account currently exists
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
// This function creates a string out of the current time and date. It is used in all of the transaction functions
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
CreateAccount::CreateAccount(vector<string> accountInfo, void *sharedMemory, Monitor &monitor)
{
    monitor.acquire();
    // get data from vector
    accBalance = stoi(accountInfo[2].data());
    string accName = accountInfo[0];

    // check if account balance is at least 0
    if (accBalance >= 0)
    {

        // get location to open the file and add the name of the account
        string temp = "Accounts/" + accountInfo[0];

        // create file and place balance inside it
        ofstream outfile("Accounts/" + accName);
        outfile << accBalance;

        // close the file
        outfile.close();
    }

    // if the account exists, print to console and to shared memory log
    if (accExists(accountInfo[0]))
    {
        // message to console that account was created
        cout << "Account " + accName + " Created" << endl;

        /************************************* BELOW THIS LINE ADDED FOR SHARED MEMORY *************************************/
        // get the time
        string time = returnCurrentTimeAndDate();
        // prepare string to write to log
        string writeToFile = "Transaction type: Create " + accName + " " + accountInfo[2] + " SUCCESS " + time + "\n";
        // convert to char* to write to log
        char *writeInLog = writeToFile.data();
        // concatenate the message into the shared memory
        strcat((char *)sharedMemory, writeInLog);
        /************************************* ABOVE THIS LINE ADDED FOR SHARED MEMORY *************************************/
    }
    // if the account does not exist, print to console and to shared memory log
    else
    {
        // message to console that account was not created
        cout << "Account " + accName + " Failed to be Created" << endl;

        /************************************* BELOW THIS LINE ADDED FOR SHARED MEMORY *************************************/
        // get the time
        string time = returnCurrentTimeAndDate();
        // prepare string to write to log
        string writeToFile = "Transaction type: Create " + accName + " " + accountInfo[2] + " FAILURE " + time + "\n";
        // convert to char* to write to log
        char *writeInLog = writeToFile.data();
        // concatenate the message into the shared memory
        strcat((char *)sharedMemory, writeInLog);
        /************************************* ABOVE THIS LINE ADDED FOR SHARED MEMORY *************************************/
    }
    monitor.release();
}

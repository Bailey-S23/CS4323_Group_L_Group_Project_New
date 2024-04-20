// Group L
// Main Author: Bailey Schultz
// Co Authors: Zach Wilson, Calleb Sullard, Katie Pinell

#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
#include "CreateAccount.h"
#include "CreateAccount.cpp"
#include <mutex>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include "UserAccounts.h"
#include "UserAccounts.cpp"
#include "memoryModule.h"
#include "memoryModule.cpp"
#include "Monitor.h"
TransactionMonitor monitor; // Global monitor instance

using namespace std;

#define PAGESIZE 4096

// This function breaks down lines of file and returns a vector holding each piece as an element
vector<string> tokenize(string lineOfFile)
{
    stringstream sstream(lineOfFile);
    string singleString;
    vector<string> partsOfLine;

    while (sstream >> singleString)
    {
        partsOfLine.push_back(singleString);
    }

    return partsOfLine;
}

// This function checks to see if a file exists or not
bool accountExists(string accNum)
{

    ifstream file;

    file.open("Accounts/" + accNum);

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

int checkForAccountInVector(vector<UserAccounts> accountVector, string accountName)
{
    for (int i = 0; i < accountVector.size(); i++)
    {
        if (accountName == accountVector[i].accountNumber)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
   
    monitor.logTransaction("Sample log entry 1");
    monitor.logTransaction("Sample log entry 2");
    
    monitor.printLogQueue();  // This will print all entries in the queue

    // This block of code creates the directory "Accounts" if it does not exist already
    //.................................................................................
    const char *dir = "Accounts";
    struct stat sb;
    if (stat(dir, &sb) == 0)
    {
        cout << "Directory exists, continuing" << endl;
    }
    else
    {
        if (mkdir(dir, 0777) == -1)
        {
            cerr << "Error :  " << strerror(errno) << endl;
        }
        else
        {
            cout << "Directory created" << endl;
        }
    }
    //.................................................................................

    // used to read file
    string fileToRead = "InputFile";
    ifstream inputFile(fileToRead);
    string lineOfFile;

    int numOfUsers;

    vector<UserAccounts> accountVector;

    // if file is open
    if (inputFile.is_open())
    {
        // Get int value at top of input file
        cout << "Start" << endl;

        getline(inputFile, lineOfFile);

        numOfUsers = stoi(lineOfFile);

        // read lines of file one at a time until they are all read
        while (getline(inputFile, lineOfFile))
        {

            // take each line of the file break it into its pieces
            vector<string> partsOfLine;
            partsOfLine = tokenize(lineOfFile);

            // Create accounts and add operations for each account into vector associated with that account
            if (accountVector.empty() == true)
            {
                UserAccounts newAccount = UserAccounts(partsOfLine[0]);
                newAccount.operationVector.push_back(partsOfLine);
                newAccount.operations.push_back(lineOfFile);
                accountVector.push_back(newAccount);
            }
            else if (checkForAccountInVector(accountVector, partsOfLine[0]) != -1)
            {
                int i = checkForAccountInVector(accountVector, partsOfLine[0]);

                accountVector[i].operationVector.push_back(partsOfLine);
                accountVector[i].operations.push_back(lineOfFile);
            }
            else
            {
                UserAccounts newAccount2 = UserAccounts(partsOfLine[0]);
                newAccount2.operationVector.push_back(partsOfLine);
                newAccount2.operations.push_back(lineOfFile);
                accountVector.push_back(newAccount2);
            }
        }
    }

// Pass user accounts and number of user accounts to memoryModule
    memoryModule memory = memoryModule(accountVector, numOfUsers);

    /*
        for (int i = 0; i < accountVector.size(); i++)
        {
            for (int k = 0; k < accountVector[i].operationVector.size(); k++)
            {
                vector<string> line = accountVector[i].operationVector[k];
                for (int j = 0; j < line.size(); j++)
                {
                    cout << line[j] << endl;
                }
            }
            cout << "----" << endl;
        }

        cout << "===============================" << endl;

        for (int i = 0; i < accountVector.size(); i++)
        {
            for (int k = 0; k < accountVector[i].operations.size(); k++)
            {
                string line = accountVector[i].operations[k];
                cout << line << endl;
            }
        }

        */
    monitor.printLogQueue();
    return 0;
}

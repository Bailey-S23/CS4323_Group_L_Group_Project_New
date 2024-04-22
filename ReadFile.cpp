#include "ReadFile.h"
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
#include "SharedMemoryMod.h"
#include "ProcessModule.h"
#include "ProcessModule.cpp"

using namespace std;

// This function breaks down lines of file and returns a vector holding each piece as an element
vector<string> ReadFile::tokenize(string lineOfFile)
{
    stringstream sstream(lineOfFile); // stream string to split lines of file into single pieces of line
    string singleString;              // string to hold single piece of line
    vector<string> partsOfLine;       // vector to hold all individual pieces of line

    // loop through entire line, placing each piece in the vector
    while (sstream >> singleString)
    {
        partsOfLine.push_back(singleString);
    }

    // return the vector containing each piece of the line
    return partsOfLine;
}

// This function checks to see if a file exists or not, returns true if exists, false otherwise
bool ReadFile::accountExists(string accNum)
{

    // ifsteam to open file
    ifstream file;

    // attempt to open file
    file.open("Accounts/" + accNum);

    // bool returned
    bool exists = false;

    if (file)
    {
        // set true if file exists
        exists = true;
    }
    else
    {
        // false otherwise
        exists = false;
    }

    // return if file exists
    return exists;
}

// This function checks for an account in the vector that holds all user accounts from input
int ReadFile::checkForAccountInVector(vector<UserAccounts> accountVector, string accountName)
{
    // loop through current account vector
    for (int i = 0; i < accountVector.size(); i++)
    {
        // if name is found in vector, return location of account in vector
        if (accountName == accountVector[i].accountNumber)
        {
            return i;
        }
    }
    // no account found, return -1
    return -1;
}

// constructor to read the input file and create an array of users and their respective transactions
ReadFile::ReadFile(string fileToRead)
{

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

    // ifstream and string to read file, attempt to open file passed from driver
    ifstream inputFile(fileToRead);
    string lineOfFile;

    // holds number of users from top of input file
    int numOfUsers;

    // vector to hold all user accounts
    vector<UserAccounts> accountVector;

    // if file is open
    if (inputFile.is_open())
    {
        // indicate when file reading begins
        cout << "Begin reading file" << endl;

        // Get int value at top of input file
        getline(inputFile, lineOfFile);

        // hold number of accounts expected
        numOfUsers = stoi(lineOfFile);

        // read lines of file one at a time until they are all read
        while (getline(inputFile, lineOfFile))
        {

            // take each line of the file break it into its pieces using helper function tokenize
            vector<string> partsOfLine;
            partsOfLine = tokenize(lineOfFile);

            // if vector is empty, place first account in vector
            if (accountVector.empty() == true)
            {

                UserAccounts newAccount = UserAccounts(partsOfLine[0]); // create new account
                newAccount.operationVector.push_back(partsOfLine);      // add operations to vector of vectors *THIS IS NEVER USED*
                newAccount.operations.push_back(lineOfFile);            // add transaction to vector attached to user account
                accountVector.push_back(newAccount);                    // add new user to account vector
            }
            // if user has account in account vector add transactions to that accounts operations vector
            else if (checkForAccountInVector(accountVector, partsOfLine[0]) != -1)
            {
                int i = checkForAccountInVector(accountVector, partsOfLine[0]); // access correct account in UserAccounts vector
                accountVector[i].operationVector.push_back(partsOfLine);        // *NEVER USED*
                accountVector[i].operations.push_back(lineOfFile);              // add transaction to vector attached to user account
            }
            // vector is not empty, but user account does not exist
            else
            {
                UserAccounts newAccount2 = UserAccounts(partsOfLine[0]); // create new account
                newAccount2.operationVector.push_back(partsOfLine);      // *NEVER USED**
                newAccount2.operations.push_back(lineOfFile);            // add transaction to vector attached to user account
                accountVector.push_back(newAccount2);                    // add new user to account vector
            }
        }
    }
    // Opening file failed, exit the program
    else
    {
        cerr << "Failed to open file: " << fileToRead << endl;
        exit(-1);
    }

    // Pass user accounts and number of user accounts to memoryModule
    ProcessModule processes = ProcessModule(accountVector, numOfUsers);
}
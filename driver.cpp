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

using namespace std;

#define PAGESIZE 4096

void *createSharedMemory()
{
    return mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, -1, 0);
}

// This function breaks down lines of file and returns a vector holding each piece as an element
vector<string> tokenizer(string lineOfFile)
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
        cout << "File " + accNum + " exists" << endl;
        exists = true;
    }
    else
    {
        exists = false;
    }

    return exists;
}

int main()
{

    // Create pointer to shared memory
    void *sharedMemory = createSharedMemory();

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

    // if file is open
    if (inputFile.is_open())
    {
        // Get int value at top of input file
        getline(inputFile, lineOfFile);

        // read lines of file one at a time until they are all read
        while (getline(inputFile, lineOfFile))
        {

            // take each line of the file break it into its pieces to do stuff with them
            vector<string> partsOfLine;
            partsOfLine = tokenizer(lineOfFile);


            /********************************************************************************
            code needs additional statements to handle input for files that already exist.
            Existing code only handles account numbers that it has not previously encountered.
            This code will be passed to the other classes in the same way, as a vector containing
            the individual pieces of a line and a pointer to the shared memory
            *********************************************************************************/


            // check if the file (account) exists
            if (!accountExists(partsOfLine[0]) && fork() == 0)
            {

                // if the account does not exist, create a child process that does stuff with the new account number
                int command = 7;

                // Switch statment below if statements does not work with strings
                // int command is set using if statements based on withdraw/create etc to use in switch block
                if (partsOfLine[1] == "Withdraw")
                {
                    command = 0;
                }
                if (partsOfLine[1] == "Create")
                {
                    command = 1;
                }
                if (partsOfLine[1] == "Inquiry")
                {
                    command = 2;
                }
                if (partsOfLine[1] == "Deposit")
                {
                    command = 3;
                }
                if (partsOfLine[1] == "Transfer")
                {
                    command = 4;
                }
                if (partsOfLine[1] == "Close")
                {
                    command = 5;
                }

                switch (command)
                {
                case 0:
                {
                    CreateAccount newAccount = CreateAccount(partsOfLine, sharedMemory);
                    break;
                }
                case 1:
                {
                    CreateAccount newAccount = CreateAccount(partsOfLine, sharedMemory);
                    break;
                }
                case 2:
                {
                    // add code for inquiry class
                    break;
                }
                case 3:
                {
                    // add code for deposit class
                    break;
                }
                case 4:
                {
                    // add code for transfer class
                    break;
                }
                case 5:
                {
                    // add code for close class
                    break;
                }
                }

                // cheat code since syncronization is not currently in place
                pid_t PID = getpid();
                kill(PID, SIGKILL);
            }
            
            // Needs to be refined, code to execute if account exists (withdraw from existing account, etc)
            else if (accountExists(partsOfLine[0]))
            {

                // if the account does not exist, create a child process that does stuff with the new account number
                int command = 7;

                // Switch statment below if statements does not work with strings
                // int command is set using if statements based on withdraw/create etc to use in switch block
                if (partsOfLine[1] == "Withdraw")
                {
                    command = 0;
                }
                if (partsOfLine[1] == "Create")
                {
                    command = 1;
                }
                if (partsOfLine[1] == "Inquiry")
                {
                    command = 2;
                }
                if (partsOfLine[1] == "Deposit")
                {
                    command = 3;
                }
                if (partsOfLine[1] == "Transfer")
                {
                    command = 4;
                }
                if (partsOfLine[1] == "Close")
                {
                    command = 5;
                }

                switch (command)
                {
                case 0:
                {
                    // Add code for withdraw class
                    break;
                }
                case 1:
                {
                    // handle create for account that exists
                    break;
                }
                case 2:
                {
                    // add code for inquiry class
                    break;
                }
                case 3:
                {
                    // add code for deposit class
                    break;
                }
                case 4:
                {
                    // add code for transfer class
                    break;
                }
                case 5:
                {
                    // add code for close class
                    break;
                }

                }
            }
        }

        for (int i = 0; i < 3; i++)
        {
            wait(NULL);
        }

        return 0;
    }
}

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include "CreateAccount.h"
#include "UserAccounts.h"
#include "Inquiry.h"
#include "Inquiry.cpp"
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include "Deposit.h"
#include "Deposit.cpp"
#include "Withdraw.h"
#include "Withdraw.cpp"
#include "CloseAccount.h"
#include "CloseAccount.cpp"
#include "TransferTo.h"
#include "TransferTo.cpp"
#include "SharedMemoryMod.h"

using namespace std;

void *SharedMemoryMod::createSharedMem(size_t size)
{
    // Our memory buffer will be readable and writable:
    int protection = PROT_READ | PROT_WRITE;

    // The buffer will be shared (meaning other processes can access it), but
    // anonymous (meaning third-party processes cannot obtain an address for it),
    // so only this process and its children will be able to use it:
    int visibility = MAP_ANONYMOUS | MAP_SHARED;

    // The remaining parameters to `mmap()` are not important for this use case,
    // but the manpage for `mmap` explains their purpose.
    return mmap(NULL, size, protection, visibility, -1, 0);
}

// Turn line from input file into vector of individual pieces
vector<string> SharedMemoryMod::tokenizeLine(string lineOfFile)
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

// Check if file exists
bool SharedMemoryMod::accExistsMem(string accountNumber)
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

// Handle operations from input file
void SharedMemoryMod::operationsMem(UserAccounts account, int processAccount, void *sharedMemory, Monitor& monitor)
{

    for (int i = 0; i < account.operations.size(); i++)
    {
        vector<string> partsOfLine = tokenizeLine(account.operations[i]);

        // if the account does not exist, create a child process that does stuff with the new account number
        int command = 7;

        // Switch statment below, switch statements do not work with strings
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

            Withdraw(partsOfLine, sharedMemory);
            break;
        }
        case 1:
        {
            if (!accExistsMem(partsOfLine[0]))
            {
                CreateAccount(partsOfLine, sharedMemory);
            }
            break;
        }
        case 2:
        {
            // add code for inquiry class
            Inquiry(partsOfLine, sharedMemory, monitor);
            break;
        }
        case 3:
        {
            // add code for deposit class
            Deposit(partsOfLine, sharedMemory, monitor);
            break;
        }
        case 4:
        {
            // add code for transfer class
            TransferTo(partsOfLine, sharedMemory);
            break;
        }
        case 5:
        {
            CloseAccount closeAccount = CloseAccount(partsOfLine, sharedMemory);

            break;
        }
        }
    }
}

// Create shared memory for semaphores and files, and spawns child processes
// Needs to be updated. Does not control syncronization
void SharedMemoryMod::createMem(UserAccounts account, int processCount, void *sharedMemory, Monitor &monitor)
{

    // shared memory ID
    operationsMem(account, processCount, sharedMemory, monitor);
}

// Constructor, calls create memory with user accounts from driver
SharedMemoryMod::SharedMemoryMod(UserAccounts account, int processCount, void *sharedMemory, Monitor &monitor)
{
    createMem(account, processCount, sharedMemory, monitor);
}

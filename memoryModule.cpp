// Author: Bailey Schultz

#include "memoryModule.h"
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

using namespace std;

/*
The memoryModule will be updated or changed. As of now some code showing memory mapping is being tested
int the CreateAccount class. It needs more work, and needs to be moved to the memoryModule class where
the other classes like CreateAccount, Withdraw, etc should be called from.
*/

void *sharedMemory = mmap(0, 1024, PROT_READ, MAP_SHARED, -1, 0);

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

bool accountExistsMem(string accNum)
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

void operations(UserAccounts account, sem_t **allSems, int processNum)
{

    for (int i = 0; i < account.operations.size(); i++)
    {
        vector<string> partsOfLine = tokenizer(account.operations[i]);

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

            cout << "No Account exists, invalid transaction attempt" << endl;

            break;
        }
        case 1:
        {
            sem_wait(allSems[processNum]);
            if (!accountExistsMem(partsOfLine[0]))
            {
                CreateAccount(partsOfLine, sharedMemory);
            }
            sem_post(allSems[processNum]);
            break;
        }
        case 2:
        {
            // add code for inquiry class
            sem_wait(allSems[processNum]);
            Inquiry(partsOfLine, sharedMemory);
            sem_post(allSems[processNum]);
            break;
        }
        case 3:
        {
            // add code for deposit class
            sem_wait(allSems[processNum]);
            Deposit(partsOfLine, sharedMemory);
            sem_post(allSems[processNum]);
            break;
        }
        case 4:
        {
            // add code for transfer class
            sem_wait(allSems[processNum]);
            TransferTo transfer = TransferTo(partsOfLine, sharedMemory);
            sem_post(allSems[processNum]);
            break;
        }
        case 5:
        {
            CloseAccount closeAccount = CloseAccount(partsOfLine);
            break;
        }
        }
    }
}

// This function checks to see if a file exists or not
void createMemory(vector<UserAccounts> accounts, int processCount)
{
    pid_t pid = -1;

    // Create array to hold semaphores, one per account
    sem_t **semArray = new sem_t *[processCount];

    // initialize semaphores to null
    for (int j = 0; j < processCount; j++)
    {
        semArray[j] = NULL;
    }

    // Create key for shared memory
    key_t key = ftok("Accounts/", 'a');

    int i = 0;

    // shared memory ID
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    ;

    // loop to attach all semaphores to shared memory location
    for (i = 0; i < processCount; i++)
    {

        if (shmid == -1)
        {
            cout << "Memory Creation Failed" << endl;
        }

        // Attach each semaphore in array to shared memory
        semArray[i] = (sem_t *)shmat(shmid, NULL, 0);

        // Initialize all semaphores in array to 1. Must use sem_wait() to lock
        sem_init(semArray[i], 1, 1);
    }

    // Create child process, one for each account
    for (int k = 0; k < processCount; k++)
    {
        if (fork() == 0)
        {
            operations(accounts[k], semArray, k);
            break;
        }
    }
}

memoryModule::memoryModule(vector<UserAccounts> accounts, int processCount)
{
    createMemory(accounts, processCount);
}

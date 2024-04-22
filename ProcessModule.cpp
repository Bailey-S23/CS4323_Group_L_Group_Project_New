// Author: Bailey Schultz
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include "UserAccounts.h"
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include "ProcessModule.h"
#include "SharedMemoryMod.h"
#include "SharedMemoryMod.cpp"
#include "Monitor.h"
#include "Monitor.cpp"

using namespace std;
/*
void ProcessModule::createProcesses(vector<UserAccounts> accounts, int processCount, void *sharedMemory)
{
    pid_t pid;
    // Create child process, one for each account
    for (int k = 0; k < processCount; k++)
    {
        pid = fork();
        if (pid == 0)
        {
            UserAccounts account = accounts[k];
            SharedMemoryMod(account, processCount, sharedMemory);
            break;
        }
    }

    for (int i = 0; i < processCount; i++)
    {
        wait(NULL);
    }

    if (pid != 0)
    {
        char *readInMemMod = (char *)sharedMemory;

        cout << "This line read in ProcessModule: \n" << readInMemMod << endl;
    }
}*/

void ProcessModule::createProcesses(vector<UserAccounts> accounts, int processCount, void *sharedMemory, Monitor &monitor)
{ // add monitory
    pid_t pid;
    // pid_t pid = getpid();
    // kill(pid, SIGTERM);
    for (int k = 0; k < processCount; k++)
    {
        pid = fork();
        if (pid == 0)
        {
            // Child process
            monitor.acquire();
            UserAccounts account = accounts[k];
            SharedMemoryMod(account, processCount, sharedMemory);
            monitor.release();

            exit(0);
        }
    }

    for (int i = 0; i < processCount; i++)
    {
        wait(NULL);
    }

    if (pid != 0)
    { // Parent process
        char *readInMemMod = (char *)sharedMemory;
        cout << "This line read in ProcessModule: \n"
             << readInMemMod << endl;
    }
}

// Constructor, calls create memory with user accounts from driver
/*ProcessModule::ProcessModule(vector<UserAccounts> accounts, int processCount)
{
    void *sharedMemory = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);

    createProcesses(accounts, processCount, sharedMemory);
}*/

ProcessModule::ProcessModule(vector<UserAccounts> accounts, int processCount)
{

    void *sharedMemory = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    if (sharedMemory == MAP_FAILED)
    {
        perror("Error mapping shared memory");
        exit(EXIT_FAILURE);
    }
    Monitor monitor("/processMutex", "/processCondVar");            // Monitor
    createProcesses(accounts, processCount, sharedMemory, monitor); // add monitor
}
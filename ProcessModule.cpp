// Group L
// Author: Bailey Schultz
// Email: Bailey.Schultz@okstate.edu
// 4/21/2024

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

void ProcessModule::createProcesses(vector<UserAccounts> accounts, int processCount, void *sharedMemory, Monitor &monitor)
{ // add monitory
    pid_t pid;

    for (int k = 0; k < processCount; k++)
    {
        // Spawn Child Processes
        pid = fork();
        if (pid == 0)
        {
            // Child process
            UserAccounts account = accounts[k];
            SharedMemoryMod(account, processCount, sharedMemory, monitor);
            break;
        }
    }

    // Wait for Child Proccess
    for (int i = 0; i < processCount; i++)
    {
        wait(NULL);
    }

    // Print out log
    if (pid != 0)
    { // Parent process
        char *readInMemMod = (char *)sharedMemory;
        cout << "Transaction Log: \n"
             << readInMemMod << endl;
    }
}

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
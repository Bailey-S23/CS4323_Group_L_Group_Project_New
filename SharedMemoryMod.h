// Author: Bailey Schultz

#ifndef SHAREDMEMORYMOD_H
#define SHAREDMEMORYMOD_H

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
#include "UserAccounts.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include "CreateAccount.h"
#include "UserAccounts.h"
#include "Inquiry.h"
#include "Deposit.h"
#include "Withdraw.h"
#include "CloseAccount.h"
#include "TransferTo.h"
#include "Monitor.h"


using namespace std;

/*
The memoryModule will be updated or changed. As of now some code showing memory mapping is being tested
int the CreateAccount class. It needs more work, and needs to be moved to the memoryModule class where
the other classes like CreateAccount, Withdraw, etc should be called from.
*/

class SharedMemoryMod
{
public:
    SharedMemoryMod(UserAccounts accountForProcess, int processCount, void *sharedMemory, Monitor &monitor);
    void *createSharedMem(size_t size);
    vector<string> tokenizeLine(string lineOfFile);
    bool accExistsMem(string accNum);
    void operationsMem(UserAccounts account, int processAccount, void *sharedMemory, Monitor &monitor);
    void createMem(UserAccounts account, int processCount, void *sharedMemory, Monitor &monitor);
};

#endif
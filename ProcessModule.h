// Author: Bailey Schultz

#ifndef PROCESSMODULE_H
#define PROCESSMODULE_H

#include <sys/ipc.h>
#include <sys/shm.h>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
#include "UserAccounts.h"
#include "SharedMemoryMod.h"

using namespace std;

/*
The memoryModule will be updated or changed. As of now some code showing memory mapping is being tested
int the CreateAccount class. It needs more work, and needs to be moved to the memoryModule class where
the other classes like CreateAccount, Withdraw, etc should be called from.
*/

class ProcessModule
{
public:
    ProcessModule(vector<UserAccounts> accounts, int processCount);

private:
    void createProcesses(vector<UserAccounts> accounts, int processCount, void* sharedMemory);
};

#endif
#ifndef READFILE_H
#define READFILE_H

#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
#include <mutex>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include "UserAccounts.h"
#include "SharedMemoryMod.h"
#include "ProcessModule.h"

using namespace std;

class ReadFile
{
public:
    ReadFile(string inputFileName);
    int checkForAccountInVector(vector<UserAccounts> accountVector, string accountName);
    bool accountExists(string accNum);
    vector<string> tokenize(string lineOfFile);
};

#endif
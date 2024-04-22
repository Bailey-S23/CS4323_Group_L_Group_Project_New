// Author: Bailey Schultz

#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H

#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
#include "Monitor.h"



using namespace std;

class CreateAccount
{

public:
    std::string accName;
    int accBalance;
    Monitor& monitor;
    // CreateAccount(vector<string> accountInfo, void* sharedMemory);
    CreateAccount(vector<string> accountInfo, void* sharedMemory, Monitor& monitor);
    bool accExists(string accountName);
    
    std::string returnCurrentTimeAndDate();
};

#endif
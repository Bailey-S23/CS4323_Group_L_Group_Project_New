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
    string accName;
    int accBalance;
    CreateAccount(vector<string> accountInfo, void* sharedMemory, Monitor& monitor);
    bool accExists(string accountName);
    string returnCurrentTimeAndDate();
};

#endif
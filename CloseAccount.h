// Author: Katie Pinell
// Date: 4/14/2024
// Description: This is the header file for CloseAccount.cpp
// CloseAccount.cpp closes an account by deleting the corresponding file.

#ifndef CLOSEACCOUNT_H
#define CLOSEACCOUNT_H

#include <string>
#include <vector>
#include "Monitor.h"

using namespace std;

class CloseAccount
{

    public:
        string accName;
        CloseAccount(vector<string> accountInfo, void* sharedMemory, Monitor& monitor);
        string returnCurrentTimeAndDate();
};

#endif
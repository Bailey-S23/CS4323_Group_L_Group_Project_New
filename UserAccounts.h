// Author: Bailey Schultz

#ifndef USERACCOUNTS_H
#define USERACCOUNTS_H

#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class UserAccounts
{
    public:
        string accountNumber;
        //vector<vector<string>> operationVector;
        vector<string> operations;
        UserAccounts(string accountNumber);
};

#endif
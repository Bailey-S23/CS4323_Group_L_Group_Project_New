// Group L
// Author: Bailey Schultz
// Email: Bailey.Schultz@okstate.edu
// 4/21/2024

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

// Class to represent a user
class UserAccounts
{
    public:
        string accountNumber;
        vector<vector<string>> operationVector; // *NOT USED*
        vector<string> operations;
        UserAccounts(string accountNumber);
};

#endif
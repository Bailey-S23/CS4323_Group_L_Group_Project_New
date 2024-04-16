// Author: Caleb Sullard
// Date: 4/14/2024
// Description: This is the header file for TransferTo.cpp
// TransferTo.cpp moves money from account to another account

#ifndef TRANSFERTO_H
#define TRANSFERTO_H

#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <string>


class TransferTo {
public:
    TransferTo(vector<string> transactionDetails, void* sharedMemory);

private:
    void transferAmount(string withdrawAccount, double amount, string depositAccount);
};

#endif

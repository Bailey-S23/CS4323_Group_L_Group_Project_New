// Author: Katie Pinell
// Date: 4/14/2024
// Description: This is the header file for Withdraw.cpp
// Withdraw.cpp withdraws a given amount from an account.

#ifndef TRANSFER_H
#define TRANSFER_H

#include <vector>
#include <string>

using namespace std;

class Withdraw {
public:
    Withdraw(vector<string> transactionDetails, void* sharedMemory);

private:
    void WithdrawAmount(string withdrawAccount, double amount);
};

#endif
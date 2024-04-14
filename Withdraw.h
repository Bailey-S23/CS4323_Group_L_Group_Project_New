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
// Group L
// Caleb Sullard
// caleb.sullard@okstate.edu
// 4/21/2024
// Description: This is the header file for TransferTo.cpp
// TransferTo.cpp moves money from account to another account

#ifndef TRANSFERTO_H
#define TRANSFERTO_H

#include <string>
#include <vector>
#include "Monitor.h"


class TransferTo {
public:
    TransferTo(vector<string> transactionDetails, void* sharedMemory, Monitor& monitor);

private:
    static mutex mtx;
    void withdrawAmount(string withdrawAccount, double amount, string depositAccount, void* sharedMemory);
    void depositAmount(string withdrawAccount, double amount, string depositAccount, void* sharedMemory);
    string returnCurrentTimeAndDate();
    Monitor& monitor; // Reference to the Monitor object for inter-process synchronization
};

#endif

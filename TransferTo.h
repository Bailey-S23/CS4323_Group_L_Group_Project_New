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
    // I separated transfer into 2 methods (withdraw & deposit) to better organize file access and prevent any mistakes with shared resources
    void withdrawAmount(string withdrawAccount, double amount, string depositAccount, void* sharedMemory);
    void depositAmount(string withdrawAccount, double amount, string depositAccount, void* sharedMemory);
    string returnCurrentTimeAndDate(); // Use this to log process execution infor
    Monitor& monitor; // Reference to the Monitor object for inter-process synchronization
};

#endif

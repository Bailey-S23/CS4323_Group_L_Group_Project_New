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

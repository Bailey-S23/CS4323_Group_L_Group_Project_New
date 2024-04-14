#ifndef TRANSFER_H
#define TRANSFER_H

#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <string>

class Transfer {
public:
    Transfer(std::vector<std::string> transactionDetails, void* sharedMemory);

private:
    void transferAmount(std::string withdrawAccount, double amount, std::string depositAccount);
};

#endif

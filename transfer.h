#ifndef TRANSFER_H
#define TRANSFER_H

#include <vector>
#include <string>

class transfer {
public:
    transfer(std::vector<std::string> transactionDetails, void* sharedMemory);

private:
    void transferAmount(std::string withdrawAccount, double amount, std::string depositAccount);
};

#endif
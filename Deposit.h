#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <vector>
#include <string>

// Forward declaration of std::vector and std::string to minimize includes
class Deposit {
public:
    // Constructor: Takes a vector of strings containing the transaction details and a pointer to shared memory
    Deposit(std::vector<std::string> transactionDetails, void* sharedMemory);

private:
    void depositAmount(std::string accNum, double amount);
    static mutex mtx;  // Make mutex a class static member if sharing across instances
};

#endif // DEPOSIT_H

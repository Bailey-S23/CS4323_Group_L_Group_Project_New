/* Author Name: Zach  Wilson
    Email: stealth.wilson@okstate.edu
    Date: 04/14/2024
   Deposit header file holding deposit class definition */

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
    void depositAmount(std::string accNum, double amount, void* sharedMemory);
    static mutex mtx;  // Make mutex a class static member if sharing across instances
    string returnCurrentTimeAndDate();
};

#endif // DEPOSIT_H

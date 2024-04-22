/* Author Name: Zach  Wilson
    Email: stealth.wilson@okstate.edu
    Date: 04/14/2024
   Deposit header file holding deposit class definition */

#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <vector>
#include <string>
#include "Monitor.h"


// Forward declaration of std::vector and std::string to minimize includes
class Deposit {
public:
    // Constructor: Takes a vector of strings containing the transaction details and a pointer to shared memory
    Deposit(std::vector<std::string> transactionDetails, void* sharedMemory, Monitor& monitor);

private:
    void depositAmount(std::string accNum, double amount, void* sharedMemory);
    //static mutex mtx;  // Make mutex a class static member if sharing across instances
    std::string returnCurrentTimeAndDate();

    Monitor& monitor; // Reference to the Monitor object for inter-process synchronization
   
};

#endif // DEPOSIT_H

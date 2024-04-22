/* Author Name: Katie Pinell
    Email: katie.pinell@okstate.edu
    Date: 04/21/2024
   Withdraw header file holding Withdraw class definition */

#ifndef WITHDRAW_H
#define WITHDRAW_H

#include <vector>
#include <string>

class Withdraw {
public:
    Withdraw(std::vector<std::string> transactionDetails, void* sharedMemory);

private:
    void WithdrawAmount(std::string accNum, double amount, void* sharedMemory);
    static mutex mtx;
    string returnCurrentTimeAndDate();
};

#endif

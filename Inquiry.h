/* Author Name: Zach  Wilson
    Email: stealth.wilson@okstate.edu
    Date: 04/14/2024
    Inquire header file to define the inquiry class*/

#ifndef INQUIRY_H
#define INQUIRY_H

#include <string>
#include <vector>

class Inquiry
{
public:
    Inquiry(const std::vector<std::string> &transactionDetails, void *sharedMemory);

private:
    void inquireBalance(const std::string accNum, void *sharedMemory); // Declaration of the private member function
    string returnCurrentTimeAndDate();
};

#endif // INQUIRY_H

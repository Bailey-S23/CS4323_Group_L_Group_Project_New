#ifndef INQUIRY_H
#define INQUIRY_H

#include <string>
#include <vector>

class Inquiry {
public:
    Inquiry(const std::vector<std::string>& transactionDetails, void* sharedMemory);

private:
    void inquireBalance(const std::string accNum); // Declaration of the private member function
};

#endif // INQUIRY_H
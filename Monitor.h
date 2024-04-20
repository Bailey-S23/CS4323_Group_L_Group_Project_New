// Monitor.h
#ifndef MONITOR_H
#define MONITOR_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <string>

// Structure to represent a transaction
struct Transaction {
    std::string command;                 // Command type (Withdraw, Deposit, etc.)
    std::vector<std::string> parameters; // Parameters associated with the command
};

class TransactionMonitor {
public:
    TransactionMonitor();               // Constructor
    ~TransactionMonitor();              // Destructor
    void enqueueTransaction(const Transaction& transaction);
    Transaction dequeueTransaction();
    bool isEmpty();

private:
    std::mutex mtx;                            // Mutex for synchronization
    std::condition_variable cv;                // Condition variable for queue management
    std::queue<Transaction> transactionQueue;  // Queue to hold transactions
};

#endif // MONITOR_H

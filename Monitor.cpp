// Monitor.cpp
#include "Monitor.h"

TransactionMonitor::TransactionMonitor() {
    // Constructor implementation, if needed
}

TransactionMonitor::~TransactionMonitor() {
    // Destructor implementation, if needed
}

void TransactionMonitor::enqueueTransaction(const Transaction& transaction) {
    std::lock_guard<std::mutex> lock(mtx);
    transactionQueue.push(transaction);
    cv.notify_one();  // Notify one waiting thread that a transaction is available
}

Transaction TransactionMonitor::dequeueTransaction() {
    std::unique_lock<std::mutex> lock(mtx);
    while (transactionQueue.empty()) {
        cv.wait(lock);  // Wait until there is a transaction in the queue
    }
    Transaction trans = transactionQueue.front();
    transactionQueue.pop();
    return trans;
}

bool TransactionMonitor::isEmpty() {
    std::lock_guard<std::mutex> lock(mtx);
    return transactionQueue.empty();
}

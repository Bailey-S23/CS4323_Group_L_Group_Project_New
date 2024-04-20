#include "Monitor.h"
#include "iostream"

std::mutex TransactionMonitor::mtx; // Correctly define the static mutex

void TransactionMonitor::logTransaction(const std::string& logEntry) {
    std::lock_guard<std::mutex> lock(mtx);
    logQueue.push(logEntry);
    cv.notify_all();
}

std::string TransactionMonitor::getLog() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this] { return !logQueue.empty(); });
    std::string log = logQueue.front();
    logQueue.pop();
    return log;
}

void TransactionMonitor::printLogQueue() {
    std::lock_guard<std::mutex> lock(mtx);
    if (logQueue.empty()) {
        std::cout << "Log queue is empty." << std::endl;
    } else {
        std::cout << "Current Log Queue Contents (" << logQueue.size() << " entries):" << std::endl;
        std::queue<std::string> tmpQueue = logQueue;
        while (!tmpQueue.empty()) {
            std::cout << tmpQueue.front() << std::endl;
            tmpQueue.pop();
        }
    }
}

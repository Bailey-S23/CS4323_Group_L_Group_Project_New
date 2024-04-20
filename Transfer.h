#ifndef MONITOR_H
#define MONITOR_H

#include <mutex>
#include <string>
#include <queue>
#include <condition_variable>

class TransactionMonitor {
public:
    void logTransaction(const std::string& logEntry);
    std::string getLog();
    void printLogQueue();

    static std::mutex mtx;  // This declaration must be public or private with public access via method if needed

private:
    std::queue<std::string> logQueue;
    std::condition_variable cv;
};

#endif // MONITOR_H

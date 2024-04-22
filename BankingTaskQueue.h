/* Author Name: Zach  Wilson
    Email: stealth.wilson@okstate.edu
    Date: 04/14/2024
   Banking taske Queue header file */


#ifndef BANKING_TASK_QUEUE_H
#define BANKING_TASK_QUEUE_H

#include "Monitor.h"
#include <vector>
#include <string>
#include <optional>

// Define the BankingTask struct
struct BankingTask {
    enum class Type { Deposit, Withdrawal, Transfer, Inquiry } type;
    std::vector<std::string> params; // Details of the task
};

class BankingTaskQueue {
public:
    BankingTaskQueue(Monitor& monitor, void* sharedMemory);

    void enqueueTask(const BankingTask& task);
    std::optional<BankingTask> dequeueTask();

private:
    Monitor& monitor;
    // The shared memory space where the queue lives
    // This can be a pointer to a structure that resides in shared memory
    void* sharedMemory;
};

#endif // BANKING_TASK_QUEUE_H

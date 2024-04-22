/* Author Name: Zach  Wilson
    Email: stealth.wilson@okstate.edu
    Date: 04/14/2024
   Banking taske Queue */

#include "BankingTaskQueue.h"

BankingTaskQueue::BankingTaskQueue(Monitor& monitor, void* sharedMemory)
    : monitor(monitor), sharedMemory(sharedMemory) {
    // Initialize shared memory structure for the queue
}

void BankingTaskQueue::enqueueTask(const BankingTask& task) {
    monitor.acquire();
    // Add the task to the queue in shared memory
    monitor.release();
}

std::optional<BankingTask> BankingTaskQueue::dequeueTask() {
    std::optional<BankingTask> task;
    monitor.acquire();
    // Remove the task from the queue in shared memory
    // and assign it to 'task' if the queue is not empty
    monitor.release();
    return task;
}

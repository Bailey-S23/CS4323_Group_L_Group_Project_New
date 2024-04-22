/* Author Name: Zach  Wilson
    Email: stealth.wilson@okstate.edu
    Date: 04/14/2024
    Monitor header file to define the monitor class*/
#ifndef MONITOR_H
#define MONITOR_H

#include <semaphore.h>
#include <fcntl.h> // For O_CREAT, O_EXCL, etc.

class Monitor {
private:
    sem_t* mutex;
    sem_t* cond_var;
    std::string mutexName;
    std::string condVarName;
public:
    Monitor(const char* mutexName, const char* condVarName);
    ~Monitor();
    void acquire();
    void release();
    void wait();
    void signal();
};

#endif // MONITOR_H
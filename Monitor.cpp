/* Author Name: Zach  Wilson
    Email: stealth.wilson@okstate.edu
    Date: 04/14/2024
    Monitor*/
    
#include "Monitor.h"
#include <fcntl.h>            // For O_CREAT, O_EXCL, etc.
#include <sys/stat.h>         // For mode constants
#include <cstdio>             // For perror
#include <cstdlib>            // For exit and EXIT_FAILURE
#include <iostream>           // For std::cout
#include <unistd.h>           // For getpid(), used in multi-process environments

Monitor::Monitor(const char* mutexName, const char* condVarName) {
    mutex = sem_open(mutexName, O_CREAT, 0644, 1);
    cond_var = sem_open(condVarName, O_CREAT, 0644, 0);
    if (mutex == SEM_FAILED || cond_var == SEM_FAILED) {
        perror("Semaphore initialization failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "Monitor initialized with mutex: " << mutexName << " and cond_var: " << condVarName << std::endl;
}

Monitor::~Monitor() {
    sem_close(mutex);
    sem_close(cond_var);
    sem_unlink("/mutexSem");
    sem_unlink("/condVarSem");
    std::cout << "Monitor destroyed and semaphores unlinked." << std::endl;
}

void Monitor::acquire() {
    std::cout << "Process " << getpid() << " attempting to acquire lock..." << std::endl;
    //sem_wait(mutex); 
    sem_post(mutex);
    std::cout << "Process " << getpid() << " acquired lock." << std::endl;
}

void Monitor::release() {
    sem_post(mutex);
    std::cout << "Process " << getpid() << " released lock." << std::endl;
}

void Monitor::wait() {
    std::cout << "Process " << getpid() << " is waiting on condition variable..." << std::endl;
    sem_post(mutex);  // Release mutex while waiting
    sem_wait(cond_var);  // Wait for the condition variable
    sem_wait(mutex);  // Reacquire mutex after waking up
    std::cout << "Process " << getpid() << " wait over, reacquired lock." << std::endl;
}

void Monitor::signal() {
    sem_post(cond_var);
    std::cout << "Process " << getpid() << " signaled condition variable." << std::endl;
}

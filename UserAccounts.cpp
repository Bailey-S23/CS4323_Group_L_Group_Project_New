// Group L
// Author: Bailey Schultz
// Email: Bailey.Schultz@okstate.edu
// 4/21/2024

#include "UserAccounts.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fstream>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>

using namespace std;

// Constructor for User Account
UserAccounts::UserAccounts(string x)
{
    accountNumber = x;
}
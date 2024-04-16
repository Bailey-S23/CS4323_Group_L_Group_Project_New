// Author: Bailey Schultz

#include "UserAccounts.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fstream>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>

using namespace std;

UserAccounts::UserAccounts(string x)
{
    accountNumber = x;
}
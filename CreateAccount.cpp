// Author: Bailey Schultz

#include "CreateAccount.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fstream>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>

/*
CreateAccount::CreateAccount(vector<string> accountInfo, void *sharedMemory)
{

    accBalance = stoi(accountInfo[2].data());
    string accName = accountInfo[0];

    string temp = "Accounts/" + accountInfo[0];
    const char *account = temp.data();
    struct stat sb;



    ofstream outfile("Accounts/" + accName);
    outfile << accBalance;


    int fd = open(account, 0666);

    if (fstat(fd, &sb) == -1)
    {
        perror("Couldnt get size of file");
    }


    sharedMemory = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

    outfile.close();

    cout << "Account Created: " + accName << endl;
}
*/

// Constructor that creates new account files
CreateAccount::CreateAccount(vector<string> accountInfo, void *sharedMemory)
{

    accBalance = stoi(accountInfo[2].data());
    string accName = accountInfo[0];

    string temp = "Accounts/" + accountInfo[0];

    struct stat sb;

    ofstream outfile("Accounts/" + accName);
    outfile << accBalance;

    outfile.close();

    cout << "------------------Account Created: " + accName << endl;

    //------------------------------------------







    char *readInCreate = (char *)sharedMemory;

    cout << "Read in Create: " << readInCreate << endl;

    string writtenInCreate = "This line written in create\n";

    string writtenInCreate2 = "This line written in create2\n";

    char *writeInCreate = writtenInCreate.data();

    char *writeInCreate2 = writtenInCreate2.data();

    sprintf((char *)sharedMemory, writeInCreate);

    sprintf((char *)sharedMemory, writeInCreate2);

    // memcpy(sharedMemory, writeInCreate,  sizeof(writtenInCreate) * 2);

    /*
        char *writeOut = (char *)shmat(shmid, NULL, 0);

        cout << "Read from Create" << writeOut;

        if (writeOut == (void *)-1)
        {
            perror("Shared memory attach");
        }

        cout << writeOut << endl
             << flush;

             */
}

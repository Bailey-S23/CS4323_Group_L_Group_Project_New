#include "memoryModule.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include "CreateAccount.h"
#include "CreateAccount.cpp"

/*
The memoryModule will be updated or changed. As of now some code showing memory mapping is being tested
int the CreateAccount class. It needs more work, and needs to be moved to the memoryModule class where
the other classes like CreateAccount, Withdraw, etc should be called from.
*/


vector<string> tokenizer(string lineOfFile)
{
    stringstream sstream(lineOfFile);
    string singleString;

    vector<string> partsOfLine;

    while (sstream >> singleString)
    {
        partsOfLine.push_back(singleString);
    }

    return partsOfLine;
}

// This function checks to see if a file exists or not
bool accountExists(string accNum)
{

    ifstream file;

    file.open("Accounts/" + accNum);

    bool exists = false;

    if (file)
    {
        cout << "File " + accNum + " exists" << endl;
        exists = true;
    }
    else
    {
        exists = false;
    }

    return exists;
}




memoryModule::memoryModule (vector<string> partsOfLine)
{
    
}
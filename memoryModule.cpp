#include "memoryModule.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include "CreateAccount.h"
#include "CreateAccount.cpp"




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
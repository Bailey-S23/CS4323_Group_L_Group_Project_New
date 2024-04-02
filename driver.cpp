#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
#include "CreateAccount.h"
#include "CreateAccount.cpp"

using namespace std;

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

bool accountExists(string accNum)
{
    char *file = accNum.data();
    struct stat sb;
    bool exists = false;

    if (stat(file, &sb) == 0)
    {
        cout << file << " exists" << endl;
        exists = true;
    }

    return exists;
}

int main()
{

    const char *dir = "Accounts";
    struct stat sb;

    if (stat(dir, &sb) == 0)
    {
        cout << "Directory exists, continuing" << endl;
    }
    else
    {
        if (mkdir(dir, 0777) == -1)
        {
            cerr << "Error :  " << strerror(errno) << endl;
        }
        else
        {
            cout << "Directory created" << endl;
        }
    }

    string fileToRead = "InputFile";
    ifstream inputFile(fileToRead);

    string lineOfFile;

    if (inputFile.is_open())
    {
        getline(inputFile, lineOfFile);

        while (getline(inputFile, lineOfFile))
        {
            vector<string> partsOfLine;

            partsOfLine = tokenizer(lineOfFile);

            int command = 7;

            if (partsOfLine[1] == "Withdraw")
            {
                command = 0;
            }
            if (partsOfLine[1] == "Create")
            {
                command = 1;
            }
            if (partsOfLine[1] == "Inquiry")
            {
                command = 2;
            }
            if (partsOfLine[1] == "Deposit")
            {
                command = 3;
            }
            if (partsOfLine[1] == "Transfer")
            {
                command = 4;
            }
            if (partsOfLine[1] == "Close")
            {
                command = 5;
            }

            switch (command)
            {
            case 0:
            {
                CreateAccount newAccount = CreateAccount(partsOfLine);
                break;
            }
            case 1:
            {
                // do stuff
                break;
            }
            default:
            {
                break;
            }
            }
        }
    }

    return 0;
}

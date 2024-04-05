#ifndef MEMORYMODULE_H
#define MEMORYMODULE_H

#include <sys/ipc.h>
#include <sys/shm.h>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class memoryModule
{
    public:
        memoryModule(vector<string> partsOfLine);
        vector<string> tokenizer(string lineOfFile);
        bool accountExists(string accNum);
};

#endif
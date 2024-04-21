// Author: Group L

#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
#include <mutex>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>


#include "ReadFile.h"
#include "ReadFile.cpp"

using namespace std;

int main(int argc, char* argv[])
{

    string inputFileName = "InputFile";
    ReadFile fileToRead = ReadFile(inputFileName);

    return 0;
}

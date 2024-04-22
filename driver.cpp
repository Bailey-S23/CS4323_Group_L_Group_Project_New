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
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file_name>\n";
        return 1;
    }

      string fileToRead = argv[1]; // Use the command-line argument for the input file name
    ifstream inputFile(fileToRead);
    if (!inputFile.is_open()) {
        cerr << "Failed to open file: " << fileToRead << endl;
        return 1;
    }

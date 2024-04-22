// Group L
// Caleb Sullard
// caleb.sullard@okstate.edu
// 4/21/2024
// Description: This file moves money from account to another account

// forks must be used and they must run in parrallel
// add sleep() function of at least 10 seconds

#include "TransferTo.h"  // Include the header to get the class definition
#include <iostream>
#include <fstream>
#include <mutex>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <unistd.h>

using namespace std;

mutex mtx;

TransferTo::TransferTo(vector<string> transactionDetails, void* sharedMemory) {

    if (transactionDetails.size() < 4)
    {
        cerr << "Invalid transaction details for transfer." << endl;
        return;
    }
    else
    {
        string withdrawAccount = transactionDetails[0];
        double amount = stod(transactionDetails[2]);
        string depositAccount = transactionDetails[3];

    sleep(10);

    withdrawAmount(withdrawAccount, amount, depositAccount, sharedMemory);
    }
}

string TransferTo::returnCurrentTimeAndDate()
{
    auto currentTime = chrono::system_clock::now();
    auto currentTime_t = chrono::system_clock::to_time_t(currentTime);

    stringstream ss;
    ss << std::put_time(localtime(&currentTime_t), "%Y-%m-%d %X");
    return ss.str();
}

void TransferTo::withdrawAmount(string withdrawAccount, double amount, string depositAccount, void* sharedMemory)
{
    lock_guard<mutex> guard(mtx);
    string filePath = "Accounts/" + withdrawAccount;
    fstream withdrawAccountFile(filePath, ios::in | ios::out | ios::binary);

    if (!withdrawAccountFile.is_open())
    {
        cerr << "Account file " << withdrawAccount << " could not be opened for withdrawing." << endl;
        return;
    }

    double currentBalance = 0.0;
    withdrawAccountFile >> currentBalance;

    if (currentBalance < amount)
    {
        string time = returnCurrentTimeAndDate();
        string writeToFile = "Transaction type: Transfer " + withdrawAccount + " " + to_string(amount) + " " + depositAccount + " FAILURE " + time + "\n";
        char *readInCreate = (char *)sharedMemory;
        char *writeInLog = writeToFile.data();
        strcat((char *)sharedMemory, writeInLog);

        cerr << "Account file " << withdrawAccount << " has insufficient funds." << endl;
        return;
    }
    else
    {
        withdrawAccountFile.clear();
        withdrawAccountFile.seekp(0, ios::beg);

        currentBalance -= amount;

        withdrawAccountFile << fixed << setprecision(2) << currentBalance;
        withdrawAccountFile.flush();
        withdrawAccountFile.close();

        depositAmount(withdrawAccount, amount, depositAccount, sharedMemory);
    }
}

void TransferTo::depositAmount(string withdrawAccount, double amount, string depositAccount, void* sharedMemory)
{
    lock_guard<mutex> guard(mtx);
    string filePath = "Accounts/" + depositAccount;
    fstream depositAccountFile(filePath, ios::in | ios::out | ios::binary);

    if (!depositAccountFile.is_open())
    {
        string time = returnCurrentTimeAndDate();
        string writeToFile = "Transaction type: Transfer " + withdrawAccount + " " + to_string(amount) + " " + depositAccount + " " + " FAILURE " + time + "\n";
        cerr << "Account file " << depositAccount << " could not be opened for deposit." << endl;
        return;
    }
    else
    {
        double currentBalance = 0.0;
        depositAccountFile >> currentBalance;

        depositAccountFile.clear(); 
        depositAccountFile.seekp(0, ios::beg);

        currentBalance += amount;

        depositAccountFile << fixed << setprecision(2) << currentBalance;
        depositAccountFile.flush();
        depositAccountFile.close();

        string time = returnCurrentTimeAndDate();
        string writeToFile = "Transaction type: Transfer " + withdrawAccount + " " + to_string(amount) + " " + depositAccount + " " + " SUCCESS " + time + "\n";
        char *writeInLog = writeToFile.data();
        strcat((char *)sharedMemory, writeInLog);
    }
}





























// #include "TransferTo.h"
// #include <fstream>
// #include <iomanip>
// #include <iostream>
// #include <mutex>
// #include <string>
// #include <vector>

// using namespace std;

// mutex mtx;

// TransferTo::TransferTo(vector<string> transactionDetails, void* sharedMemory) {

//     if (transactionDetails.size() < 4)
//     {
//         cerr << "Invalid transaction details for transfer." << endl;
//         return;
//     }

//     string withdrawAccount = transactionDetails[0];
//     double amount = stod(transactionDetails[2]);
//     string depositAccount = transactionDetails[3];

//     sleep(10);

//     transferAmount(withdrawAccount, amount, depositAccount);
// }

// void TransferTo::transferAmount(string withdrawAccount, double amount, string depositAccount) {

//     lock_guard<mutex> guard(mtx);
//     string filePath = "Accounts/" + withdrawAccount;

//     fstream withdrawAccountFile(filePath, ios::in | ios::out | ios::binary);
//     if (!withdrawAccountFile.is_open())
//     {
//         cerr << "Account " << withdrawAccount << " could not be opened for withdraw." << endl;
//         return;
//     }
//     if (withdrawAccountBalance < amount)
//     {
//         withdrawAccountFile.close();
//         cerr << withdrawAccount << " has insufficent funds for withdrawal." << endl;
//         return;
//     }



//     double withdrawAccountBalance = 0.0;
//     withdrawAccountFile >> withdrawAccountBalance;








//     fstream depositAccountFile(filePath, ios::in | ios::out | ios::binary);
//     if (!depositAccountFile.is_open())
//     {
//         withdrawAccountFile.close();
//         cerr << "Account " << depositAccount << " could not be opened for deposit." << endl;
//         return;
//     }





    

//     double withdrawAccountBalance = 0.0;
//     withdrawAccountFile >> withdrawAccountBalance;

//     double depositAccountBalance = 0.0;
//     depositAccountFile >> depositAccountBalance;

//     if (withdrawAccountBalance < amount)
//     {
//         withdrawAccountFile.close();
//         depositAccountFile.close();
//         cerr << withdrawAccount << " has insufficent funds for withdrawal." << endl;
//         return;
//     }
//     else
//     {
//         withdrawAccountBalance -= amount;
//         depositAccountBalance += amount;

//         withdrawAccountFile.clear();
//         withdrawAccountFile.seekp(0, ios::beg);
//         depositAccountFile.clear();
//         depositAccountFile.seekp(0, ios::beg);

//         withdrawAccountFile << withdrawAccountBalance;
//         depositAccountFile << depositAccountBalance;

//         withdrawAccountFile << fixed << setprecision(2) << withdrawAccountBalance;
//         withdrawAccountFile.flush();
//         depositAccountFile << fixed << setprecision(2) << depositAccountBalance;
//         depositAccountFile.flush();

//         if (withdrawAccountFile.fail() || depositAccountFile.fail())
//         {
//             cerr << "Failed to transfer " << amount << "from " << withdrawAccount << "to " << depositAccount << endl;
//         }
//         else
//         {
//             cout << "Transfer of " << amount << " from account " << withdrawAccount << " to account " << depositAccount << " successful." << endl;
//             cout << "New balance of " << withdrawAccount << ": " << withdrawAccountBalance << endl;
//             cout << "New balance of " << depositAccount << ": " << depositAccountBalance << endl;
//         }
//     }

//     withdrawAccountFile.close();
//     depositAccountFile.close();
// }
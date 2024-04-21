// Author: Caleb Sullard
// Date: 4/15/2024
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

using namespace std;

mutex mtx;

TransferTo::TransferTo(vector<string> transactionDetails, void* sharedMemory) {

    if (transactionDetails.size() < 4)
    {
        cerr << "Invalid transaction details for transfer." << endl;
        return;
    }

    string withdrawAccount = transactionDetails[0];
    double amount = stod(transactionDetails[2]);
    string depositAccount = transactionDetails[3];

    sleep(10);

    if (withdrawAmount(withdrawAccount, amount) == 1)
    {
        if (depositAmount(depositAccount, amount) == 1)
        {
            cout << "Transfer of " << amount << " from account " << withdrawAccount << " to account " << depositAccount << " successful." << endl;
            cout << "New balance of " << withdrawAccount << ": " << withdrawAccountBalance << endl;
            cout << "New balance of " << depositAccount << ": " << depositAccountBalance << endl;
        } else { cerr << "Failed to transfer " << amount << "from " << withdrawAccount << "to " << depositAccount << endl; }
    } else { cerr << "Failed to transfer " << amount << "from " << withdrawAccount << "to " << depositAccount << endl; }
}

int TransferTo::withdrawAmount(string account, double amount)
{
    lock_guard<mutex> guard(mtx);
    string filePath = "Accounts/" + account;
    fstream withdrawAccountFile(filePath, ios::in | ios::out | ios::binary);

    if (!withdrawAccountFile.is_open())
    {
        cerr << "Account file " << account << " could not be opened for withdrawing." << endl;
        return 0;
    }

    double currentBalance = 0.0;
    accountFile >> currentBalance;

    withdrawAccountFile.clear(); 
    withdrawAccountFile.seekp(0, ios::beg);

    currentBalance -= amount;

    withdrawAccountFile << fixed << setprecision(2) << currentBalance;
    withdrawAccountFile.flush();
    withdrawAccountFile.close();
    return 1;
}

int TransferTo::depositAmount(string account, double amount)
{
    lock_guard<mutex> guard(mtx);
    string filePath = "Accounts/" + account;
    fstream depositAccountFile(filePath, ios::in | ios::out | ios::binary);

    if (!depositAccountFile.is_open())
    {
        cerr << "Account file " << account << " could not be opened for deposit." << endl;
        return 0;
    }

    double currentBalance = 0.0;
    accountFile >> currentBalance;

    depositAccountFile.clear(); 
    depositAccountFile.seekp(0, ios::beg);

    currentBalance += amount;

    depositAccountFile << fixed << setprecision(2) << currentBalance;
    depositAccountFile.flush();
    depositAccountFile.close();
    return 1;
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
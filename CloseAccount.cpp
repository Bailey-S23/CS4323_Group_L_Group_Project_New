#include "CloseAccount.h"
#include <iostream>
#include <unistd.h>
#include <cstdio>

using namespace std;

CloseAccount::CloseAccount(vector<string> accountInfo)
{
    // Get the account name from the account info
    string accName = accountInfo[0];

    // The file path is Accounts/account
    string filePath = "Accounts/" + accName;

    // Delete the account file and store the outcome
    int accountDeleted = remove(filePath.c_str());

    // Check if there was an error deleting the account
    if (accountDeleted != 0)
    {
        cout << "Error deleting account: " + accName << endl;
    } else  // The account was successfully deleted
    {
        cout << "Account deleted: " + accName << endl;
    }
}
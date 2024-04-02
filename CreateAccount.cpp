#include "CreateAccount.h"

CreateAccount::CreateAccount(vector<string> accountInfo)
        {
            char *account = accountInfo[0].data();

            accBalance = stoi(accountInfo[2]);
            accName = accountInfo[0];
            ofstream outfile("Accounts/" + accName);
            outfile << accBalance;
            outfile.close();
        }

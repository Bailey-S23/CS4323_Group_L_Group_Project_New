#include "CreateAccount.h"

CreateAccount::CreateAccount(vector<string> accountInfo)
        {
            char *account = accountInfo[0].data();

            ofstream outfile("Accounts/" + accountInfo[0]);
            outfile << accountInfo[2];
            outfile.close();
        }

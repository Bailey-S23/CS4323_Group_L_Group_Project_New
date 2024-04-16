#ifndef CLOSEACCOUNT_H
#define CLOSEACCOUNT_H

#include <string>
#include <vector>

using namespace std;

class CloseAccount
{

    public:
        string accName;
        CloseAccount(const vector<string>& accountInfo);
        CloseAccount(vector<string> accountInfo);
};

#endif

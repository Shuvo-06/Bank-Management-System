#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <bits/stdc++.h>
using namespace std;

// ---------------------------------
// Account Data Struct
// ---------------------------------
struct AccountData {
    string name;
    string nid;
    string password;
    double deposit=0.0;
    double withdraw=0.0;
    vector<double> history;


};

// Global vector for all account holders
extern vector<AccountData> Account_vector;

// ---------------------------------
// Account Holder Class
// ---------------------------------
class AccountHolder {
    string name;
    string nid;
    string pass;
    string conf_pass;
    double deposit;

public:
    // Constructors
    AccountHolder(double deposit = 0.0);       // For sign-up
    AccountHolder(int index, string nid);      // For sign-in / dashboard

    // Member functions
    void collect_info();                        // Sign-up info collection
    static void accntHolderInfo();              // Display all account holder info
    static void updateCustomer(int);
    static void complainBox(string);

};

#endif // GENERAL_HPP

#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <bits/stdc++.h>
#include "tools.hpp"
#include "admin.hpp"
#include "general.hpp"
#include "sign.hpp"

using namespace std;


struct EmployeeData;

// ---------------------------------
// Employee Data Struct
// ---------------------------------

// Extern vectors for global access (used in cpp)
extern vector<EmployeeData> Employee_vector;
extern vector<AccountData> Account_vector;

struct EmployeeData {
    int id;
    string name;
    string password;
};


struct AccountData;


// ---------------------------------
// Employee Class
// ---------------------------------
class Employee {
    string name;
    string password;
    string conf_pass;

public:
    static int employee_id;
    static int employee_count;

    Employee();                    // Constructor for signup
    Employee(string, string);      // Constructor for signin
    Employee(int);                 // Dummy constructor for account holder to use

    void employee_dashboard(int);  // Main dashboard
    void updateEmployee(int);
    void remove_account();
    void search_account();
    void transaction_history();
    void deposit_request(int, double, string);
    void withdraw_request(int, double, string);
};

#endif // EMPLOYEE_HPP

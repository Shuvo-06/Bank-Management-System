#ifndef ADMIN_H
#define ADMIN_H
#define ADMIN_PIN 1098765486


#include <bits/stdc++.h>
using namespace std;
void main_menu();
void complainBox();
void deposit_request(int,double);
void withdraw_request(int,double);


class AccountHolder{
   string name,nid,pass,conf_pass;
   double deposit;

   public:
       AccountHolder(double);
       AccountHolder(int);
       static void accntHolderInfo();
       void collect_info();



};



class Admin
{

    void manageEmployees();
    void employeeInfo();
    void cashManagement();
    void removeEmployee();
    void searchEmployee();

public:
    bool login(int);
    Admin();

};

class Employee {

    string name, password, conf_pass;

public:
    static int employee_id;
    static int employee_count;

    Employee();
    Employee(string,string);
    void collect_info();
    void employee_dashboard(int);
    void remove_account();
    void account_management();
    void search_account();



};



class SignUp
{
    string name, password, confirm_pass, nid;
    public:
    void signup_employee();
    void signup_general();
    SignUp();

};

class SignIn
{
public:
    SignIn();
    void signin_employee();
    void signin_general();
};

class Contact
{
public:
    Contact();

};

class About
{
public:
    About();
};

struct AccountData
{
    string name;
    string nid;
    string password;
    double deposit;
    vector<double> history;
};



struct EmployeeData
{
    int id;
    string name, password;
};




#endif

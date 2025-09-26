#ifndef ADMIN_H
#define ADMIN_H

#include <bits/stdc++.h>
using namespace std;
void main_menu();

class Admin
{

    void manageEmployees();
    void employeeInfo();
    void accntHolderInfo();
    void cashManagement();
    void complainBox();
    void removeEmployee();

public:
    bool login();
    Admin();

};

class Employee {

    string name, password, conf_pass;

public:
    static int employee_id;
    static int employee_count;

    Employee();
    void collect_info();
    bool check_data();
    void employee_dashboard();
};

class AccountHolder{
   string name,nid,pass,conf_pass;
   double deposit;

   public:
       AccountHolder(double);
       void collect_info();


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

#endif

#ifndef ADMIN_HPP
#define ADMIN_HPP

#include <bits/stdc++.h>
#include "employee.hpp"
#include "general.hpp"
using namespace std;

#define ADMIN_PIN 1098765486
#define STARTING_ID 2307000

class Admin {
public:
    Admin();
    static void view_employee();
    //static void cashManagement();
    static void removeEmployee();
    static void searchEmployee();
    static void employee_info();
    static void manageRates();
};


class Transaction{
public:
    //Overloaded operators
    friend AccountData operator +=(AccountData &, double);
    friend AccountData operator -=(AccountData &, double);

    //Other methods
    static void cashManagement();

};

class Loading{
   public:

       //Methods to load data

       void load_accounts();
       void load_employees();
       void load_complaints();
       void load_rates();
       void load_histories();

       //Parameterized Constructor
       Loading(int a){
           load_accounts();
           load_employees();
           load_complaints();
           load_rates();
           load_histories();
       }

       //Default Constructor
       Loading(){}

       //Methods to save data

       void save_accounts();
       void save_histories();
       void save_employees();
       void save_rates();
       void save_complaints();


       //Overloaded operator
       friend ostream& operator << (ostream &, AccountData &);

};

#endif

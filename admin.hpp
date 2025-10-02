#ifndef ADMIN_HPP
#define ADMIN_HPP

#include <bits/stdc++.h>
#include "employee.hpp"
using namespace std;

#define ADMIN_PIN 1098765486
#define STARTING_ID 2307000

class Admin {
public:
    Admin();
    static void view_employee();
    static void cashManagement();
    static void removeEmployee();
    static void searchEmployee();
    static void employee_info();
    static void manageRates();
};


#endif


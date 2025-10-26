#include "tools.hpp"
#include "admin.hpp"
#include "employee.hpp"
#include "general.hpp"
#include "sign.hpp"
#include "converter.hpp"
#include "complaint.hpp"
using namespace std;

/*-------------------------
        Admin Panel
--------------------------*/

//Overloaded Operators
AccountData operator +=(AccountData &cus, vector<double>&history){
    for(auto &val:history){
        if(val>=0) cus.deposit+=val;
        else cus.withdraw-=val;
    }

    return cus;
}

//AdminnFunctionalities
void Admin::employee_info()
{
    while (true)
    {
        vector<string> options = {"View Employee", "Search Employee", "Remove Employee", "Go Back"};
        int op = menu(options, "MANAGE EMPLOYEES");
        switch (op)
        {
        case 0:
            view_employee();
            break;
        case 1:
            searchEmployee();
            break;
        case 2:
            removeEmployee();
            break;
        case 3:
            return;
        }
    }
}

void Admin::view_employee()
{
    clear_screen();
    header("EMPLOYEE INFO", YELLOW, 100);
    cout << "+--------------+------------------------------+----------------------+\n";
    cout << "| " << RED << "ID" << RESET
         << "           | " << RED << "Name" << RESET
         << "                         | " << RED << "Password" << RESET << "             |\n";
    cout << "+--------------+------------------------------+----------------------+\n";

    for (auto &emp : Employee_vector)
    {
        string password = emp.password;
        Encryption::encrypt(password); // decrypt for display
        cout << "| " << setw(12) << left << emp.id
             << " | " << setw(28) << left << emp.name
             << " | " << setw(20) << left << password << " |\n";
    }
    cout << "+--------------+------------------------------+----------------------+\n";
    go_back();
    return;
}

void Admin::searchEmployee()
{
    clear_screen();
    string SID;
    Msg("Enter employee ID", "prompt");
    cin >> SID;
    for(auto &c:SID){
        if(!isdigit(c)){
            Msg("Invalid Input", "error");
            go_back();
            return;
        }
    }
    int sid= stoi(SID);

    auto it = lower_bound(Employee_vector.begin(), Employee_vector.end(), sid,
                          [](const EmployeeData &emp, int value)
    {
        return emp.id < value;
    });

    if (it != Employee_vector.end() && it->id == sid) Msg("Employee: " + it->name + " (ID: " + to_string(it->id) + ")", "info");
    else Msg("Employee with ID " + to_string(sid) + " not found!", "error");

    go_back();
    return;
}

void Admin::removeEmployee()
{
    clear_screen();
    string RID;
    Msg("Enter Employee ID", "prompt");
    cin >> RID;
    for(auto &c:RID){
        if(!isdigit(c)){
            Msg("Invalid Input", "error");
            go_back();
            return;
        }
    }
    int rid =stoi(RID);

    auto it = lower_bound(Employee_vector.begin(), Employee_vector.end(), rid,
                          [](const EmployeeData &emp, int value)
    {
        return emp.id < value;
    });

    if (it != Employee_vector.end() && it->id == rid)
    {
        Msg("Removing Employee: " + it->name + " (ID: " + to_string(it->id) + ")", "warning");
        Employee_vector.erase(it);
        Employee::employee_count = Employee_vector.size();
        Msg("Employee removed successfully!", "success");
    }
    else Msg("Employee with ID " + to_string(rid) + " not found!", "error");

    go_back();
    return;
}



void Admin::cashManagement()
{
    clear_screen();
    header("CASH MANAGEMENT", YELLOW, 100);
    double total_Deposit = 0.0;
    double total_Withdraw = 0.0;

    cout << "+----------------------+----------------------+----------------------+-----------------------------+\n";
    cout << "| " << RED << "NID" << RESET
         << "                  | " << RED << "Deposited" << RESET
         << "            | " << RED << "Withdrawn" << RESET
         << "            | " << RED << "Net Balance" << RESET << "                 |\n";
    cout << "+----------------------+----------------------+----------------------+-----------------------------+\n";

    for (int i = 0; i < (int)Account_vector.size(); i++) {

        AccountData sum;
        sum+= Account_vector[i].history;

        total_Deposit += sum.deposit;
        total_Withdraw += sum.withdraw;




        cout << "| " << setw(20) << left << Account_vector[i].nid
             << " | " << setw(20) << left << fixed << setprecision(2) << sum.deposit
             << " | " << setw(20) << left << fixed << setprecision(2) << sum.withdraw
             << " | " << setw(27) << left << fixed << setprecision(2) << (sum.deposit - sum.withdraw)
             << " |\n";
    }

    cout << "+----------------------+----------------------+----------------------+-----------------------------+\n";

    Msg("Total Deposited : " + to_string(total_Deposit), "info");
    Msg("Total Withdrawn : " + to_string(total_Withdraw), "info");
    Msg("Net Balance in Bank : " + to_string(total_Deposit - total_Withdraw), "info");

    go_back();
    return;
}
void Admin::manageRates()
{
   while(true){
    vector<string> options{"Edit Rate", "Add New Currency", "Remove Currency", "Exit"};
    int op = menu(options, "Exchange Rates");

    switch(op)
    {
    case 0:
    {
        int choice = menu(Converter::types, "Choose Currency Type : ");
        Msg("Type new rate", "prompt");

        string input;
        cin >> input;

        stringstream ss(input);
        double rate;
        if (!(ss >> rate) || !(ss.eof()) || rate <= 0)
        {
            Msg("Invalid rate! Must be a positive number.", "error");
            go_back();
            break;
        }

        Converter::rates[choice] = rate;
        Msg("Rate updated successfully!", "info");
        go_back();
            break;
    }
    case 1:
    {
        string new_currency, new_cur_rate;

        Msg("Enter currency name", "prompt");
        cin>>new_currency;

        if (new_currency.size() != 3 ||
                !isalpha(new_currency[0]) ||
                !isalpha(new_currency[1]) ||
                !isalpha(new_currency[2]))
        {
            Msg("Invalid currency name! Use 3 letters (e.g., USD).", "error");
            go_back();
            break;
        }

        Msg("Enter rate", "prompt");
        cin>>new_cur_rate;



        for (char &c : new_currency)
        {
            c = toupper(c);
        }
        stringstream ss(new_cur_rate);
        double rate;
        if (!(ss >> rate) || !(ss.eof()) || rate <= 0)
        {
            Msg("Invalid rate! Must be a positive number.", "error");
            go_back();
            break;
        }

        Converter::types.push_back(new_currency);
        Converter::rates.push_back(rate);
        Msg("Currency added successfully!", "success");
        go_back();
        break;
    }
    case 2:
    {
        int choice = menu(Converter::types, "Choose Currency Type : ");
        Converter::types.erase(Converter::types.begin() + choice);
        Converter::rates.erase(Converter::rates.begin() + choice);
        Msg("Deleted Successfully","success");
        go_back();
        break;
    }
    case 3:
    {
        return;
    }
    }
   }
}


Admin::Admin()
{
    string admin_pass;
    Msg("Enter Pin", "prompt");
    read_password(admin_pass);

    for(auto &c:admin_pass){
        if(!isdigit(c)){
            Msg("Invalid Input", "error");
            go_back();
            return;
        }
    }
    int admin_pin= stoi(admin_pass);
    if(admin_pin != ADMIN_PIN)
    {
        Msg("Password Incorrect. Access denied.","error");
        go_back();
        return;
    }

    while (true)
    {
        vector<string> options =
        {
            "Employee Info",
            "Account Holders Info",
            "Cash Management",
            "Manage Exchange Rates",
            "Complaints",
            "Sign Out"
        };

        int admin_option = menu(options, "ADMIN DASHBOARD");
        switch (admin_option)
        {
        case 0:
            employee_info();
            break;
        case 1:
            AccountHolder::accntHolderInfo();
            break;
        case 2:
            cashManagement();
            break;
        case 3:
            manageRates();
            break;
        case 4:
            Complaint::show_all_complains();
            break;
        case 5:
            return;
        }
    }
}

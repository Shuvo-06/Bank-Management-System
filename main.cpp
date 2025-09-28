#include <bits/stdc++.h>
#include "tools.hpp"
#include "admin.hpp"
using namespace std;

/*-----------------------------------------------------------------------
             Global Functions --> Name, NID and Password Validation
-------------------------------------------------------------------------*/

void main_menu();
static vector<AccountData> Account_vector;
static vector<EmployeeData> Employee_vector;
int Employee::employee_id = 2307000;
int Employee::employee_count = 0;



/* Name validity */
bool check_name_validity(const string &n)
{
    if (n.empty()) return false;
    if (!isupper(n[0])) return false;

    for (char c : n)
    {
        if (c == ' ') continue;
        if (!isalpha(c)) return false;
    }
    return true;
}

/* Password validity */
bool check_pass_validity(string p)
{
    if (p.length() < 8)
    {
        Msg("Password must be at least 8 characters long.","error");
        return false;
    }
    bool sp_char = false, upper = false, number = false;
    for (int i = 0; i < p.length(); i++)
    {
        if (isdigit(p[i])) number = true;
        if (isupper(p[i])) upper = true;
        if (!isdigit(p[i]) &&(p[i] < 65 || (p[i] > 90 && p[i] < 97) || p[i] > 122)) sp_char = true;
    }

    if (!number)
    {
        Msg("Password must contain at least 1 digit.","error");
        return false;
    }
    if (!upper)
    {
        Msg("Password must contain at least 1 uppercase letter.", "error");
        return false;
    }
    if (!sp_char)
    {
        Msg("Password must contain at least 1 special character.","error");
        return false;
    }
    return true;
}

/*NID validity*/
bool check_nid_validity(string nid)
{
    if(nid.length() != 10)
    {
        Msg("NID must be exactly 10 digits long", "error");
        return false;
    }

    for(char &c : nid)
    {
        if(!isdigit(c))
        {
            Msg("NID must contain digits only.", "error");
            return false;
        }
    }


    for(auto &acc:Account_vector)
    {
        if (acc.nid == nid)
        {
            Msg("This NID is already registered.", "error");
            return false;
        }
    }

    return true;
}

/*--------------------------------------
       Account Holder Section
---------------------------------------*/


/* Load accounts from file */
void loadAccounts(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line))
    {
        if (line.empty()) continue;
        stringstream ss(line);
        string name, nid, pass, depStr;
        getline(ss, name, ',');
        getline(ss, nid, ',');
        getline(ss, pass, ',');
        getline(ss, depStr);
        double dep = stod(depStr);
        Account_vector.push_back({name, nid, pass, dep});
    }
    file.close();
}
/*load accounts history from file*/
void loadHistory(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line))
    {
        if(line.empty()) continue;
        stringstream ss(line);
        string nid;
        double amount;
        ss >> nid >> amount;
        for (auto &acc : Account_vector)
        {
            if (acc.nid == nid)
            {
                acc.history.push_back(amount);
                break;
            }
        }
    }
    file.close();
}

/* Save accounts to file */
void saveAccounts(const string &filename)
{
    ofstream file(filename, ios::trunc);
    if (!file.is_open())
    {
        Msg("Error saving account data!", "warning");
        return;
    }
    for (auto &acc : Account_vector)
    {
        file << acc.name << "," << acc.nid << "," << acc.password << "," << acc.deposit << "\n";
    }
    file.close();
}

/* Account holder signup */
//Constructor for sign-up
AccountHolder::AccountHolder(double deposit=0.0)
{
    this->deposit = deposit;
    collect_info();
}
void AccountHolder::collect_info()
{
    while (true)
    {
        Msg("Name","prompt");
        getline(cin >> ws, name);
        if (check_name_validity(name)) break;
        else Msg("Invalid name. Try again.", "error");
    }

    while (true)
    {
        Msg("Password","prompt");
        read_password(pass);
        if (check_pass_validity(pass)) break;
    }

    while (true)
    {
        Msg("Retype Password","prompt");
        read_password(conf_pass);
        if (pass != conf_pass)
        {
            Msg("Passwords don't match! Type again.", "error");
        }
        else
        {
            Encryption::encrypt(pass);
            break;
        }
    }


    while(true)
    {
        Msg("NID Number","prompt");
        cin>>nid;
        if(check_nid_validity(nid))break;


    }
    Account_vector.push_back({name, nid, pass, deposit});
    saveAccounts("customer.txt");
    Msg("Congrats! You have successfully signed up!","success");
    go_back();
    return;
}



//Constructor for sign-in
AccountHolder::AccountHolder(int index, string nid)
{
    Employee emp(100);
    while (true)
    {
        vector<string> options =
        {
            "Balance Enquiry",
            "Deposit Money",
            "Withdraw Money",
            "Transaction History",
            "Complain Box",
            "Sign Out"
        };

        int choice = menu(options, "ACCOUNT HOLDER DASHBOARD");
        switch (choice)
        {
        case 0:
         {
            ostringstream oss;
            oss<<fixed <<setprecision(2)<< Account_vector[index].deposit;
            Msg("Your Current Balance: " + oss.str(), "info");
            go_back();
            break;
         }
        case 1:
        {
            double amount;
            Msg("Enter amount to deposit", "prompt");
            cin >> amount;
            emp.deposit_request(index, amount);

            go_back();
            break;
        }

        case 2:
        {
            double amount;
            Msg("Enter amount to withdraw", "prompt");
            cin >> amount;
            emp.withdraw_request(index, amount);
            go_back();
            break;
        }

        case 3:
        {
            subHeader("Transaction History",RED, 60);
            cout << BOLD << YELLOW
                 << "+----------------+------------------------------+\n"
                 << "|      Status    |           Amount             |\n"
                 << "+----------------+------------------------------+\n" << RESET;


            for (double t : Account_vector[index].history)
            {
                string type = (t >= 0 ? "Deposit" : "Withdrawal");

                string color = (t >= 0 ? GREEN : RED);

                cout << "| " << setw(14) << left << type
                     << " | " << color << setw(28) << left << fixed << setprecision(2) << fabs(t) << RESET << " |\n";
            }

            cout << BOLD << YELLOW
                 << "+----------------+------------------------------+\n" << RESET;



            go_back();
            break;
        }

        case 4:
            complainBox();
            break;

        case 5:
            return;
        }

    }



}
/*Account Holder Info*/

void AccountHolder::accntHolderInfo()
{
    clear_screen();
    header("ACCOUNT HOLDERS INFO", CYAN, 100);
    cout << "+----------------------------------+------------------+------------------+--------------------------------+\n";
    cout << "| " << RED << "Name" << RESET
         << "                             | " << RED << "NID" << RESET
         << "              | " << RED << "Password" << RESET
         << "         | " << RED << "Deposit" << RESET << "                        |\n";
    cout << "+----------------------------------+------------------+------------------+--------------------------------+\n";

    for (auto &acc : Account_vector)
    {
        string pass = acc.password;
        Encryption::encrypt(pass);

        cout << "| " << setw(28) << left << acc.name
             << "     | " << setw(16) << left << acc.nid
             << " | " << setw(16) << left << pass
             << " | " << setw(30) << right << fixed << setprecision(2) << acc.deposit << " |\n";
    }

    cout << "+----------------------------------+------------------+------------------+--------------------------------+\n";
    go_back();
    return;
}


/*save account history into file*/
void saveHistory(const string &filename)
{
    ofstream file(filename, ios::trunc);
    if (!file.is_open()) return;
    for (auto &acc : Account_vector)
    {
        for (double t : acc.history)
        {
            file << acc.nid << " " << t << "\n";
        }
    }
    file.close();
}

/*---------------------------------
        Employee Section
----------------------------------*/
Employee::Employee(int)
{
//Empty constructor for account holder to use
}

/* Load employees */
void loadEmployees(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line))
    {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, name, pass;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, pass);
        int id = stoi(idStr);
        Employee_vector.push_back({id, name, pass});
        Employee::employee_id = id;
    }
    Employee::employee_count = Employee_vector.size();
    file.close();
}

/* Save employees */
void saveEmployees(const string &filename)
{
    ofstream file(filename, ios::trunc);
    if (!file.is_open())
    {
        Msg("Error saving employee data!","warning");
        return;
    }
    for (auto &emp : Employee_vector)
    {
        file << emp.id << "," << emp.name << "," << emp.password << "\n";
    }
    file.close();
}

/* Employee signup */
void Employee::collect_info()
{
    while (true)
    {
        Msg("Name","prompt");
        getline(cin >> ws, name);
        if (check_name_validity(name)) break;
        else Msg("Invalid name. Try again.", "error");
    }

    while (true)
    {
        Msg("Password","prompt");
        read_password(password);
        if (check_pass_validity(password)) break;
    }

    while (true)
    {
        Msg("Retype Password","prompt");
        read_password(conf_pass);
        if (password != conf_pass)
        {
            Msg("Passwords don't match! Type again.", "error");
        }
        else
        {
            Encryption::encrypt(password);
            break;
        }
    }


    Employee_vector.push_back({employee_id, name, password});
    saveEmployees("employee.txt");
    Msg("Congrats! You signed up successfully as our Employee!","success");
    cout<<"Your ID: "<<CYAN<<Employee:: employee_id<<RESET;
    go_back();
    return;
}

//Constructor for SignUp
Employee::Employee()
{
    ++employee_id;
    ++employee_count;
    collect_info();
}

//Constructor for SignIn
Employee::Employee(string name, string password)
{
    this->name=name;
    this->password=password;

}

/*Employee SignIn*/
void Employee::employee_dashboard(int id)
{
    clear_screen();

    while (true)
    {
        vector<string> options =
        {
            "View Account Holder Info",
            "Search Account",
            "Remove Account Holder",
            "Transaction History",
            "Complaints",
            "Sign Out"
        };
        int employee_option = menu(options, "EMPLOYEE DASHBOARD");

        switch (employee_option)
        {
        case 0:
            AccountHolder::accntHolderInfo();
            break;
        case 1:
            search_account();
            break;
        case 2:
            remove_account();
            break;
        case 3:
            transaction_history();
            break;
        case 4:
            complainBox();
            break;
        default:
            return;
        }
    }


}
void Employee::remove_account()
{
    clear_screen();
    string nrid;
    Msg("Enter Account NID","prompt");
    cin >> nrid;

    auto it = lower_bound(Account_vector.begin(), Account_vector.end(), nrid,
                          [](const AccountData &acc, string value)
    {
        return acc.nid < value;
    });

    if (it != Account_vector.end() && it->nid == nrid)
    {
        Msg("Removing Account Holder: " + it->name + " (ID: " + it->nid + ")", "success");
        Account_vector.erase(it);
    }
    else
    {
        Msg("Account with NID " + nrid + " not found!", "error");
    }

    go_back();
    return;
}
void Employee::search_account()
{
    clear_screen();
    string sid;
    Msg("Enter Account ID","prompt");
    cin>>sid;

    auto it = lower_bound(Account_vector.begin(), Account_vector.end(), sid,
                          [](const AccountData &acc, string value)
    {
        return acc.nid < value;
    });
    if (it != Account_vector.end() && it->nid == sid)
    {
        Msg("Account: " + it->name + " (ID: " + it->nid + ") << Balance: " + to_string(it->deposit), "info");
    }
    else
    {
        Msg("Account with ID " + sid + " not found!", "error");
    }

    go_back();
    return;
}
void Employee::transaction_history()
{
    clear_screen();
    header("Transaction History", MAGENTA, 60);

    string nid;
    Msg("Enter Account NID","prompt");
    cin >> nid;

    int index = -1;
    for (int i = 0; i < Account_vector.size(); i++)
    {
        if (Account_vector[i].nid == nid)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        Msg("Account not found.","error");
        go_back();
        return;
    }
    double amount;

    subHeader("Transaction History for NID: " + nid, RESET, 60);
    cout << BOLD << YELLOW
         << "+------------------+------------------------------+\n"
         << "|      Status      |           Amount             |\n"
         << "+------------------+------------------------------+\n" << RESET;


    for (double t : Account_vector[index].history)
    {
        string type = (t >= 0 ? "Deposit" : "Withdrawal");

        string color = (t >= 0 ? GREEN : RED);

        cout << "| " << setw(14) << left << type
             << "   | " << color << setw(28) << left << fixed << setprecision(2) << fabs(t) << RESET << " |\n";
    }

    cout << BOLD << YELLOW
         << "+------------------+------------------------------+\n" << RESET;



    go_back();

}
void Employee::deposit_request(int index, double amount)
{
    if (amount <= 0)
    {
        Msg("Invalid deposit amount","error");
        return;
    }

    Account_vector[index].deposit += amount;
    Account_vector[index].history.push_back(amount); // Positive for deposit
    ostringstream oss;
    oss <<fixed << std::setprecision(2);
    oss << amount << ". New balance: " << Account_vector[index].deposit;

    Msg("Successfully deposited " + oss.str(), "success");

    saveAccounts("customer.txt");
    saveHistory("history.txt");
}
void Employee:: withdraw_request(int index, double amount)
{
    if (amount <= 0)
    {
        Msg("Invalid withdrawal amount.","error");
        return;
    }

    if (Account_vector[index].deposit < amount)
    {
        Msg("Insufficient balance.","warning");
        return;
    }

    Account_vector[index].deposit -= amount;
    Account_vector[index].history.push_back(-amount); // Negative for withdrawal
    ostringstream oss;
    oss << fixed << std::setprecision(2);
    oss << amount << ". New balance: " << Account_vector[index].deposit;

    Msg("Successfully dwithdrew " + oss.str(), "success");


    saveAccounts("customer.txt");
    saveHistory("history.txt");
}


/*-------------------------------
         Sign Up Section
--------------------------------*/
SignUp::SignUp()
{
    while (true)
    {
        vector<string> SignUp_menu = {"Employee", "General", "Go Back"};
        int op = menu(SignUp_menu,"SIGN UP");
        switch (op)
        {
        case 0:
            signup_employee();
            break;
        case 1:
            signup_general();
            break;
        case 2:
            return;
        }
    }
}
void SignUp::signup_employee()
{
    Employee employee;
}
void SignUp::signup_general()
{
    AccountHolder customer;
}



/*-------------------------------
         Sign In Section
--------------------------------*/
SignIn::SignIn()
{
    while (true)
    {
        vector<string> SignIn_menu = {"Admin", "Employee", "General", "Go Back"};
        int op = menu(SignIn_menu,"SIGN IN");
        switch (op)
        {
        case 0:
        {
            Admin admin;
            break;
        }
        case 1:
            signin_employee();
            break;
        case 2:
            signin_general();
            break;
        case 3:
            return;
        }
    }
}
void SignIn::signin_employee()
{
    int login_id;
    string login_pass;
    Msg("Enter Your ID","prompt");
    cin>>login_id;

    Msg("Enter Password","prompt");
    read_password(login_pass);
    auto it = lower_bound(Employee_vector.begin(), Employee_vector.end(), login_id,
                          [](const EmployeeData &emp, int value)
    {
        return emp.id < value;
    });
    if(it==Employee_vector.end())
    {
        Msg("Sorry Wrong Credentials.","error");
    }
    else
    {
        Encryption::encrypt(login_pass);
        if(it->password!=login_pass)
        {
            Msg("Sorry Wrong Credentials.","error");
        }
        else
        {
            Employee temp(it->name, it->password);
            temp.employee_dashboard(it->id);
        }
    }

    go_back();
}
void SignIn::signin_general()
{
    string name,nid,password;
    Msg("Enter Your NID","prompt");
    cin>>nid;
    Msg("Enter Password","prompt");
    read_password(password);

    int index=-1;
    for(int i=0; i<Account_vector.size(); i++)
    {
        if(Account_vector[i].nid==nid)
        {
            index=i;
            break;
        }
    }
    if(index==-1)
    {
        Msg("Sorry Wrong Credentials.","error");
    }
    else
    {
        Encryption::encrypt(password);
        if(Account_vector[index].password!=password)
        {
            Msg("Sorry Wrong Credentials.","error");
        }
        else
        {
            AccountHolder temp(index,Account_vector[index].nid);
        }
    }

    go_back();
}

/*-------------------------------
         Contact & About
--------------------------------*/
Contact::Contact()
{
    clear_screen();
    cout << "Contact info...\n";
    go_back();
}
About::About()
{
    clear_screen();
    Msg("5 random lads and 2 ladies from KUET CSE","info");
    go_back();

}

/*-------------------------
        Admin Panel
--------------------------*/
bool Admin::login(int pin)
{
    return (pin == ADMIN_PIN);
}

Admin::Admin()
{
    string admin_pass;
    Msg("Enter Pin","prompt");
    read_password(admin_pass);

    int admin_pin= stoi(admin_pass);
    if(!login(admin_pin))
    {
        Msg("Password Incorrect. Acess deined.","error");
        go_back();
        return;
    }
    while (true)
    {
        vector<string> options =
        {
            "Employee Info",
            "Manage Employees",
            "Account Holders Info",
            "Cash Management",
            "Complaints",
            "Sign Out"
        };
        int admin_option = menu(options, "ADMIN DASHBOARD");
        switch (admin_option)
        {
        case 0:
            employeeInfo();
            break;
        case 1:
            manageEmployees();
            break;
        case 2:
            AccountHolder::accntHolderInfo();
            break;
        case 3:
            cashManagement();
            break;
        case 4:
            complainBox();
            break;
        case 5:
            return;
        }
    }
}

void Admin::manageEmployees()
{
    while (true)
    {
        vector<string> options = {"View Employee","Search Employee", "Remove Employee", "Go Back"};
        int op = menu(options, "MANAGE EMPLOYEES");
        switch (op)
        {
        case 0:
            employeeInfo();
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

void Admin::employeeInfo()
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
    int sid;
    Msg("Enter employee ID", "prompt");
    cin >> sid;

    auto it = lower_bound(Employee_vector.begin(), Employee_vector.end(), sid,
                          [](const EmployeeData &emp, int value)
    {
        return emp.id < value;
    });

    if (it != Employee_vector.end() && it->id == sid)
    {
        Msg("Employee: " + it->name + " (ID: " + to_string(it->id) + ")", "info");
    }
    else
    {
        Msg("Employee with ID " + to_string(sid) + " not found!", "error");
    }

    go_back();
    return;
}

void Admin::removeEmployee()
{
    clear_screen();
    int rid;
    Msg("Enter Employee ID", "prompt");
    cin >> rid;

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
    else
    {
        Msg("Employee with ID " + to_string(rid) + " not found!", "error");
    }

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

    for (size_t i = 0; i < Account_vector.size(); i++)
    {
        double deposit = 0.0, withdraw = 0.0;

        
        for (size_t j = 0; j < Account_vector[i].history.size(); j++)
        {
            if (Account_vector[i].history[j] > 0)
                deposit += Account_vector[i].history[j];
            else
                withdraw += (-Account_vector[i].history[j]);
        }

       
        total_Deposit += deposit;
        total_Withdraw += withdraw;

      
        cout << "| " << setw(20) << left << Account_vector[i].nid
             << " | " << setw(20) << left << fixed << setprecision(2) << deposit
             << " | " << setw(20) << left << fixed << setprecision(2) << withdraw
             << " | " << setw(27) << left << fixed << setprecision(2) << (deposit - withdraw)
             << " |\n";
    }

    cout << "+----------------------+----------------------+----------------------+-----------------------------+\n";

    Msg("Total Deposited : " + to_string(total_Deposit), "info");
    Msg("Total Withdrawn : " + to_string(total_Withdraw), "info");
    Msg("Net Balance in Bank : " + to_string(total_Deposit - total_Withdraw), "info");

    go_back();
    return;
}


void complainBox()
{
    clear_screen();
    cout << "Complaints...\n";
    go_back();
    return;
}

/*-------------------------
        Main Menu
--------------------------*/
void main_menu()
{
    while (true)
    {
        vector<string> options = {"Sign Up", "Sign In", "Contact Info", "About Us", "Exit"};
        int option = menu(options, "WELCOME TO XYZ BANK");
        switch (option)
        {
        case 0:
        {
            SignUp signup;
            break;
        }
        case 1:
        {
            SignIn signin;
            break;
        }
        case 2:
        {
            Contact contact;
            break;
        }
        case 3:
        {
            About about;
            break;
        }
        case 4:
            return; // exit program
        }
    }
}

int main()
{
    loadAccounts("customer.txt");
    loadEmployees("employee.txt");
    loadHistory("history.txt");
    main_menu();
    saveAccounts("customer.txt");
    saveEmployees("employee.txt");
    saveHistory("history.txt");
    return 0;
}



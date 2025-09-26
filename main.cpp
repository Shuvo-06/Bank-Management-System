#include <bits/stdc++.h>
#include "tools.hpp"
#include "admin.hpp"
using namespace std;

/*-----------------------------------------------------------------------
             Global Functions --> Name and Password Validation
-------------------------------------------------------------------------*/

void main_menu();

/* Name validity */
bool check_name_validity(string n) {
    for (int i = 0; i < n.length(); i++) {
        if (!isupper(n[0])) return false;
        if (n[i] < 65) return false;
        if (n[i] > 90 && n[i] < 97) return false;
        if (n[i] > 122) return false;
    }
    return true;
}

/* Password validity */
bool check_pass_validity(string p) {
    if (p.length() < 8) {
        cout << "Password must be at least 8 characters long.\n";
        return false;
    }
    bool sp_char = false, upper = false, number = false;
    for (int i = 0; i < p.length(); i++) {
        if ((p[i] - '0') >= 0 && (p[i] - '0' <= 9)) number = true;
        if (p[i] >= 65 && p[i] <= 90) upper = true;
        if (p[i] < 65 || (p[i] > 90 && p[i] < 97) || p[i] > 122 && !(p[i] - '0') >= 0 && (p[i] - '0' <= 9)) sp_char = true;
    }

    if (!number) { cout << "Password must contain at least 1 digit."; return false; }
    if (!upper) { cout << "Password must contain at least 1 uppercase letter."; return false; }
    if (!sp_char) { cout << "Password must contain at least 1 special character."; return false; }
    return true;
}

/*--------------------------------------
       Account Holder Section
---------------------------------------*/
struct AccountData {
    string name;
    string nid;
    string password;
    double deposit;
};

static vector<AccountData> Account_vector;

/* Load accounts from file */
void loadAccounts(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
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

/* Save accounts to file */
void saveAccounts(const string &filename) {
    ofstream file(filename, ios::trunc);
    if (!file.is_open()) {
        cout << "Error saving account data!\n";
        return;
    }
    for (auto &acc : Account_vector) {
        file << acc.name << "," << acc.nid << "," << acc.password << "," << acc.deposit << "\n";
    }
    file.close();
}

/* Account holder signup */
AccountHolder::AccountHolder(double deposit=0.0) {
    this->deposit = deposit;
    collect_info();
}
void AccountHolder::collect_info() {
    while (true) {
        cout << "Name: ";
        cin >> name;
        if (check_name_validity(name)) break;
        else cout << "Invalid name. Please try again.\n";
    }

    while (true) {
        cout << "Password: ";
        read_password(pass);
        if (check_pass_validity(pass)) break;
        else cout << "Please try again.\n";
    }

    while (true) {
        cout << "Retype Password: ";
        read_password(conf_pass);
        if (pass != conf_pass) {
            cout << "Passwords don't match! Type again.\n";
        } else {
            Encryption::encrypt(pass);
            break;
        }
    }

    cout << "NID Number: ";
    cin >> nid;
    Account_vector.push_back({name, nid, pass, deposit});
    cout<<"Congrats! From now on, you are our nigga customer!";
    go_back();
}

/*---------------------------------
        Employee Section
----------------------------------*/
struct EmployeeData {
    int id;
    string name, password;
};

static vector<EmployeeData> Employee_vector;

int Employee::employee_id = 2307000;
int Employee::employee_count = 0;

/* Load employees */
void loadEmployees(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
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
void saveEmployees(const string &filename) {
    ofstream file(filename, ios::trunc);
    if (!file.is_open()) {
        cout << "Error saving employee data!\n";
        return;
    }
    for (auto &emp : Employee_vector) {
        file << emp.id << "," << emp.name << "," << emp.password << "\n";
    }
    file.close();
}

/* Employee signup */
void Employee::collect_info() {
    while (true) {
        cout << "Name: ";
        cin >> name;
        if (check_name_validity(name)) break;
        else cout << "Invalid name. Please try again.\n";
    }

    while (true) {
        cout << "Password: ";
        read_password(password);
        if (check_pass_validity(password)) break;
        else cout << "Invalid Password. Please try again.\n";
    }

    while (true) {
        cout << "Retype Password: ";
        read_password(conf_pass);
        if (password != conf_pass) {
            cout << "Passwords don't match! Type again.\n";
        } else {
            Encryption::encrypt(password);
            break;
        }
    }

    Employee_vector.push_back({employee_id, name, password});
    cout<<"Congrats! You signed up successfully as our nigga kamla!";
    go_back();
}

Employee::Employee() {
    ++employee_id;
    ++employee_count;
    collect_info();
}

/*-------------------------------
         Sign Up Section
--------------------------------*/
SignUp::SignUp() {
    while (true) {
        vector<string> SignUp_menu = {"Employee", "General", "Go Back"};
        int op = menu(SignUp_menu, "SIGN UP");
        switch (op) {
            case 0: signup_employee(); break;
            case 1: signup_general(); break;
            case 2: return;
        }
    }
}
void SignUp::signup_employee() { Employee employee; }
void SignUp::signup_general() { AccountHolder customer; }

/*-------------------------------
         Sign In Section
--------------------------------*/
SignIn::SignIn() {
    while (true) {
        vector<string> SignIn_menu = {"Admin", "Employee", "General", "Go Back"};
        int op = menu(SignIn_menu, "SIGN IN");
        switch (op) {
            case 0: { Admin admin; break; }
            case 1: signin_employee(); break;
            case 2: signin_general(); break;
            case 3: return;
        }
    }
}
void SignIn::signin_employee() {
    cout << "Employee signing in...\n";
    go_back();
}
void SignIn::signin_general() {
    cout << "General signing in...\n";
    go_back();
}

/*-------------------------------
         Contact & About
--------------------------------*/
Contact::Contact() {
    clear_screen();
    cout << "Contact info...\n";
    go_back();
}
About::About() {
    clear_screen();
    cout << "Just 7 random guys from KUET CSE\n";
    go_back();

}

/*-------------------------
        Admin Panel
--------------------------*/
Admin::Admin() {
    while (true) {
        vector<string> options = {
            "Employee Info",
            "Manage Employees",
            "Account Holders Info",
            "Cash Management",
            "Complaints",
            "Go Back"
        };
        int admin_option = menu(options, "ADMIN DASHBOARD");
        switch (admin_option) {
            case 0: employeeInfo(); break;
            case 1: manageEmployees(); break;
            case 2: accntHolderInfo(); break;
            case 3: cashManagement(); break;
            case 4: complainBox(); break;
            case 5: return;
        }
    }
}

void Admin::manageEmployees() {
    while (true) {
        vector<string> options = {"View Employee", "Remove Employee", "Go Back"};
        int op = menu(options, "MANAGE EMPLOYEES");
        switch (op) {
            case 0: employeeInfo(); break;
            case 1: removeEmployee(); break;
            case 2: return;
        }
    }
}

void Admin::employeeInfo() {
    clear_screen();
    cout << "======================= " << CYAN << "EMPLOYEE INFO" << RESET << " =======================\n";
    cout << "+--------------+----------------------+----------------------+\n";
    cout << "| " << RED << "ID" << RESET
         << "           | " << RED << "Name" << RESET
         << "                 | " << RED << "Password" << RESET << "             |\n";
    cout << "+--------------+----------------------+----------------------+\n";

    for (auto &emp : Employee_vector) {
        string password = emp.password;
        Encryption::encrypt(password); // decrypt for display
        cout << "| " << setw(12) << left << emp.id
             << " | " << setw(20) << left << emp.name
             << " | " << setw(20) << left << password << " |\n";
    }
    cout << "+--------------+----------------------+----------------------+\n";
    go_back();
    return;
}

void Admin::accntHolderInfo() {
    clear_screen();
    cout << "=================== " << CYAN << "ACCOUNT HOLDERS INFO" << RESET << " ===================\n";
    cout << "+------------------+------------------+------------------+-------------+\n";
    cout << "| " << RED << "Name" << RESET
         << "             | " << RED << "NID" << RESET
         << "              | " << RED << "Password" << RESET
         << "          | " << RED << "Deposit" << RESET << "    |\n";
    cout << "+------------------+------------------+------------------+-------------+\n";

    for (auto &acc : Account_vector) {
        string pass = acc.password;
        Encryption::encrypt(pass);
        cout << "| " << setw(16) << left << acc.name
             << " | " << setw(16) << left << acc.nid
             << " | " << setw(16) << left << pass
             << " | " << setw(11) << left << acc.deposit << " |\n";
    }
    cout << "+------------------+------------------+------------------+-------------+\n";
    go_back();
    return;
}

void Admin::removeEmployee() {
    clear_screen();
    int rid;
    cout << "Enter Employee ID: ";
    cin >> rid;

    auto it = lower_bound(Employee_vector.begin(), Employee_vector.end(), rid,
        [](const EmployeeData &emp, int value) { return emp.id < value; });

    if (it != Employee_vector.end() && it->id == rid) {
        cout << "Removing Employee: " << it->name << " (ID: " << it->id << ")\n";
        Employee_vector.erase(it);
        Employee::employee_count = Employee_vector.size();
    } else {
        cout << "Employee with ID " << rid << " not found!\n";
    }

    go_back();
    return;
}

void Admin::cashManagement() {
    clear_screen();
    cout << "Cash Management...\n";
    go_back();
   
}

void Admin::complainBox() {
    clear_screen();
    cout << "Complaints...\n";
    go_back();
  
}

/*-------------------------
        Main Menu
--------------------------*/
void main_menu() {
    while (true) {
        vector<string> options = {"Sign Up", "Sign In", "Contact Info", "About Us", "Exit"};
        int option = menu(options, "WELCOME TO XYZ BANK");
        switch (option) {
            case 0: { SignUp signup; break; }
            case 1: { SignIn signin; break; }
            case 2: { Contact contact; break; }
            case 3: { About about; break; }
            case 4: exit(0); // exit program
        }
    }
}

int main() {
    loadAccounts("customer.txt");
    loadEmployees("employee.txt");
    main_menu();
    saveAccounts("customer.txt");
    saveEmployees("employee.txt");
    return 0;
}


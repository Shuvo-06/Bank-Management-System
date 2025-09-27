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
        cout << "Password must be at least 8 characters long.\n";
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
        cout << "Password must contain at least 1 digit.";
        return false;
    }
    if (!upper)
    {
        cout << "Password must contain at least 1 uppercase letter.";
        return false;
    }
    if (!sp_char)
    {
        cout << "Password must contain at least 1 special character.";
        return false;
    }
    return true;
}

/*NID validity*/
bool check_nid_validity(string nid)
{
    if(nid.length() != 10) {
        cout << "NID must be exactly 10 digits long.\n";
        return false;
    }

    for(char &c : nid) {
        if(!isdigit(c)){
            cout << "NID must contain digits only.\n";
            return false;
        }
    }


    for(auto &acc:Account_vector) {
        if (acc.nid == nid) {
            cout << "This NID is already registered.\n";
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
void loadHistory(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string nid;
        double amount;
        ss >> nid >> amount;
        for (auto &acc : Account_vector) {
            if (acc.nid == nid) {
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
        cout << "Error saving account data!\n";
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
        cout << "Name: ";
        getline(cin >> ws, name);
        if (check_name_validity(name)) break;
        else cout << "Invalid name. Please try again.\n";
    }

    while (true)
    {
        cout << "Password: ";
        read_password(pass);
        if (check_pass_validity(pass)) break;
        else cout << "Please try again.\n";
    }

    while (true)
    {
        cout << "Retype Password: ";
        read_password(conf_pass);
        if (pass != conf_pass)
        {
            cout << "Passwords don't match! Type again.\n";
        }
        else
        {
            Encryption::encrypt(pass);
            break;
        }
    }


    while(true){
         cout<<"NID Number: ";
         cin>>nid;
         if(check_nid_validity(nid))break;
         else cout<<"Please Try Again.";

    }
    Account_vector.push_back({name, nid, pass, deposit});
    saveAccounts("customer.txt");
    cout<<"Congrats! You have successfully signed up!";
    go_back();
    return;
}
//Construtor for sign-in
//==================================//
//              SADIK               //
//===================================//
AccountHolder::AccountHolder(int index){

  cout<<"Welcome Back "<<Account_vector[index].name<<"!";
  //Account holder Dashboard will be created using menu function
  //Following operations will be done in this section:
  //1. Balance Enquiry (just print Account_vector[index].deposit)
  //2. Request Deposit ( call rashed er banano function )
  //3. Request Withdraw ( call rashed er function)
  //4. Show Account History ( output the content of the vector Account_vector[index].history)
  //5. Complain Box
  //6. Go Back (call go_back() )
  cout<<"Account holder dashboard...TODO by SADIK.";


}
/*Account Holder Info*/
void AccountHolder::accntHolderInfo()
{
    clear_screen();
    cout << "================================ " << CYAN << "ACCOUNT HOLDERS INFO" << RESET << " ================================\n";
    cout << "+----------------------------------+------------------+------------------+-------------+\n";
    cout << "| " << RED << "Name" << RESET
         << "                             | " << RED << "NID" << RESET
         << "              | " << RED << "Password" << RESET
         << "         | " << RED << "Deposit" << RESET << "     |\n";
    cout << "+----------------------------------+------------------+------------------+-------------+\n";

    for (auto &acc : Account_vector)
    {
        string pass = acc.password;
        Encryption::encrypt(pass);
        cout << "| " << setw(28) << left << acc.name
             << "     | " << setw(16) << left << acc.nid
             << " | " << setw(16) << left << pass
             << " | " << setw(11) << left << acc.deposit << " |\n";
    }
    cout << "+----------------------------------+------------------+------------------+-------------+\n";
    go_back();
    return;
}
/*save account history into file*/
void saveHistory(const string &filename) {
    ofstream file(filename, ios::trunc);
    if (!file.is_open()) return;
    for (auto &acc : Account_vector) {
        for (double t : acc.history) {
            file << acc.nid << " " << t << "\n";
        }
    }
    file.close();
}

/*---------------------------------
        Employee Section
----------------------------------*/

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
        cout << "Error saving employee data!\n";
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
        cout << "Name: ";
        getline(cin >> ws, name);
        if (check_name_validity(name)) break;
        else cout << "Invalid name. Please try again.\n";
    }

    while (true)
    {
        cout << "Password: ";
        read_password(password);
        if (check_pass_validity(password)) break;
        else cout << "Invalid Password. Please try again.\n";
    }

    while (true)
    {
        cout << "Retype Password: ";
        read_password(conf_pass);
        if (password != conf_pass)
        {
            cout << "Passwords don't match! Type again.\n";
        }
        else
        {
            Encryption::encrypt(password);
            break;
        }
    }

    Employee_vector.push_back({employee_id, name, password});
    saveEmployees("employee.txt");
    cout<<"Congrats! You signed up successfully as our Employee!\n";
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
Employee::Employee(string name, string password){
  this->name=name;
  this->password=password;

}

//========================//
//         RASHED         //
//========================//
/*Employee SignIn*/
void Employee::employee_dashboard(int id){
  clear_screen();
  cout<<"Welcome "<<name;
    while (true)
    {
        vector<string> options =
        {
            "View Account Holder Info",
            "Search Account",
            "Remove Account Holder",
            "Account Management",
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
            account_management();
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
    cout << "Enter Account NID: ";
    cin >> nrid;

    auto it = lower_bound(Account_vector.begin(), Account_vector.end(), nrid,
                          [](const AccountData &acc, string value)
    {
        return acc.nid < value;
    });

    if (it != Account_vector.end() && it->nid == nrid)
    {
        cout << "Removing Account Holder: " << it->name << " (ID: " << it->nid << ")\n";
        Account_vector.erase(it);
    }
    else
    {
        cout << "Account with NID " << nrid << " not found!\n";
    }

    go_back();
    return;
}
void Employee::search_account()
{
        clear_screen();
    string sid;
    cout<<"Enter Account ID: ";
    cin>>sid;

        auto it = lower_bound(Account_vector.begin(), Account_vector.end(), sid,
                          [](const AccountData &acc, string value)
    {
        return acc.nid < value;
    });
        if (it != Account_vector.end() && it->nid == sid)
    {
        cout << "Account: " << it->name << " (ID: " << it->nid << ")<<Balance: "<<it->deposit<<"\n";
    }
    else
    {
        cout << "Account with ID " << sid << " not found!\n";
    }

    go_back();
    return;
}
void Employee::account_management()
{
          clear_screen();
    cout<<"Account Management"<<endl;

    string nid;
    cout << "Enter Account NID: ";
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
        cout << "Account not found.\n";
        go_back();
        return;
    }
    double amount;
        while (true)
    {
        clear_screen();
        vector<string> options =
        {
            "Account Withdrawal",
            "Account Deposit",
            "Transaction History",
            "Go Back"
        };
        int employee_option = menu(options, "ACCOUNT MANAGEMENT");
        switch (employee_option)
        {
        case 0:
            cout<<endl<<"Enter amount: ";
            cin>>amount;
            withdraw_request(index,amount);
            go_back();
            break;
        case 1:
            cout<<endl<<"Enter amount: ";
            cin>>amount;
            deposit_request(index,amount);
            go_back();
            break;
        case 2:
            cout << "Transaction History:\n";
            for (double t : Account_vector[index].history)
            {
                cout<<nid<<": ";
                if (t >= 0) cout << "+";
                cout << t << "\n";
            }
            go_back();
        break;
        case 3:
            return;
        }
    }
}
void deposit_request(int index, double amount)
{
    if (amount <= 0)
    {
        cout << "Invalid deposit amount.\n";
        return;
    }

    Account_vector[index].deposit += amount;
    Account_vector[index].history.push_back(amount); // Positive for deposit
    cout << "Successfully deposited " << amount << ". New balance: " << Account_vector[index].deposit << "\n";

    saveAccounts("customer.txt");
    saveHistory("history.txt");
}
void withdraw_request(int index, double amount)
{
    if (amount <= 0)
    {
        cout << "Invalid withdrawal amount.\n";
        return;
    }

    if (Account_vector[index].deposit < amount)
    {
        cout << "Insufficient balance.\n";
        return;
    }

    Account_vector[index].deposit -= amount;
    Account_vector[index].history.push_back(-amount); // Negative for withdrawal
    cout << "Successfully withdrew " << amount << ". New balance: " << Account_vector[index].deposit << "\n";

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
    cout<<"Enter Your ID: ";
    cin>>login_id;

    cout<<"Enter Password: ";
    read_password(login_pass);
    auto it = lower_bound(Employee_vector.begin(), Employee_vector.end(), login_id,
                          [](const EmployeeData &emp, int value)
    {
        return emp.id < value;
    });
    if(it==Employee_vector.end()){
        cout<<"Sorry Wrong Credentials.";
    }else{
        Encryption::encrypt(login_pass);
        if(it->password!=login_pass){
            cout<<"Sorry Wrong Credentials.";
        }else{
          Employee temp(it->name, it->password);
          temp.employee_dashboard(it->id);
        }
    }

    go_back();
}
void SignIn::signin_general()
{
    string name,nid,password;
    cout<<"Enter Your NID: ";
    cin>>nid;
    cout<<"Enter Password: ";
    read_password(password);

    int index=-1;
    for(int i=0; i<Account_vector.size(); i++){
        if(Account_vector[i].nid==nid){
            index=i;
            break;
        }
    }
    if(index==-1){
        cout<<"Sorry Wrong Credentials.";
    }else{
        Encryption::encrypt(password);
        if(Account_vector[index].password!=password){
            cout<<"Sorry Wrong Credentials.";
        }else{
          AccountHolder temp(index);
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
    cout << "5 random lads and 2 ladies from KUET CSE\n";
    go_back();

}

/*-------------------------
        Admin Panel
--------------------------*/
bool Admin::login(int pin){
  return (pin == ADMIN_PIN);
}

Admin::Admin()
{
    string admin_pass;
    cout<<"Enter Pin: ";
    read_password(admin_pass);

    int admin_pin= stoi(admin_pass);
    if(!login(admin_pin)){
        cout<<"Password incorrect. Access Denied.";
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
    cout << "========================== " << CYAN << "EMPLOYEE INFO" << RESET << " ==========================\n";
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
    cout<<"Enter employee ID: ";
    cin>>sid;

        auto it = lower_bound(Employee_vector.begin(), Employee_vector.end(), sid,
                          [](const EmployeeData &emp, int value)
    {
        return emp.id < value;
    });
        if (it != Employee_vector.end() && it->id == sid)
    {
        cout << "Employee: " << it->name << " (ID: " << it->id << ")\n";
    }
    else
    {
        cout << "Employee with ID " << sid << " not found!\n";
    }

    go_back();
    return;
}
void Admin::removeEmployee()
{
    clear_screen();
    int rid;
    cout << "Enter Employee ID: ";
    cin >> rid;

    auto it = lower_bound(Employee_vector.begin(), Employee_vector.end(), rid,
                          [](const EmployeeData &emp, int value)
    {
        return emp.id < value;
    });

    if (it != Employee_vector.end() && it->id == rid)
    {
        cout << "Removing Employee: " << it->name << " (ID: " << it->id << ")\n";
        Employee_vector.erase(it);
        Employee::employee_count = Employee_vector.size();
    }
    else
    {
        cout << "Employee with ID " << rid << " not found!\n";
    }

    go_back();
    return;
}
//=========================//
//         TAHMINA         //
//=========================//
void Admin::cashManagement()
{
    clear_screen();
    cout << "==================================== " << CYAN << "CASH MANAGEMENT" << RESET << " =======================================\n";
    double total_Deposit = 0.0;
    double total_Withdraw = 0.0;

    cout << "+----------------------+----------------------+----------------------+----------------------+\n";
    cout << "| " << RED << "NID" << RESET
         << "                  | " << RED << "Deposited" << RESET
         << "            | " << RED << "Withdrawn" << RESET
         << "            | " << RED << "Net Balance" << RESET << "          |\n";
    cout << "+----------------------+----------------------+----------------------+----------------------+\n";

    for (size_t i = 0; i < Account_vector.size(); i++)
    {
        double deposit = 0.0, withdraw = 0.0;

        // calculate per-account deposits & withdrawals
        for (size_t j = 0; j < Account_vector[i].history.size(); j++)
        {
            if (Account_vector[i].history[j] > 0)
                deposit += Account_vector[i].history[j];
            else
                withdraw += (-Account_vector[i].history[j]);
        }

        // update global totals
        total_Deposit += deposit;
        total_Withdraw += withdraw;

        // print account line with larger spacing
        cout << "| " << setw(20) << left << Account_vector[i].nid
             << " | " << setw(20) << left << deposit
             << " | " << setw(20) << left << withdraw
             << " | " << setw(20) << left << (deposit - withdraw)
             << " |\n";
    }

    cout << "+----------------------+----------------------+----------------------+----------------------+\n";
    cout << "Total Deposited : " << total_Deposit << "\n";
    cout << "Total Withdrawn : " << total_Withdraw << "\n";
    cout << "Net Balance in Bank : " << (total_Deposit - total_Withdraw) << "\n";

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



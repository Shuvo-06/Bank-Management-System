#include <bits/stdc++.h>
#include "tools.hpp"
#include "sign.hpp"
#include "admin.hpp"
#include "employee.hpp"
#include "general.hpp"
#include "converter.hpp"
#include "complaint.hpp"
using namespace std;

/*-----------------------------------------------------------------------
             Global Functions --> Name, NID and Password Validation
-------------------------------------------------------------------------*/

vector<AccountData> Account_vector;
vector<EmployeeData> Employee_vector;

//Overloaded operators
ostream& operator << (ostream & output, AccountData &acc){
  for(auto &t : acc.history){
    output << acc.nid << " " << t << "\n";
  }
  return output;

}


/* Load accounts from file */
void load_accounts() {
    ifstream file("customer.txt");
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

/* Load employees */
void load_employees() {
    ifstream file("employee.txt");
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
    file.close();

    Employee::employee_count = Employee_vector.size();
    Employee::employee_id = STARTING_ID + Employee_vector.size();
}

/*load accounts history from file*/
void load_histories() {
    ifstream file("history.txt");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if(line.empty()) continue;

        stringstream ss(line);
        string nid;
        double amount;
        ss >> nid >> amount;

        // accounts will be sorted according to their ID
        int lo = 0, hi = Account_vector.size();

        while (lo <= hi) {
            int mid = (lo + hi) / 2;

            if (Account_vector[mid].nid == nid) {
                Account_vector[mid].history.push_back(amount);
                break;
            }
            else if (Account_vector[mid].nid > nid) hi = mid - 1;
            else lo = mid + 1;
        }
    }
    file.close();
}

void load_rates() {
    ifstream file("converter.txt");

    if (!file.is_open()) {
        Msg("Something went wrong.", "error");
        return;
    }

    Converter::types.clear();
    Converter::rates.clear();

    string type;
    double rate;
    while (file >> type >> rate) {
        Converter::types.push_back(type);
        Converter::rates.push_back(rate);
    }

    file.close();

    if (count(Converter::types.begin(), Converter::types.end(), "BDT") == 0) {
        Converter::types.push_back("BDT");
        Converter::rates.push_back(1.00);
    }
}

/* Save accounts to file */
void save_accounts() {
    ofstream file("customer.txt", ios::trunc); // ios :: trunc tells compiler to override the file
    if (!file.is_open()) {
        Msg("Error saving account data!", "warning");
        return;
    }

    for (auto &acc : Account_vector) {
        file << acc.name << "," << acc.nid << "," << acc.password << "," << acc.deposit << "\n";
    }

    file.close();
}

/* Save employees */
void save_employees() {
    ofstream file("employee.txt", ios::trunc); // ios :: trunc tells compiler to override the file
    if (!file.is_open()) {
        Msg("Error saving employee data!","warning");
        return;
    }

    for (auto &emp : Employee_vector) {
        file << emp.id << "," << emp.name << "," << emp.password << "\n";
    }
    file.close();
}


/*save account history into file*/
void save_histories() {
    ofstream file("history.txt", ios::trunc);
    if (!file.is_open()) return;
    for (auto &acc : Account_vector) {
         file<< acc;
    }
    file.close();
}

void save_rates() {
    ofstream file("converter.txt", ios::trunc);

    if (!file.is_open()) {
        Msg("Something went wrong.", "error");
        return;
    }

    for (int i = 0; i < (int)Converter::types.size(); i++) {
        if (Converter::types[i] == "BDT") continue;
        file << Converter::types[i] << " " << Converter::rates[i] << "\n";
    }

    file.close();
}




void load_complaints() {
    Complaints_vector_t.clear();
    Complaints_vector_n.clear();

    ifstream file("complaints.txt");
    if (!file.is_open()) {
        Msg("Something went wrong", "error");
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string nid, status, complain;

        getline(ss, nid, '|');
        getline(ss, status, '|');
        getline(ss, complain); // rest of the line

        Complaints c;
        c.nid = nid;
        c.resolved = (status == "1");
        c.complain = complain;
        Complaints_vector_t.push_back(c);
        Complaints_vector_n[nid].push_back(c);
    }

    file.close();
}

void save_complaints() {
    ofstream file("complaints.txt", ios::trunc);
    if (!file.is_open()) {
        Msg("Something went wrong", "error");
        return;
    }

    for (auto &c : Complaints_vector_t) {
        file << c.nid << "|" << (c.resolved ? "1" : "0") << "|" << c.complain << "\n";
    }

    file.close();
}

int main() {
    SetConsoleCtrlHandler(ConsoleHandler, TRUE);  // <--- for 'x' users :)

    // Loads data from previous runs
    load_accounts();
    load_histories();
    load_complaints();
    load_rates();
    load_employees();

    while (true) { // main menu
        vector<string> options = {"Sign Up", "Sign In", "Contact Info", "About Us", "Exit"};
        int option = menu(options, "WELCOME TO XYZ BANK");
        switch (option) {
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
            clear_screen();
            read_entire_file("contact.txt");
            go_back();
            break;
        }
        case 3:
        {
            clear_screen();
            read_entire_file("about.txt");
            go_back();
            break;
        }
        case 4:
            save_accounts();
            save_employees();
            save_histories();
            save_rates();
            save_complaints();
            return 0; // exit program
        }
    }
}

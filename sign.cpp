#include "tools.hpp"
#include "admin.hpp"
#include "employee.hpp"
#include "general.hpp"
#include "sign.hpp"
#include "complaint.hpp"
/*-------------------------------
         Sign Up Section
--------------------------------*/
SignUp::SignUp() {
    while (true) {
        vector<string> SignUp_menu = {"Employee", "General", "Go Back"};
        int op = menu(SignUp_menu,"SIGN UP");

        if (op == 0) Employee employee;
        else if (op == 1) AccountHolder customer;
        else  return;
    }
}


/*-------------------------------
         Sign In Section
--------------------------------*/
SignIn::SignIn() {
    while (true) {
        vector<string> SignIn_menu = {"Admin", "Employee", "General", "Go Back"};
        int op = menu(SignIn_menu,"SIGN IN");
        switch (op) {
            case 0:
            {
                Admin admin;
                break;
            }
            case 1:
            {
                signin_employee();
                break;
            }
            case 2:
            {
                signin_general();
                break;
            }
            case 3: return;
        }
    }
}

void SignIn::signin_employee() {
    string loginId;
    string login_pass;

    Msg("Enter Your ID","prompt");
    cin>>loginId;
    int login_id;
    try {
        login_id = stoi(loginId); // safe conversion
    } catch (...) {
        Msg("Invalid ID format!", "error");
        go_back();
        return;
    }

    Msg("Enter Password","prompt");
    read_password(login_pass);

    auto it = lower_bound(Employee_vector.begin(), Employee_vector.end(), login_id,
                          [](const EmployeeData &emp, int value) {
                                return emp.id < value;
                            }
    );

    if(it == Employee_vector.end() || it->id != login_id) Msg("Wrong Credentials.","error");
    else {
        Encryption::encrypt(login_pass);
        if(it -> password != login_pass) Msg("Wrong Credentials.","error");
        else {
            Employee temp(it->name, it->password);
            temp.employee_dashboard(it->id);
        }
    }
    go_back();
}

void SignIn::signin_general() {
    string nid, password;

    Msg("Enter Your NID", "prompt");
    cin >> nid;
    if(nid=="0"){
        Msg("Your Account Has Been Deleted","Warning");
        go_back();
        return;
    }

    Msg("Enter Password", "prompt");
    read_password(password);

    int index = -1;
    for(int i = 0; i < (int)Account_vector.size(); i++) {
        if(Account_vector[i].nid == nid) {
            index = i;
            break;
        }
    }

    if(index == -1) Msg("Wrong Credentials.","error");
    else {
        Encryption::encrypt(password);

        if(Account_vector[index].password != password) Msg("Wrong Credentials.","error");
        else AccountHolder temp(index, Account_vector[index].nid);
    }

    go_back();
}

#include "employee.hpp"
#include "tools.hpp"
#include "complaint.hpp"
/*---------------------------------
        Employee Section
----------------------------------*/
int Employee::employee_id;  // starting ID
int Employee::employee_count;


Employee::Employee(int) {} //Empty constructor for account holder to use

//Constructor for SignUp
Employee::Employee()
{
    ++employee_id;
    ++employee_count;

    for (int i = 1; i <= ENTRY_LIMIT; i++)
    {
        Msg("Name", "prompt");
        getline(cin >> ws, name);
        if (check_name_validity(name)) break;
        else
        {
            if (i == ENTRY_LIMIT)
            {
                Msg("Try again later", "error");
                go_back();
                return;
            }
            else Msg("Invalid name. Try again.", "error");
        }
    }

    for (int i = 1; i <= ENTRY_LIMIT; i++)
    {
        Msg("Password", "prompt");
        read_password(password);
        if (check_pass_validity(password)) break;
        else
        {
            if (i == ENTRY_LIMIT)
            {
                Msg("Try again later", "error");
                go_back();
                return;
            }
        }
    }

    for (int i = 1; i <= ENTRY_LIMIT; i++)
    {
        Msg("Retype Password", "prompt");
        read_password(conf_pass);
        if (password != conf_pass)
        {
            if (i == ENTRY_LIMIT)
            {
                Msg("Try again later.", "error");
                go_back();
                return;
            }
            else Msg("Passwords don't match! Type again.", "error");
        }
        else
        {
            Encryption::encrypt(password);
            break;
        }
    }


    Employee_vector.push_back({employee_id, name, password});
    Msg("Congrats! You signed up successfully as our Employee!","success");

    ostringstream oss;
    oss << "YOUR ID : " << Employee :: employee_id;
    Msg(oss.str(), "info");

    go_back();
    return;
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
            "Update Profile",
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
            updateEmployee(id);
            break;
        case 1:
            AccountHolder::accntHolderInfo();
            break;
        case 2:
            search_account();
            break;
        case 3:
            remove_account();
            break;
        case 4:
            transaction_history();
            break;
        case 5:
        {
            Complaint::update_first_complain_status();
            break;
        }
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
        // Mark complaints in Complaints_vector_n
        for (auto &entry : Complaints_vector_n)
        {
            for (auto &comp : entry.second)
            {
                if (comp.nid == it->nid)
                    comp.nid = "0";
            }
        }

        // Mark complaints in Complaints_vector_t
        for (auto &comp : Complaints_vector_t)
        {
            if (comp.nid == it->nid)
                comp.nid = "0";
        }

        // Finally mark the account itself as ghost
        it->nid = "0";
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
    if (it != Account_vector.end() && it->nid == sid && it->nid !="0")
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
    //Handling ghost account
    if(nid=="0")
    {
        Msg("Account No Longer Available", "warning");
        go_back();
        return;
    }

    int index = -1;
    for (int i = 0; i < (int)Account_vector.size(); i++)
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

void Employee::deposit_request(int index, double amount, string dep)
{
    if (amount <= 0)
    {
        Msg("Invalid deposit amount","error");
        return;
    }

    Account_vector[index].deposit += amount;
    Account_vector[index].history.push_back(amount); // Positive for deposit

    ostringstream oss;
    oss << fixed << std::setprecision(2);
    oss << "Successfully deposited " << dep << ". New balance: " << Account_vector[index].deposit << " BDT";

    Msg(oss.str(), "success");
}

void Employee:: withdraw_request(int index, double amount, string with)
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
    oss << fixed << setprecision(2);
    oss << "Successfully withdrawn " << with << ". New balance: " << Account_vector[index].deposit << " BDT.";
    Msg(oss.str(), "success");
}

void Employee::updateEmployee(int id)
{
    auto it = lower_bound(Employee_vector.begin(), Employee_vector.end(), id,
                          [](const EmployeeData &emp, int value)
    {
        return emp.id < value;
    });
    int index = it - Employee_vector.begin();

    while (true)
    {
        vector<string> options = {"Update Name", "Change Password", "Exit"};
        int op = menu(options, "Update Information");

        switch (op)
        {
        case 0:
        {
            Msg("Type Name", "prompt");
            string new_name;
            getline(cin >> ws, new_name);
            if (!check_name_validity(new_name))
            {
                Msg("Invalid name!", "error");
                go_back();
                break;
            }
            Employee_vector[index].name = new_name;
            Msg("Name updated successfully", "success");
            go_back();
            break;
        }
        case 1:
        {
            Msg("Enter current password", "prompt");
            string old_pass;
            read_password(old_pass);
            Encryption::encrypt(old_pass);

            if (old_pass != Employee_vector[index].password)
            {
                Msg("Incorrect current password!", "error");
                go_back();
                break;
            }

            Msg("Enter new password", "prompt");
            string new_pass;
            read_password(new_pass);

            Msg("Confirm new password", "prompt");
            string confirm_pass;
            read_password(confirm_pass);

            if (new_pass != confirm_pass)
            {
                Msg("Passwords do not match!", "error");
                go_back();
                break;
            }

            if (!check_pass_validity(new_pass))
            {
                Msg("Password does not meet requirements!", "error");
                go_back();
                break;
            }
            Encryption::encrypt(new_pass);
            Employee_vector[index].password = new_pass;
            Msg("Password updated successfully", "success");
            go_back();
            break;
        }
        case 2:
            return;
        }
    }
}

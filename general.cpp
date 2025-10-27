#include "tools.hpp"
#include "admin.hpp"
#include "employee.hpp"
#include "general.hpp"
#include "sign.hpp"
#include "converter.hpp"
#include "complaint.hpp"

/*--------------------------------------
       Account Holder Section
---------------------------------------*/

extern vector<AccountData> Account_vector;  // actual storage

/* Account holder signup */
//Constructor for sign-up
AccountHolder::AccountHolder(double deposit)   // don't add default values twice
{
    this->deposit = deposit;
    collect_info();
}

void AccountHolder::collect_info()
{
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
                return;
            }
            else Msg("Invalid name. Try again.", "error");
        }
    }

    for (int i = 1; i <= ENTRY_LIMIT; i++)
    {
        Msg("Password","prompt");
        read_password(pass);
        if (check_pass_validity(pass)) break;
        else
        {
            if (i == ENTRY_LIMIT)
            {
                Msg("Try again later", "error");
                return;
            }
            else Msg("Invalid name. Try again.", "error");
        }
    }

    for (int i = 1; i <= ENTRY_LIMIT; i++)
    {
        Msg("Retype Password","prompt");
        read_password(conf_pass);
        if (pass != conf_pass)
        {
            if (i == ENTRY_LIMIT)
            {
                Msg("Try again later", "error");
                return;
            }
            else Msg("Passwords don't match! Type again.", "error");
        }
        else
        {
            Encryption::encrypt(pass);
            break;
        }
    }


    for (int i = 1; i <= ENTRY_LIMIT; i++)
    {

        Msg("NID Number","prompt");
        cin>>nid;
        if(check_nid_validity(nid)) break;
        else
        {
            if (i == ENTRY_LIMIT)
            {
                Msg("Try again later", "error");
                return;
            }
            else Msg("NID is not valid.", "error");
        }
    }

    Account_vector.push_back({name, nid, pass, deposit});
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
            "Update Profile",
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
            updateCustomer(index);
            break;

        }
        case 1:
        {
            ostringstream oss;
            oss<<fixed <<setprecision(2)<< Account_vector[index].deposit;
            Msg("Your Current Balance: " + oss.str() + " BDT.", "info");
            go_back();
            break;
        }
        case 2:
        {
            double amount;
            string Amount;
            Msg("Enter amount to deposit", "prompt");
            cin >> Amount;

            stringstream ss(Amount);
            if (!(ss >> amount) || !(ss.eof()))
            {
                Msg("Invalid Input", "error");
                go_back();
                break;
            }


            double iamount = amount;

            int choice = menu(Converter::types, "Choose deposited currency type : ");
            Converter::convert_to_bdt(amount, Converter :: types [choice]);

            ostringstream oss;
            oss << fixed << setprecision(2) << iamount << " " << Converter :: types[choice];

            emp.deposit_request(index, amount, oss.str());

            go_back();
            break;
        }

        case 3:
        {
            double amount;
            string Amount;
            Msg("Enter amount to withdraw", "prompt");
            cin >> Amount;

            stringstream ss(Amount);
            if (!(ss >> amount) || !(ss.eof()))     // fails if not a pure number
            {
                Msg("Invalid Input", "error");
                go_back();
                break;
            }

            double iamount = amount;

            int choice = menu(Converter::types, "Choose withdrawn currency type : ");
            Converter::convert_to_bdt(amount, Converter :: types [choice]);

            ostringstream oss;
            oss << fixed << setprecision(2) << iamount << " " << Converter :: types[choice];

            emp.withdraw_request(index, amount, oss.str());
            go_back();
            break;
        }

        case 4:
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

        case 5:
            complainBox(nid);
            break;

        case 6:
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


/*Updating Account Holder Info*/
void AccountHolder::updateCustomer(int index)
{
    while (true) {
        vector<string> options = {"Update Name", "Change Password", "Exit"};
        int op = menu(options, "Update Information");

        switch(op)
        {
        case 0: {
            Msg("Type Name", "prompt");
            string new_name;
            getline(cin >> ws, new_name);

            if (!check_name_validity(new_name)) {
                Msg("Invalid name!", "error");
                go_back();
                break;
            }

            Account_vector[index].name = new_name;
            Msg("Name updated successfully", "success");
            go_back();
            break;

        }case 1: {
            Msg("Enter current password", "prompt");
            string old_pass;
            read_password(old_pass);
            Encryption::encrypt(old_pass);

            if (old_pass != Account_vector[index].password) {
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

            if (new_pass != confirm_pass) {
                Msg("Passwords do not match!", "error");
                go_back();
                break;
            }

            if (!check_pass_validity(new_pass)) {
                Msg("Password does not meet requirements!", "error");
                go_back();
                break;
            }

            Encryption::encrypt(new_pass);
            Account_vector[index].password = new_pass;
            Msg("Password updated successfully", "success");
            go_back();
            break;
        }

        case 2:
            return;
        }
    }
}


void AccountHolder::complainBox(string nid) {
    while (true) {
        vector<string> options = {"Submit Complaint", "Show Complaint", "Exit"};
        int op = menu(options, "Complain Box");

        switch(op) {
            case 0:
                Complaint::submit_complain(nid);
                break;
            case 1:
                Complaint::show_complains_by_nid(nid);
                break;
            case 2:
                return;  // leave the complain box

        }
    }
}

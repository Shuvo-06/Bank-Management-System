#include "complaint.hpp"
#include "tools.hpp"
using namespace std;

Complaint Complaints_array[100000]; // according to time

int Complaint::index_of_pending, Complaint::total_complaint;


void Complaint::operator += (Complaint &c) {
    Complaints_array[total_complaint] = c;

    Msg("Complaint submitted successfully!", "success");
    total_complaint++;
}

void Complaint::submit_complain(string nid) {
    clear_screen();
    Msg("Enter your complaint", "prompt");

    Complaint c;
    c.nid = nid;
    c.resolved = false;
    cin.ignore();
    getline(cin, c.complain);

    Complaint temp;
    temp += c;

    go_back();
    return;
}

void Complaint::show_complains_by_nid(string nid) { // Account Holder functionality
    clear_screen();
    header("Your Complains", MAGENTA, 50);

    int cnt = 0;
    for (int i = 0; i < total_complaint; i++) cnt += (Complaints_array[i].nid == nid);
    if (cnt == 0) {
        Msg("The complaint box is empty!!!", "success");
        go_back();
        return;
    }

    int idx = 1;
    for (int i = 0; i < total_complaint; i++) {
        if (Complaints_array[i].nid != nid) continue;

        string status = Complaints_array[i].resolved ? (string(GREEN) + "Resolved" + RESET) : (string(YELLOW) + "Pending" + RESET);

        ostringstream title;
        title << idx++ << ". Complaint";
        subHeader(title.str(), YELLOW, 50);


        cout << BOLD << CYAN   << "Status  : " << RESET << status << "\n";
        cout << BOLD << CYAN   << "Details : " << RESET << Complaints_array[i].complain << "\n";
    }
    go_back();
}

void Complaint::show_all_complains() // Admin functionality
{
    clear_screen();
    header("All Complains", GREEN, 50);

    if (total_complaint == 0) {
        Msg("The complaint box is empty!!!", "warning");
        go_back();
        return;
    }

    for (int i = 0; i < total_complaint; i++) {
        string status = Complaints_array[i].resolved ? (string(GREEN) + "Resolved" + RESET) : (string(YELLOW) + "Pending" + RESET);

        ostringstream title;
        title << i + 1 << ". Complaint";
        subHeader(title.str(), YELLOW, 50);
        cout <<BOLD<< CYAN   << "NID     : " << RESET << Complaints_array[i].nid << "\n";
        cout <<BOLD<< CYAN   << "Status  : " << RESET << status << "\n";
        cout <<BOLD<< CYAN   << "Details : " << RESET << Complaints_array[i].complain << "\n";
    }
    go_back();
    return;
}

// change status
void Complaint::update_first_complain_status() {
    clear_screen();
    index_of_pending = -1;

    for (int i = 0; i < total_complaint; i++) {
        if (!Complaints_array[i].resolved) {
            index_of_pending = i;
            break;
        }
    }

    if (index_of_pending == -1) {
        Msg("No pending complaints found!", "success");
        go_back();
        return;
    }

    int idx = 1;
    for (int i = index_of_pending; i < total_complaint; i++) {
        if (Complaints_array[i].resolved)
            continue;

        cout << "\n-------------------------------------------\n";
        cout << YELLOW << idx << ". Complaint\n" << RESET;
        cout << BOLD << CYAN << "NID     : " << RESET << Complaints_array[i].nid << "\n";
        cout << BOLD << CYAN << "Status  : " << YELLOW << "Pending" << RESET << "\n";
        cout << BOLD << CYAN << "Details : " << RESET << Complaints_array[i].complain << "\n";
        idx++;
    }

    Complaints_array[index_of_pending].resolved = true;
    Msg("The first complaint has been successfully resolved!", "success");
    go_back();
    return;
}

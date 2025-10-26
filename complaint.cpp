#include "complaint.hpp"
#include "tools.hpp"

using namespace std;
vector <Complaints> Complaints_vector_t; // according to time
map <string, vector <Complaints>> Complaints_vector_n; // according to NID
int Complaint::index_of_pending, Complaint::total_complaint;

void Complaint::submit_complain(string nid) {
    clear_screen();
    Msg("Enter your complaint", "prompt");

    Complaints c;
    c.nid = nid;
    c.resolved = false;
    cin.ignore(); // maybe;
    getline(cin, c.complain);

    Complaints_vector_t.push_back(c);
    Complaints_vector_n[nid].push_back(c);

    Msg("Complaint submitted successfully!", "success");
    total_complaint++;
    go_back();
    return;
}

void Complaint::show_complains_by_nid(string nid) { // Account Holder functionality
    clear_screen();
    header("Your Complains", MAGENTA, 50);

    if (Complaints_vector_n[nid].empty())
    {
        Msg("The complaint box is empty!!!", "success");
        go_back();
        return;
    }

    int idx = 1;
    for (auto &x : Complaints_vector_n[nid])
    {
        string status = x.resolved
                        ? (string(GREEN) + "Resolved" + RESET)
                        : (string(YELLOW) + "Pending" + RESET);


        ostringstream title;
        title << idx << ". Complaint";
        subHeader(title.str(), YELLOW, 50);


        cout <<BOLD<< CYAN   << "Status  : " << RESET << status << "\n";
        cout <<BOLD<< CYAN   << "Details : " << RESET << x.complain << "\n";

        idx++;
    }
    go_back();
}

void Complaint::show_all_complains() // Admin functionality
{
    clear_screen();
    header("All Complains", GREEN, 50);

    if (Complaints_vector_t.empty())
    {
        Msg("The complaint box is empty!!!", "warning");
        go_back();
        return;
    }

    int idx = 1;
    for (auto x : Complaints_vector_t)
    {
        string status = x.resolved
                        ? (string(GREEN) + "Resolved" + RESET)
                        : (string(YELLOW) + "Pending" + RESET);


        ostringstream title;
        title << idx << ". Complaint";
        subHeader(title.str(), YELLOW, 50);
        cout <<BOLD<< CYAN   << "NID     : " << RESET << x.nid << "\n";
        cout <<BOLD<< CYAN   << "Status  : " << RESET << status << "\n";
        cout <<BOLD<< CYAN   << "Details : " << RESET << x.complain << "\n";
        idx++;
    }
    go_back();
    return;
}

// change status
void Complaint::update_first_complain_status() {
    clear_screen();
    index_of_pending=-1;
    for (int i = 0; i < (int)Complaints_vector_t.size(); i++) {
    if (!Complaints_vector_t[i].resolved) {
        index_of_pending = i;
        break;
    }
    }
    if (index_of_pending ==-1)
    {
        Msg("The complaint box is empty", "success");
        go_back();
        return;
    }

    for (int i = index_of_pending, idx = 1; i < (int)Complaints_vector_t.size(); i++, idx++) {
        auto &c = Complaints_vector_t[i];
        ostringstream title;
        title << idx << ". Complaint";
        subHeader(title.str(), YELLOW, 60);

        cout << BOLD << CYAN << "NID     : " << RESET << c.nid << "\n";
        cout << BOLD << CYAN << "Status  : " << YELLOW << "Pending"<<RESET << "\n";
        cout << BOLD << CYAN << "Details : " << RESET << c.complain << "\n\n";

        idx++;
    }

    Msg("The first complaint has been successfully resolved", "success");

    Complaints f = Complaints_vector_t[index_of_pending];
    Complaints_vector_t[index_of_pending].resolved = true;
    for (auto &x : Complaints_vector_n[f.nid])
    {
        if (x.resolved == false)
        {
            x.resolved = true;
            break;
        }
    }
    go_back();
}

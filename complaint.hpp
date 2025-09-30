#ifndef COMPLAINT_HPP
#define COMPLAINT_HPP

#include "tools.hpp"
using namespace std;

struct Complaints {
    string nid;
    bool resolved;  // false = pending, true = resolved
    string complain;
};

extern vector <Complaints> Complaints_vector_t; // according to time
extern map <string, vector <Complaints>> Complaints_vector_n; // according to NID

class Complaint{
    static int index_of_pending, total_complaint;
public:
    static void submit_complain(string NID); // used to submit a new complaint, account holders will use this function

    static void show_complains_by_nid(string NID);

    static void show_all_complains();

    static void update_first_complain_status();

};

#endif // COMPLAINT_HPP


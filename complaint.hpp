#ifndef COMPLAINT_HPP
#define COMPLAINT_HPP

#include "tools.hpp"
using namespace std;

struct Complaints {
    string nid;
    bool resolved;  // false = pending, true = resolved
    string complain;
};

extern Complaints Complaints_array[100000];

class Complaint{
public:
    static int index_of_pending, total_complaint;

    static void submit_complain(string NID); // used to submit a new complaint, account holders will use this function

    static void show_complains_by_nid(string NID);

    static void show_all_complains();

    static void update_first_complain_status();

};

#endif //COMPLAINT_HPP

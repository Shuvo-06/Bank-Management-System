#ifndef COMPLAINT_HPP
#define COMPLAINT_HPP

#include "tools.hpp"
using namespace std;

class Complaint{
public:
    string nid;
    bool resolved;
    string complain;

    static int total_complaint, index_of_pending;

    static void submit_complain(string NID);

    static void show_complains_by_nid(string NID);

    static void show_all_complains();

    static void update_first_complain_status();

    void operator += (Complaint &c);
};

extern Complaint Complaints_array[100000];


#endif //COMPLAINT_HPP

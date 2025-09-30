#ifndef SIGN_HPP
#define SIGN_HPP

#include <bits/stdc++.h>
using namespace std;

class SignUp {
    string name, password, nid;
public:
    SignUp();
};

class SignIn {
public:
    SignIn();
    void signin_employee();
    void signin_general();
};


#endif // SIGN_HPP

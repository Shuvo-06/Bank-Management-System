#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <bits/stdc++.h>
using namespace std;

class Converter {
    static vector<string> types;
    static vector<double> rates;

public:
    static void convert_to_bdt(double &amount, string type);
    static void convert_from_bdt(double &amount, string type);

    friend void load_rates();
    friend void save_rates();
    friend class AccountHolder;
    friend class Admin;
};

#endif // CONVERTER_HPP

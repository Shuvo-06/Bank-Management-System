#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <bits/stdc++.h>
using namespace std;

class Converter {
public:
    double amount,rate;
    static vector<string> types;
    static vector<double> rates;

    Converter(double amt = 0, double r = 1.0);

    Converter operator*(const Converter &usd);
    Converter operator/(const Converter &usd);

    static void convert_to_bdt(double &amount, string type);
    static void convert_from_bdt(double &amount, string type);

    friend void load_rates();
    friend void save_rates();
    friend class AccountHolder;
    friend class Admin;
};

#endif // CONVERTER_HPP

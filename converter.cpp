#include "converter.hpp"
#include "tools.hpp"
#include "sign.hpp"
#include "admin.hpp"
#include "employee.hpp"
#include "general.hpp"

vector<string> Converter::types;
vector<double> Converter::rates;

Converter::Converter(double amt, double r) : amount(amt), rate(r) {}

Converter Converter::operator*(const Converter &usd) {
        Converter temp;
        temp.amount = amount*usd.rate;
        return temp;
}

Converter Converter::operator/(const Converter &usd) {
        Converter temp;
        temp.amount = amount / usd.rate;
        return temp;
}

void Converter::convert_to_bdt(double &amount, string type) {
    for (size_t i = 0; i < types.size(); i++) {
        if (types[i] == type) {
            Converter base(amount, 0);      
            Converter currency(0, rates[i]);    

            Converter result = base * currency;
            amount = result.amount;
            return;
        }
    }
}

void Converter::convert_from_bdt(double &amount, string type) {
    for (size_t i = 0; i < types.size(); i++) {
        if (types[i] == type) {
            Converter base(amount, 0);         
            Converter currency(0, rates[i]); 

            Converter result = base / currency;
            amount = result.amount;
            return;
        }
    }
}



//void Converter::convert_to_bdt(double &amount, string type) {
//    for (int i = 0; i < (int)types.size(); i++) {
//        if (types[i] == type) {
//            amount *= rates[i];
//            return;
//        }
//    }
//}
//
//void Converter::convert_from_bdt(double &amount, string type) {
//    for (int i = 0; i < (int)types.size(); i++) {
//        if (types[i] == type) {
//            amount /= rates[i];
//            return;
//        }
//    }
//}

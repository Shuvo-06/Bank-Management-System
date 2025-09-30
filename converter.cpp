#include "converter.hpp"
#include "tools.hpp"
#include "sign.hpp"
#include "admin.hpp"
#include "employee.hpp"
#include "general.hpp"

vector<string> Converter::types;
vector<double> Converter::rates;

void Converter::convert_to_bdt(double &amount, string type) {
    for (int i = 0; i < (int)types.size(); i++) {
        if (types[i] == type) {
            amount *= rates[i];
            return;
        }
    }
}

void Converter::convert_from_bdt(double &amount, string type) {
    for (int i = 0; i < (int)types.size(); i++) {
        if (types[i] == type) {
            amount /= rates[i];
            return;
        }
    }
}

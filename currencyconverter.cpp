#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <iomanip>


#define ll long long
#define ld long double
#define pb push_back
#define yes cout << "YES\n"
#define no cout << "NO\n"
#define testcase \
long long t; \
cin >> t;    \
while (t--)

using namespace std;

class Converter1 {
    int amount;
    double total;

public:
    void input(string name) {
        //takes input of the currency
        cout << "Amount in " << name << ": ";
        cin >> amount;
    }

    double calculator1(double n) {
        // calculate taka to another currency
        total = amount / n;
        return total;
    }

    double calculator2(double n) {
        // calculate another currency to taka
        total = amount * n;
        return total;
    }

    void output1(string name, double r) {
        // output the result of taka to another currency
        double result = calculator1(r);
        cout << "Amount in " << name << ": " << fixed << setprecision(2) << result << endl;
    }

    void output2(string name, double r) {
        // output the result of another currency to taka
        double result = calculator2(r);
        cout << "Amount in " << name << ": " << fixed << setprecision(2) << result << endl;
    }
};

int main() {
    while (true){
        Converter1 c1;
        int option; // option no below
        cout << "1.Taka <--> Dollar" << endl;
        cout << "2.Taka <--> Euro" << endl;
        cout << "3.Taka <--> Suadi Riyal" << endl;
        cout << "4.Taka <--> Kuwaiti Dinar" << endl;
        cout << "5.Taka <--> Pound" << endl;
        cout << "6.Taka <--> Indian Rupee" << endl;
        cout << "7.Taka <--> Canadian Dollar" << endl;
        cout << "8.Taka <--> Chinese Yuan" << endl;
        cout << "9.Taka <--> Russian Ruble" << endl;
        cout << "10.Taka <--> UAE Dirham" << endl;
        cout << "0.Exit" << endl;
        cout << "Enter option: ";
        cin >> option; //takes option input to go to the switch case
        cout << endl;
        switch (option) {
            case 1: {
                // taka <--> dollar tranfer function calling from the class
                string name1 = "Taka", name2 = "Dollar";
                double rate = 121.41;
                cout << "1." << name1 << " to " << name2 << endl;
                cout << "2." << name2 << " to " << name1 << endl;
                cout << "0.Back" << endl;
                cout << "Enter option: ";
                int opt;
                cin >> opt;
                cout << endl;
                switch (opt) {
                    case 1: {
                        // taka to dollar
                        c1.input(name1);
                        c1.output1(name2, rate);
                        break;
                    }
                    case 2: {
                        // dollar to taka
                        c1.input(name2);
                        c1.output2(name1, rate);
                        break;
                    }
                    case 0: {
                        break;
                    }
                }
                break;
            }
                // same as before
                // first subcase is always taka to another currency
                // second subcase always antoher currency to taka
            case 2: {
                string name1 = "Taka", name2 = "Euro";
                double rate = 142.03;
                cout << "1." << name1 << " to " << name2 << endl;
                cout << "2." << name2 << " to " << name1 << endl;
                cout << "0.Back" << endl;
                cout << "Enter option: ";
                int opt;
                cin >> opt;
                cout << endl;
                switch (opt) {
                    case 1: {
                        c1.input(name1);
                        c1.output1(name2, rate);
                        break;
                    }
                    case 2: {
                        c1.input(name2);
                        c1.output2(name1, rate);
                        break;
                    }
                    case 0: {
                        break;
                    }
                }
                break;
            }
            case 3: {
                string name1 = "Taka", name2 = "Suadi Riyal";
                double rate = 32.37;
                cout << "1." << name1 << " to " << name2 << endl;
                cout << "2." << name2 << " to " << name1 << endl;
                cout << "0.Back" << endl;
                cout << "Enter option: ";
                int opt;
                cin >> opt;
                cout << endl;
                switch (opt) {
                    case 1: {
                        c1.input(name1);
                        c1.output1(name2, rate);
                        break;
                    }
                    case 2: {
                        c1.input(name2);
                        c1.output2(name1, rate);
                        break;
                    }
                    case 0: {
                        break;
                    }
                }
                break;
            }
            case 4: {
                string name1 = "Taka", name2 = "Kuwaiti Dinar";
                double rate = 397.24;
                cout << "1." << name1 << " to " << name2 << endl;
                cout << "2." << name2 << " to " << name1 << endl;
                cout << "0.Back" << endl;
                cout << "Enter option: ";
                int opt;
                cin >> opt;
                cout << endl;
                switch (opt) {
                    case 1: {
                        c1.input(name1);
                        c1.output1(name2, rate);
                        break;
                    }
                    case 2: {
                        c1.input(name2);
                        c1.output2(name1, rate);
                        break;
                    }
                    case 0: {
                        break;
                    }
                }
                break;
            }
            case 5: {
                string name1 = "Taka", name2 = "Pound";
                double rate = 162.75;
                cout << "1." << name1 << " to " << name2 << endl;
                cout << "2." << name2 << " to " << name1 << endl;
                cout << "0.Back" << endl;
                cout << "Enter option: ";
                int opt;
                cin >> opt;
                cout << endl;
                switch (opt) {
                    case 1: {
                        c1.input(name1);
                        c1.output1(name2, rate);
                        break;
                    }
                    case 2: {
                        c1.input(name2);
                        c1.output2(name1, rate);
                        break;
                    }
                    case 0: {
                        break;
                    }
                }
                break;
            }
            case 6: {
                string name1 = "Taka", name2 = "Indian Rupee";
                double rate = 1.37;
                cout << "1." << name1 << " to " << name2 << endl;
                cout << "2." << name2 << " to " << name1 << endl;
                cout << "0.Back" << endl;
                cout << "Enter option: ";
                int opt;
                cin >> opt;
                cout << endl;
                switch (opt) {
                    case 1: {
                        c1.input(name1);
                        c1.output1(name2, rate);
                        break;
                    }
                    case 2: {
                        c1.input(name2);
                        c1.output2(name1, rate);
                        break;
                    }
                    case 0: {
                        break;
                    }
                }
                break;
            }
            case 7: {
                string name1 = "Taka", name2 = "Canadian Dollar";
                double rate = 87.06;
                cout << "1." << name1 << " to " << name2 << endl;
                cout << "2." << name2 << " to " << name1 << endl;
                cout << "0.Back" << endl;
                cout << "Enter option: ";
                int opt;
                cin >> opt;
                cout << endl;
                switch (opt) {
                    case 1: {
                        c1.input(name1);
                        c1.output1(name2, rate);
                        break;
                    }
                    case 2: {
                        c1.input(name2);
                        c1.output2(name1, rate);
                        break;
                    }
                    case 0: {
                        break;
                    }
                }
                break;
            }
            case 8: {
                string name1 = "Taka", name2 = "Chinese Yuan";
                double rate = 17.02;
                cout << "1." << name1 << " to " << name2 << endl;
                cout << "2." << name2 << " to " << name1 << endl;
                cout << "0.Back" << endl;
                cout << "Enter option: ";
                int opt;
                cin >> opt;
                cout << endl;
                switch (opt) {
                    case 1: {
                        c1.input(name1);
                        c1.output1(name2, rate);
                        break;
                    }
                    case 2: {
                        c1.input(name2);
                        c1.output2(name1, rate);
                        break;
                    }
                    case 0: {
                        break;
                    }
                }
                break;
            }
            case 9: {
                string name1 = "Taka", name2 = "Russian Ruble";
                double rate = 1.45;
                cout << "1." << name1 << " to " << name2 << endl;
                cout << "2." << name2 << " to " << name1 << endl;
                cout << "0.Back" << endl;
                cout << "Enter option: ";
                int opt;
                cin >> opt;
                cout << endl;
                switch (opt) {
                    case 1: {
                        c1.input(name1);
                        c1.output1(name2, rate);
                        break;
                    }
                    case 2: {
                        c1.input(name2);
                        c1.output2(name1, rate);
                        break;
                    }
                    case 0: {
                        break;
                    }
                }
                break;
            }
            case 10: {
                string name1 = "Taka", name2 = "UAE Dirham";
                double rate = 33.06;
                cout << "1." << name1 << " to " << name2 << endl;
                cout << "2." << name2 << " to " << name1 << endl;
                cout << "0.Back" << endl;
                cout << "Enter option: ";
                int opt;
                cin >> opt;
                cout << endl;
                switch (opt) {
                    case 1: {
                        c1.input(name1);
                        c1.output1(name2, rate);
                        break;
                    }
                    case 2: {
                        c1.input(name2);
                        c1.output2(name1, rate);
                        break;
                    }
                    case 0: {
                        break;
                    }
                }
                break;
            }
            case 0: {
                cout << "Proccess Terminated";
                return 0;
            }
            default: {
                cout << "Invalid option.Please try again." << endl;
                break;
            }
        }
        cout << endl;
        cout << endl;
    }
}

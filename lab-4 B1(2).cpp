#include <bits/stdc++.h>
using namespace std;

bool is_leap(int y) {
    return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
}

int days_in_month(int m, int y) {
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) return 31;
    if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
    return is_leap(y) ? 29 : 28;
}

class Date {
    int day, mon, year;

    // Convert current date to "days since 01/01/0001"
    int to_days() const {
        int days = 0;
        // add full years
        for (int i = 1; i < year; i++) {
            days += is_leap(i) ? 366 : 365;
        }
        // add months of current year
        for (int i = 1; i < mon; i++) {
            days += days_in_month(i, year);
        }
        // add days
        days += day;
        return days;
    }

    // Convert total days back to Date
    static Date from_days(int total) {
        int y = 1;
        while (true) {
            int days_in_year = is_leap(y) ? 366 : 365;
            if (total > days_in_year) {
                total -= days_in_year;
                y++;
            } else break;
        }
        int m = 1;
        while (true) {
            int dim = days_in_month(m, y);
            if (total > dim) {
                total -= dim;
                m++;
            } else break;
        }
        return Date(total, m, y);
    }

public:
    Date(int d=1, int m=1, int y=1) {
        if (d < 1 || d > 31 || m < 1 || m > 12 || y < 1) {
            cout << "Invalid Date"; exit(0);
        }
        if (m == 4 || m == 6 || m == 9 || m == 11) {
            if (d > 30) { cout << "Invalid Date"; exit(0); }
        }
        if (m == 2) {
            if ((is_leap(y) && d > 29) || (!is_leap(y) && d > 28)) {
                cout << "Invalid Date"; exit(0);
            }
        }
        day = d; mon = m; year = y;
    }

    Date& operator=(const Date& obj) {
        if (this != &obj) {
            day = obj.day;
            mon = obj.mon;
            year = obj.year;
        }
        return *this;
    }

    friend istream& operator>>(istream &input, Date &obj) {
        input >> obj.day >> obj.mon >> obj.year;
        return input;
    }

    friend ostream& operator<<(ostream &output, const Date &obj) {
        output << setw(2) << setfill('0') << obj.day << "/"
               << setw(2) << setfill('0') << obj.mon << "/"
               << setw(4) << setfill('0') << obj.year;
        return output;
    }

    // Add days (represented by another Date object’s "day" field only)
    friend Date operator+(const Date &d1, const Date &d2) {
        int total_days = d1.to_days() + d2.to_days();
        return from_days(total_days);
    }

    // Difference between two dates → as a Date (days difference, not real date)
    friend Date operator-(const Date &d1, const Date &d2) {
        int diff = abs(d1.to_days() - d2.to_days());
        return from_days(diff);
    }

    friend bool operator==(const Date &d1, const Date &d2) {
        return d1.day == d2.day && d1.mon == d2.mon && d1.year == d2.year;
    }
};

int main() {
    Date d1, d2;
    cin>>d1>>d2;
    cout << "Date1: " << d1 << endl;
    cout << "Date2: " << d2 << endl;

    cout << "Are they equal? " << (d1 == d2 ? "Yes" : "No") << endl;

    Date diff = d2 - d1;
    Date add = d1+d2;
    cout << add<<endl<< diff << endl;
}

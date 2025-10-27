#include "tools.hpp"
#include "admin.hpp"
#include "employee.hpp"
#include "general.hpp"
#include "sign.hpp"
#include "complaint.hpp"
#include <conio.h>
using namespace std;

#ifdef _WIN32
    BOOL WINAPI ConsoleHandler(DWORD signal) {
        if (signal == CTRL_CLOSE_EVENT) {
            Loading load;
            load.save_accounts();
            load.save_employees();
            load.save_histories();
            load.save_rates();
            load.save_complaints();
            Sleep(1000);
        }
        return TRUE;
    }
#endif

// -- clear_screen --
// write clear_screen() when u need to flush everything out of screen
void clear_screen() {
    system("cls");
}

// -- go_back --
// write go_back() when u need to return to the previous menu
void go_back(){
    cout << CYAN << "\nPress ANY KEY to go back\n" << RESET;
    _getch();
}

// -- read_password --
// use it to read password from user, just pass the password string to this function
void read_password(string &password) {
    password.clear();
    while (true) {
        char ch = _getch();
        if (ch == '\r' || ch == '\n') {
            cout << "\n";
            break;
        }
        else if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else if (password.size() < MAX_PASSWORD_SIZE - 1) {
            password.push_back(ch);
            cout << '*';
        }
    }
}

// -- Encryption --
// Write Encryption::encrypt (password) to encrypt it
void Encryption::encrypt(string &password) {
    const int k = KEY;
    for (auto &c : password) c ^= k;
}

// -- Menu --
// menu(vector <string> with option title, caption (optional)) to create a menu which returns the index (0-based) of the chosen option
void Menu(int choice, int scWidth, int scHeight,
          const vector<string> &menu, const string &caption) {
    int no_of_options = (int)menu.size();
    int menuWidth = 20, menuHeight = no_of_options;
    int startRow = (scHeight / 2) - (menuHeight / 2);
    int startCol = (scWidth / 2) - (menuWidth / 2);

    int captionLines = caption.empty() ? 0 : 2;
    for (int i = 0; i < max(0, startRow - captionLines); i++) cout << "\n";

    if (!caption.empty()) {
        int capStart = max(0, (scWidth / 2) - (int)(caption.size() / 2));
        for (int j = 0; j < capStart; j++) cout << " ";
        cout << caption << "\n\n";
    }

    for (int i = 0; i < no_of_options; i++) {
        for (int j = 0; j < startCol; j++) cout << " ";

        string temp;
        for (char c : menu[i]) temp += tolower(c);

        if (temp == "exit" || temp == "sign out" || temp == "go back") {
            if (i == choice) cout << ">> ";
            else cout << "   ";

            cout << RED << "Exit" << RESET;

            if (i == choice) cout << " <<";
            cout << "\n";
        }
        else {
            if (i == choice) cout << ">> ";
            else cout << "   ";

            cout << CYAN << menu[i] << RESET;

            if (i == choice) cout << " <<";
            cout << "\n";
        }
    }
}

int menu(const vector<string> &menu_options, const string &caption) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int scWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int scHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    int choice = 0;
    int key;

    while (true) {
        clear_screen();
        Menu(choice, scWidth, scHeight, menu_options, caption);

        key = _getch();
        if (key == 224) {
            switch (_getch()) {
                case 72: choice = (choice - 1 + (int)menu_options.size()) % (int)menu_options.size(); break; // Up
                case 80: choice = (choice + 1) % (int)menu_options.size(); break; // Down
            }
        }
        else if (key == 13) return choice; // Enter
    }
}

// -- Styled Message --
// call Msg("your message", "message nature")
// Type "error" to show error in inpu
//      "prompt" to show input propmt
//      "success" to say something has been done successfully
//      "warning" to show warning
//      "info" to show info in the placeholder "message nature".

void Msg(const string &msg, const string &msgNature) {
    if (msgNature == "prompt" || msgNature == "Prompt") cout << BOLD << CYAN << msg << ": " << RESET;
    else {
        string fullMsg;
        if (msgNature == "error" || msgNature == "Error") fullMsg = " XXX " + msg;
        else if (msgNature == "success" || msgNature == "Success") fullMsg = "     " + msg + "   ";
        else if (msgNature == "warning" || msgNature == "Warning") fullMsg = " !!! " + msg;
        else if (msgNature == "info" || msgNature == "Info") fullMsg = " >>> " + msg;
        else fullMsg = "     " + msg + "   ";

        int boxWidth = (int)(fullMsg.size() + 4);
        int totalPadding = boxWidth - fullMsg.size() - 2;
        int leftPadding = totalPadding / 2;
        int rightPadding = totalPadding - leftPadding;

        cout << string(boxWidth+2, '-') << "\n"<< "|"<< string(leftPadding, ' ');

        if (msgNature == "error" || msgNature == "Error") cout << RED << fullMsg << RESET;
        else if (msgNature == "success" || msgNature == "Success") cout << GREEN << fullMsg << RESET;
        else if (msgNature == "warning" || msgNature == "Warning") cout << YELLOW << fullMsg << RESET;
        else if (msgNature == "info" || msgNature == "Info") cout << MAGENTA << fullMsg << RESET;
        else cout << fullMsg;

        cout << string(rightPadding + 2, ' ') << "|\n"<< string(boxWidth + 2, '-') << "\n";
    }
}

// -- Styled Header --
// call header("Header", color, width)
void header(const string &msg, string color, int width)
{
    int totalLen = msg.size() + 6;
    if(totalLen > width) width = totalLen + 4;
    int side = (width - totalLen) / 2;
    cout << "\n" << color << string(side, '=') << BOLD << "== " <<RESET<< msg<<color<<BOLD << " ==" << RESET << color << string(width - totalLen - side, '=') << RESET << "\n\n";
}

// -- Styled Sub-header --
// call subHeader("Header", color, width)
void subHeader(const string &msg, string color, int width)
{
    cout<<endl;
    int side = (width - msg.size() - 4) / 2;
    if(side < 0) side = 0;
    cout << color << string(side, '-')
         << BOLD << " " << msg << " " << RESET
         << color << string(width - msg.size() - 4 - side, '-') << RESET << "\n\n";
}

// prints content of entire file
void read_entire_file(const string &s) {
    ifstream in(s);
    if (!in) {
        Msg("Something went wrong", "error");
        return;
    }
    cout << in.rdbuf(); // read buffer
}

/* Name validity */
bool check_name_validity(const string &n)
{
    if (n.empty()) return false;
    if (!isupper(n[0])) return false;

    for (char c : n)
    {
        if (c == ' ') continue;
        if (!isalpha(c)) return false;
    }
    return true;
}

/* Password validity */
// Requirements
// at least 1 digit
// at least 1 uppercase letter
// at least 1 special character
bool check_pass_validity(string p) {
    if (p.length() < 8) {
        Msg("Password must be at least 8 characters long.","error");
        return false;
    }

    bool sp_char = false, upper = false, number = false;
    for (int i = 0; i < (int)p.length(); i++) {
        if (isdigit(p[i])) number = true;
        if (isupper(p[i])) upper = true;
        if (!isdigit(p[i]) &&(p[i] < 65 || (p[i] > 90 && p[i] < 97) || p[i] > 122)) sp_char = true;
    }

    if (!number) {
        Msg("Password must contain at least 1 digit.","error");
        return false;
    }
    if (!upper) {
        Msg("Password must contain at least 1 uppercase letter.", "error");
        return false;
    }
    if (!sp_char){
        Msg("Password must contain at least 1 special character.","error");
        return false;
    }
    return true;
}

/*NID validity*/
// NID length exactly 10
// NID must not have any characters
bool check_nid_validity(string nid) {
    if(nid.length() != 10) {
        Msg("NID must be exactly 10 digits long", "error");
        return false;
    }

    for(char &c : nid) {
        if(!isdigit(c)) {
            Msg("NID must contain digits only.", "error");
            return false;
        }
    }

    for(auto &acc:Account_vector) {
        if (acc.nid == nid) {
            Msg("This NID is already registered.", "error");
            return false;
        }
    }

    return true;
}

#include "tools.hpp"
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

// -- Color codes
// cout << COLOR_NAME << ... << RESET
#define MAX_PASSWORD_SIZE 100
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define CYAN    "\033[36m"

// -- clear_screen --
// write clear_screen() when u need to flush everything out of screen
void clear_screen() {
    system("cls");
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
    const uint8_t k = KEY;
    for (auto &c : password) {
        c = static_cast<char>(static_cast<uint8_t>(c) ^ k);
    }
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

        if (menu[i] == "Exit" || menu[i] == "exit") {
            if (i == choice) cout << ">> ";
            else cout << "   ";

            cout << RED << "exit" << RESET;

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

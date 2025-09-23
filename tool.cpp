#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
using namespace std;
 
#define MAX_PASSWORD_SIZE 100
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define CYAN    "\033[36m"

void clear_screen() {
    system("cls");
}

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

void Menu(int choice, int scWidth, int scHeight, int no_of_options, const vector<string> &menu) {
    int menuWidth = 20, menuHeight = no_of_options;
    int startRow = (scHeight / 2) - (menuHeight / 2);
    int startCol = (scWidth / 2) - (menuWidth / 2);

    for (int i = 0; i < startRow; i++) cout << "\n";

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

int menu(const vector<string> &menu_options) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int scWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int scHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    int choice = 0;
    int key;

    while (true) {
        clear_screen();

        Menu(choice, scWidth, scHeight, menu_options.size(), menu_options);

        key = _getch();
        if (key == 224) {
            switch (_getch()) {
                case 72:
                    choice = (choice - 1 + menu_options.size()) % menu_options.size();
                    break;
                case 80:
                    choice = (choice + 1) % menu_options.size();
                    break;
            }
        }
        else if (key == 13) return choice;
    }
}

int main() {
    vector<string> options = {"Start Game", "Settings", "yugweyufb", "iuahwef", "yagbwefb", "Exit"};
    int choice = menu(options);

    cout << "You selected: " << options[choice] << "\n";

    cout << "Enter password: ";
    string password;
    read_password(password);
    cout << "Password captured (hidden): " << password.size() << " characters\n";

    return 0;
}

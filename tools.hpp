#ifndef TOOLS_H
#define TOOLS_H

#include <bits/stdc++.h>

// -- Color codes
// cout << COLOR_NAME << ... << RESET
#define MAX_PASSWORD_SIZE 100
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define YELLOW "\033[33m"
#define GREEN "\033[92m"
#define CYAN    "\033[36m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[95m"

#ifdef _WIN32
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
    #define WIN32_LEAN_AND_MEAN // cut down Windows headers
    #define byte win_byte_override // stop windows.h from defining 'byte'
    #include <windows.h>
    BOOL WINAPI ConsoleHandler(DWORD signal);
#endif

#define ENTRY_LIMIT 2

void clear_screen();
void go_back();
void read_password(std::string &);

class Encryption {
    static constexpr int KEY = 36;
public:
    static void encrypt(std::string &password);
};

void Menu(int choice, int scWidth, int scHeight, const std::vector<std::string> &menu, const std::string &caption);
int menu(const std::vector<std::string> &menu_options, const std::string &caption = "");
void Msg(const std::string &msg, const std::string &msgNature = "");
void header(const std::string &msg, std::string color = RESET, int width = 60);
void subHeader(const std::string &msg, std::string color = RESET, int width = 60);
void read_entire_file(const std::string &);

bool check_name_validity(const std::string &n);
bool check_pass_validity(std::string p);
bool check_nid_validity(std::string nid);

void save_accounts();
void save_employees();
void save_histories();
void save_rates();
void load_complaints();
void save_complaints();
#endif // TOOLS_H

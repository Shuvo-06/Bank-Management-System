#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <vector>

void clear_screen();
void go_back();
void read_password(std::string &);

class Encryption {
    static constexpr uint8_t KEY = 36;
public:
    static void encrypt(std::string &password);
};

void Menu(int choice, int scWidth, int scHeight, const std::vector<std::string> &menu, const std::string &caption);
int menu(const std::vector<std::string> &menu_options, const std::string &caption = "");

#endif // TOOLS_H

#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <vector>

#define MAX_PASSWORD_SIZE 100
#define RESET   "\033[0m"
#define BOLD    "\033[1m"

#define RED "\033[31m"
#define YELLOW "\033[33m"
#define GREEN "\033[92m"
#define CYAN    "\033[36m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[95m"


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
void Msg(const std::string &msg, const std::string &msgNature = "");
void header(const std::string &msg, std::string color = RESET, int width = 60);
void subHeader(const std::string &msg, std::string color = RESET, int width = 60);

#endif // TOOLS_H

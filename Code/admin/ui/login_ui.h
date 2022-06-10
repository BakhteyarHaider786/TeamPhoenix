#ifndef PHOENIXSYS_LOGIN_UI_H
#define PHOENIXSYS_LOGIN_UI_H

#include <string>
#include <ftxui/component/screen_interactive.hpp>

class LoginUI {
private:
    std::string username;
    std::string password;

public:
    void show(ftxui::ScreenInteractive &screen);
    std::string getUsername();
    std::string getPassword();
};


#endif //PHOENIXSYS_LOGIN_UI_H

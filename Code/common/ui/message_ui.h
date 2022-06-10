#ifndef PHOENIXSYS_MESSAGE_UI_H
#define PHOENIXSYS_MESSAGE_UI_H

#include <string>
#include <ftxui/component/screen_interactive.hpp>

using namespace ftxui;

class MessageUI {
public:
    static void show(ftxui::ScreenInteractive &screen, const std::string& message);
};


#endif //PHOENIXSYS_MESSAGE_UI_H

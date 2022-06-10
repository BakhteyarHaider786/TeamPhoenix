#include "login_ui.h"

#include <ftxui/component/component.hpp>

using namespace ftxui;
using std::string;

string LoginUI::getUsername() {
    return username;
}

string LoginUI::getPassword() {
    return password;
}

void LoginUI::show(ScreenInteractive &screen) {
    Component input_username, input_password, exit_button, login_button, component, view;

    InputOption password_option = { .password = true };

    input_username= Input(&username, "enter your username");
    input_password = Input(&password, "enter your password", password_option);
    exit_button = Button("  Exit  ", [] { exit(EXIT_SUCCESS); });
    login_button = Button("  Login  ", screen.ExitLoopClosure());

    component = Container::Vertical({
        input_username,
        input_password,
        login_button,
        exit_button
    });

    view = Renderer(component, [&] {
        return window(text(" Phoenix Systems ") | hcenter | bold, vbox({
            text(" Enter Login Credentials ") | center | color(Color::Red),
            separator(),
            filler(),
            hbox(text(" Username") | color(Color::Green), text(" : "), input_username->Render()),
            filler(),
            hbox(text(" Password") | color(Color::Green), text(" : "), input_password->Render()),
            filler(),
            hbox({ text(" "), login_button->Render() | center | color(Color::Blue),
                filler(),
                exit_button->Render() | center | color(Color::Red), text(" ") })
        }) | size(ftxui::WIDTH, ftxui::EQUAL, 40) | size(ftxui::HEIGHT, ftxui::EQUAL, 10) |
        border | center);
    });

    screen.Loop(view);
}

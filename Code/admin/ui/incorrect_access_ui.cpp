#include "incorrect_access_ui.h"

#include <ftxui/component/component.hpp>

using namespace ftxui;

void IncorrectAccessUI::show(ScreenInteractive &screen) {
    Component exit_button = Button("  Exit  ", [] { exit(EXIT_SUCCESS); });

    auto view = Renderer(exit_button, [&] {
        return  window(text(" Phoenix Systems ") | hcenter | bold, vbox({
                text(" ERROR ") | center | color(Color::Red),
                separator(),
                filler(),
                text(" Credentials are incorrect! ") | center,
                filler(),
                hbox({
                    filler(),
                    exit_button->Render() | center | color(Color::Red),
                    filler()
                })
            }) | size(ftxui::WIDTH, ftxui::EQUAL, 40) | size(ftxui::HEIGHT, ftxui::EQUAL, 10) |
        border | center);
    });

    screen.Loop(view);
}

#include "id_entry_ui.h"

#include <string>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

using namespace ftxui;

void IdEntryUI::show(ftxui::ScreenInteractive &screen, int &id) {
    id = -1;
    std::string id_input;
    Component enter_button = Button("  Enter  ", screen.ExitLoopClosure());
    Component back_button = Button("  Back  ", screen.ExitLoopClosure());
    Component input = Input(&id_input, "the id number");
    auto component = Container::Horizontal({ input, enter_button, back_button });

    auto view = Renderer(component, [&] {
        std::stringstream s(id_input);
        s >> id;
        return window(text(" Phoenix Systems ") | hcenter | bold, vbox({
                   text(" Enter ID ") | center | color(Color::Red),
                   separator(),
                   filler(),
                   hbox(text(" ID") | color(Color::Green), text(" : "), input->Render()),
                   filler(),
                   hbox({  text(" "), enter_button->Render(),
                           filler(),
                           back_button->Render() | center | color(Color::Red), text(" ") })
             }) | size(ftxui::WIDTH, ftxui::EQUAL, 40) | size(ftxui::HEIGHT, ftxui::EQUAL, 10) |
        border | center);
    });

    screen.Loop(view);
}

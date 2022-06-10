#include "message_ui.h"

#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

void MessageUI::show(ScreenInteractive &screen, const std::string& message) {
    Component back_button = Button("  Back  ", screen.ExitLoopClosure());
    auto component = Container::Horizontal({ back_button });

    auto view = Renderer(component, [&] {
        return window(text(" Phoenix Systems ") | hcenter | bold, vbox({
                   text("Message") | center | color(Color::Red),
                   separator(),
                   filler(),
                   hbox({ text("  "), text(message), text("  ") }) | center,
                   filler(),
                   hbox({ filler(), back_button->Render(), filler()})
            }) | size(ftxui::WIDTH, ftxui::EQUAL, 50) | size(ftxui::HEIGHT, ftxui::EQUAL, 10) |
        border | center);
    });

    screen.Loop(view);
}

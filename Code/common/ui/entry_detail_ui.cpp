#include "../../common/ui/message_ui.h"
#include "../misc/qr_code_gen.h"
#include "entry_detail_ui.h"

#include <string>
#include <ftxui/component/component.hpp>

using namespace ftxui;

using std::string;
using std::to_string;

void EntryDetailUI::show(ScreenInteractive &screen, entry_t entry) {
    Component back_button, qr_button, container, view;

    back_button = Button("  Back  ", screen.ExitLoopClosure());
    qr_button = Button("  QR  ", [&] {
        string path = QrCodeGen::saveToFile(entry);
        MessageUI::show(screen, "Saved to " + path);
    });

    container = Container::Horizontal({
        back_button, qr_button
    });

    view = Renderer(container, [&] {
        return window(text(" Phoenix Systems ") | hcenter | bold, vbox({
            text(" Details of ID - " + to_string(entry.id)) | center | color(Color::Red),
            separator(),
            hbox({ text(" NID   ") | color(Color::Green), text(" : "), text(entry.nid) }),
            separator(),
            hbox({ text(" AREA  ") | color(Color::Green), text(" : "), text(entry.area) }),
            separator(),
            hbox({ text(" CLASS ") | color(Color::Green), text(" : "), text(entry.category) }),
            separator(),
            hbox({ text(" NUMBER") | color(Color::Green), text(" : "), text(entry.number) }),
            separator(),
            hbox({ text(" "), back_button->Render(), filler(), qr_button->Render(), text(" ") })
        }) | size(ftxui::WIDTH, ftxui::EQUAL, 40) | size(ftxui::HEIGHT, ftxui::EQUAL, 13) |
        border | center);
    });

    screen.Loop(view);
}


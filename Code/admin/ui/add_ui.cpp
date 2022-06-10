#include "add_ui.h"

#include <ftxui/component/component.hpp>

using namespace ftxui;

using std::string;

entry_t AddUI::show(ftxui::ScreenInteractive &screen) {
    Component input_nid, input_area, input_category, input_number, add_button, back_button, container, view;
    string nid, area, category, number;
    entry_t entry;
    memset(&entry, 0, sizeof(entry_t));

    input_nid = Input(&nid, "enter nid");
    input_area = Input(&area, "enter area");
    input_category = Input(&category, "enter category");
    input_number = Input(&number, "enter number");

    add_button = Button("  Add  ", screen.ExitLoopClosure());
    back_button = Button("  Back  ", screen.ExitLoopClosure());

    container = Container::Vertical({
        input_nid,
        input_area,
        input_category,
        input_number,
        add_button,
        back_button
    });

    view = Renderer(container, [&] {
        return window(text(" Phoenix Systems ") | hcenter | bold, vbox({
            text("Details of Entry") | center | color(Color::Red),
            separator(),
            hbox({ text(" NID   ") | color(Color::Green), text(" : "), input_nid->Render() }),
            separator(),
            hbox({ text(" AREA  ") | color(Color::Green), text(" : "), input_area->Render() }),
            separator(),
            hbox({ text(" CLASS ") | color(Color::Green), text(" : "), input_category->Render() }),
            separator(),
            hbox({ text(" NUMBER") | color(Color::Green), text(" : "), input_number->Render() }),
            separator(),
            hbox({ text(" "), add_button->Render(), filler(), back_button->Render(), text(" ") })
        }) | size(ftxui::WIDTH, ftxui::EQUAL, 40) | size(ftxui::HEIGHT, ftxui::EQUAL, 13) |
        border | center);
    });

    screen.Loop(view);

    entry.id = -1;
    int nid_len = nid.length() < NID_LEN ? nid.length() : NID_LEN,
        area_len = area.length() < AREA_LEN ? area.length() : AREA_LEN,
        category_len = category.length() < CATEGORY_LEN ? category.length() : CATEGORY_LEN,
        number_len = number.length() < NUMBER_LEN ? number.length() : NUMBER_LEN;

    memcpy(entry.nid, nid.c_str(), nid_len);
    memcpy(entry.area, area.c_str(), area_len);
    memcpy(entry.category, category.c_str(), category_len);
    memcpy(entry.number, number.c_str(), number_len);

    return entry;
}

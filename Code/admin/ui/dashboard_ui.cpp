#include "add_ui.h"
#include "dashboard_ui.h"
#include "../../common/ui/entry_detail_ui.h"
#include "../../common/ui/message_ui.h"
#include "../../common/ui/id_entry_ui.h"

#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/component/component.hpp>

using namespace ftxui;

using std::vector;
using std::string;
using std::to_string;

#define STEP 5

void DashboardUI::show(ScreenInteractive &screen, Storage& storage, uint32_t start_index) {
    vector<vector<string>> table_entries;
    Component next_page, back_page, view_button, add_button, delete_button, exit_button, container, view;
    bool can_go_next, can_go_back;
    uint32_t end_index = start_index;
    auto entries = storage.all();

    next_page = Button(" > ", [&] {
        if (can_go_next) {
            screen.ExitLoopClosure();
            DashboardUI::show(screen, storage, start_index + STEP);
        }
    });
    back_page = Button(" < ", [&] {
        if (can_go_back) {
            screen.ExitLoopClosure();
            DashboardUI::show(screen, storage, start_index - STEP);
        }
    });
    view_button = Button("  View  ", [&] {
        int id;
        IdEntryUI::show(screen, id);
        if (id == -1) {
            return;
        }
        int index = storage.findById(id);
        if (index == -1) {
            MessageUI::show(screen, "Entry with id " + to_string(id) + " was not found!");
            return;
        }
        auto entry = storage.getByIndex(index);
        screen.ExitLoopClosure();
        EntryDetailUI::show(screen, entry);
        DashboardUI::show(screen, storage, start_index);
    });
    add_button  = Button("  Add  ", [&] {
        auto entry = AddUI::show(screen);
        storage.add(entry);
        storage.commit();
        storage.save();
        screen.ExitLoopClosure();
        DashboardUI::show(screen, storage, start_index);
    });
    delete_button = Button("  Delete  ", [&] {
        int id;
        IdEntryUI::show(screen, id);
        if (id == -1) {
            return;
        }
        int index = storage.findById(id);
        if (index == -1) {
            MessageUI::show(screen, "Entry with id " + to_string(id) + " was not found!");
            return;
        }
        storage.removeById(id);
        screen.ExitLoopClosure();
        DashboardUI::show(screen, storage, start_index);
    });
    exit_button = Button("  Exit  ", [&] {
        storage.save();
        screen.ExitLoopClosure();
        exit(EXIT_SUCCESS);
    });

    if (end_index + STEP <= entries.size()) {
        end_index = end_index + STEP;
    } else {
        end_index = entries.size();
    }

    if (start_index == 0) {
        can_go_back = false;
    } else {
        can_go_back = true;
    }

    if (end_index < entries.size()) {
        can_go_next = true;
    } else {
        can_go_next = false;
    }

    table_entries.push_back({ "   ID   ", "      NID      ", "      AREA      ", "      CATEGORY      ", "      NUMBER      "});
    for (uint32_t i = start_index; i < end_index; i++) {
        auto entry = entries[i];
        table_entries.push_back({ to_string(entry.id), entry.nid, entry.area, entry.category, entry.number });
    }

    auto table = Table({
        table_entries,
    });
    table.SelectAll().Border(LIGHT);
    table.SelectAll().Separator(LIGHT);
    table.SelectAll().DecorateCells(center);

    auto document = table.Render();
    container = Container::Horizontal({ back_page, next_page, view_button, add_button, delete_button, exit_button });
    view = Renderer(container, [&] {
        return window(text(" Phoenix Systems ") | hcenter | bold, vbox({
            text(" All Entries - " + to_string(start_index + 1) + " to " + to_string(end_index) + " ( " + to_string(storage.all().size()) + " )") | center | color(Color::Green),
            separator(),
            document,
            hbox({ back_page->Render(), next_page->Render(), filler(),
                   view_button->Render(), filler(),
                   add_button->Render(), filler(),
                   delete_button->Render(), filler(),
                   exit_button->Render() }),

        }) | border | center);
    });
    screen.Loop(view);
}

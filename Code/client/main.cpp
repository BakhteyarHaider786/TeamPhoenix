#include "../common/misc/exit_handler.h"
#include "../common/misc/signal_handler.h"
#include "../common/storage/storage.h"
#include "../common/ui/id_entry_ui.h"
#include "../common/ui/message_ui.h"
#include "../common/ui/entry_detail_ui.h"

#include <iostream>
#include <ftxui/component/screen_interactive.hpp>

using namespace ftxui;
using std::cout;
using std::endl;
using std::to_string;

static std::uint64_t counter = 0;

#define STORAGE_NAME "storage.data"

int main(int argc, const char* argv[]) {
    SignalHandler::registerHandler();
    ExitHandler::registerHandler();
    ExitHandler::addFunction([=] {
        system("cls");
        std::cout << "Total Run : " << counter << std::endl;
    });

    Storage storage(STORAGE_NAME);
    int index, id;
    entry_t entry;

    auto screen = ScreenInteractive::Fullscreen();

    while (true) {
        IdEntryUI::show(screen, id);

        if (id == -1) {
            MessageUI::show(screen, "Enter a valid id!");
        } else {
            index = storage.findById(id);

            if (index == -1) {
                MessageUI::show(screen, "Entry with id " + to_string(id) + " was not found!");
            } else {
                entry = storage.getByIndex(index);
                EntryDetailUI::show(screen, entry);
            }
        }


    }


    return 0;
}
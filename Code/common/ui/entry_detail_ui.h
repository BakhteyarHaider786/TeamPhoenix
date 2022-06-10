#ifndef PHOENIXSYS_ENTRY_DETAIL_UI_H
#define PHOENIXSYS_ENTRY_DETAIL_UI_H

#include "../structs/entry_struct.h"

#include <ftxui/component/screen_interactive.hpp>

class EntryDetailUI {
public:
    static void show(ftxui::ScreenInteractive& screen, entry_t entry);
};


#endif //PHOENIXSYS_ENTRY_DETAIL_UI_H

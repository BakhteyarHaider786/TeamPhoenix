#ifndef PHOENIXSYS_ADD_UI_H
#define PHOENIXSYS_ADD_UI_H

#include "../../common/structs/entry_struct.h"

#include <ftxui/component/screen_interactive.hpp>

class AddUI {
public:
    static entry_t show(ftxui::ScreenInteractive& screen);
};


#endif //PHOENIXSYS_ADD_UI_H

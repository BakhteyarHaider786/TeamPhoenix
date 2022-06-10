#ifndef PHOENIXSYS_DASHBOARD_UI_H
#define PHOENIXSYS_DASHBOARD_UI_H

#include "../../common/structs/entry_struct.h"
#include "../../common/storage/storage.h"

#include <vector>
#include <ftxui/component/screen_interactive.hpp>

class DashboardUI {
public:
    static void show(ftxui::ScreenInteractive &screen, Storage& storage, uint32_t start_index = 0);
};


#endif //PHOENIXSYS_DASHBOARD_UI_H

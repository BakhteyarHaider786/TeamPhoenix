#ifndef PHOENIXSYS_QR_CODE_GEN_H
#define PHOENIXSYS_QR_CODE_GEN_H

#include "../structs/entry_struct.h"

#include <string>
#include <ftxui/component/screen_interactive.hpp>

using namespace ftxui;

class QrCodeGen {
public:
    static std::string saveToFile(entry_t entry);
};


#endif //PHOENIXSYS_QR_CODE_GEN_H

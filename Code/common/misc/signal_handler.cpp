#include "signal_handler.h"
#include "exit_handler.h"

#include <iostream>
#include <csignal>
#include <thread>

using namespace std::literals;

using std::cout;
using std::endl;

static int signal_code = EXIT_SUCCESS;
static bool handler_registered = false;

void callHandler(int code) {
    signal_code = code;
    std::exit(code);
}

void SignalHandler::registerHandler() {
    if (!handler_registered) {
        for (int signal : {SIGTERM, SIGSEGV, SIGINT, SIGILL, SIGABRT, SIGFPE}) {
            std::signal(signal, callHandler);
        }
        handler_registered = true;
    }

    ExitHandler::addFunction([=] {
        int code = SignalHandler::signalCode();
        switch (code) {
            case SIGINT:
                cout << "SignalHandler : Program was terminated (" << code << ")" << endl;
                break;
            case SIGSEGV:
                cout << "SignalHandler : Segment violation occurred (" << code << ")" << endl;
                break;
            case SIGABRT:
                cout << "SignalHandler : Abnormal termination triggered (" << code << ")" << endl;
                break;
            case EXIT_SUCCESS:
                cout << "SignalHandler : Program ended successfully (" << code << ")" << endl;
                break;
            default:
                cout << "SignalHandler : Exited with unknown code (" << code << ")" << endl;
                break;
        }
        std::this_thread::sleep_for(1s);
    });
}

int SignalHandler::signalCode() {
    return signal_code;
}

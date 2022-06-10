#include "exit_handler.h"

#include <Windows.h>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <thread>

using namespace std::literals;

using std::chrono::steady_clock;
using std::function;
using std::cout;
using std::endl;

using time_point_t = std::chrono::time_point<steady_clock>;
using exit_functions_t = std::stack<void_function_t>;

static time_point_t start_time; //NOLINT
static exit_functions_t exit_functions; //NOLINT
static bool handler_registered;


bool isExitButtonsPushed() {
    return GetKeyState(VK_CONTROL) & 0x8000 && GetKeyState(VK_SHIFT) & 0x8000 && GetKeyState(VK_F10) & 0x8000;
}

DWORD WINAPI checkForExitCommand(LPVOID lpParam) {
    while (true) {
        std::this_thread::sleep_for(1ms);
        if (isExitButtonsPushed()) {
            break;
        }
    }
    exit(0);
}

void callHandler() {
    while (!exit_functions.empty()) {
        auto exit_function = exit_functions.top();
        exit_functions.pop();
        exit_function();
    }
}

void ExitHandler::registerHandler() {
    if (!handler_registered) {
        start_time = steady_clock::now();
        CreateThread(nullptr, 0, checkForExitCommand, nullptr, 0, nullptr);

        ExitHandler::addFunction([=] {
            cout << "Total Run-Time : ";
            time_point_t end_time = steady_clock::now();
            cout << (end_time - start_time) / 1s
                      << " sec / "
                      << (end_time - start_time) / 1ms
                      << " ms"
                      << endl;
        });

        atexit(callHandler);
        handler_registered = true;
    }
}

void ExitHandler::addFunction(const void_function_t& function) {
    exit_functions.push(function);
}


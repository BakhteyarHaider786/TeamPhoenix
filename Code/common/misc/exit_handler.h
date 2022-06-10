#ifndef PHOENIXSYS_EXIT_HANDLER_H
#define PHOENIXSYS_EXIT_HANDLER_H

#include <functional>
#include <stack>

using void_function_t = std::function<void()>;

class ExitHandler {
public:
    static void registerHandler();
    static void addFunction(const void_function_t& function);
};


#endif //PHOENIXSYS_EXIT_HANDLER_H

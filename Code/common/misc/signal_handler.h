#ifndef PHOENIXSYS_SIGNAL_HANDLER_H
#define PHOENIXSYS_SIGNAL_HANDLER_H


class SignalHandler {
public:
    static void registerHandler();
    static int signalCode();
};


#endif //PHOENIXSYS_SIGNAL_HANDLER_H

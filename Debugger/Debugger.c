
#include "Debugger.h"
#include <stdarg.h>

#define SET_DEBUGGER_METHOD_NAME(name) __DEBUGGERTOOL__FUNCTION__##name

static size_t SET_DEBUGGER_METHOD_NAME(log)(char** format, ...) {
    
}

static void SET_DEBUGGER_METHOD_NAME(start)() {

}

static void SET_DEBUGGER_METHOD_NAME(end)() {

}

fdebugger getKitDebugger() {
    fdebugger kit = {
        .log = SET_DEBUGGER_METHOD_NAME(log),
        .start = SET_DEBUGGER_METHOD_NAME(start),
        .end = SET_DEBUGGER_METHOD_NAME(end),
    };
    return kit;
}
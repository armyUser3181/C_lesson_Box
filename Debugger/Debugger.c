
#include "Debugger.h"
#include <stdarg.h>

#define SET_DEBUGGER_METHOD_NAME(name) __DEBUGGERTOOL__FUNCTION__##name

static size_t debugMode = 0;

static size_t SET_DEBUGGER_METHOD_NAME(log)(const char* format, ...) {
    if(debugMode == 0) return 0;
    char* corser = format;
    size_t line = 0;
    while(*corser) {
        int hcode = *corser;

        switch(line) {
            default:

            switch(hcode) {
                case '%':
                break;
                default:
                
                break;
            }
            line = __LINE__; break; case __LINE__:


        }
        corser++;
    }
}

static void SET_DEBUGGER_METHOD_NAME(start)() {
    debugMode = 1;
}

static void SET_DEBUGGER_METHOD_NAME(end)() {
    debugMode = 0;
}

fdebugger getKitDebugger() {
    fdebugger kit = {
        .log = SET_DEBUGGER_METHOD_NAME(log),
        .start = SET_DEBUGGER_METHOD_NAME(start),
        .end = SET_DEBUGGER_METHOD_NAME(end),
    };
    return kit;
}
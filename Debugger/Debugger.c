
#include "Debugger.h"
#include <stdarg.h>

#define SET_DEBUGGER_METHOD_NAME(name) __DEBUGGERTOOL__FUNCTION__##name

static size_t debugMode = 0;
static char* debugMemory = NULL;

static void SET_DEBUGGER_METHOD_NAME(setMemory)(char* ptr) {
    
}

static size_t SET_DEBUGGER_METHOD_NAME(log)(const char* format, ...) {
    if(debugMode == 0) return 0;
    char* corser = format;
    size_t line = 0;
    while(*corser) {
        int hcode = *corser++;

        switch(line) {
            default:


            if( hcode != '%' ) continue;
            line = __LINE__; break; case __LINE__:


        }
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
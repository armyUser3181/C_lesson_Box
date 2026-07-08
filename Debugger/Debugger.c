
#include "Debugger.h"
#include <stdarg.h>
#include <string.h>

#define SET_DEBUGGER_METHOD_NAME(name) __DEBUGGERTOOL__FUNCTION__##name

static struct {
    size_t debugMode;
    struct {
        size_t line;
    } engine;
    struct {
        size_t top;
        size_t size;
        char* ptr;
    } memory;
} debug_context = {
    .debugMode = 0,
};

static void debug_printf_engine(int* ch) {
    switch( debug_context.engine.line ) {
        
        if( strchr("-+0 #", *ch) != NULL ) {

        } else { debug_context.engine.line = __LINE__; break; } case __LINE__:
        if( strchr("1234567890", *ch) != NULL ) {

        } else { debug_context.engine.line = __LINE__; break; } case __LINE__:
        if( strchr(".", *ch) != NULL ) {

        } else { debug_context.engine.line = __LINE__; break; } case __LINE__:
        if( strchr("-+0 #", *ch) != NULL ) {

        } else { debug_context.engine.line = __LINE__; break; } case __LINE__:
        if( strchr("hll", *ch) != NULL ) {

        } else { debug_context.engine.line = __LINE__; break; } case __LINE__:
        //debug_context.engine.line = __LINE__; break; case __LINE__:
        //debug_context.engine.line = __LINE__; break; case __LINE__:
        //debug_context.engine.line = __LINE__; break; case __LINE__:
    }
}





static void SET_DEBUGGER_METHOD_NAME(setMemory)(char* ptr, size_t size) {
    debug_context.memory.ptr = ptr;
    debug_context.memory.size = size;
}

static size_t SET_DEBUGGER_METHOD_NAME(log)(const char* format, ...) {
    if(debug_context.debugMode == 0) return 0;
    char* corser_low = format;
    char* corser_high = format;
    size_t line = 0;
    while(*corser_high) {
        int* hcode = corser_high++;

        switch(line) {
            default:
            if( *hcode != '%' ) continue;
            {
                char* ptr = debug_context.memory.ptr + debug_context.memory.top;
                size_t max_size = debug_context.memory.size - debug_context.memory.top;
                size_t size = hcode - corser_low - 1;
                if( max_size < size ) {
                    puts("error: out of memory in debugger ");
                    return 0;
                }
                memcpy(ptr, corser_low, size);
                debug_context.memory.top += size;
            }
            line = __LINE__; break; case __LINE__:

        }
    }

}

static void SET_DEBUGGER_METHOD_NAME(start)() {
    debug_context.debugMode = 1;
}

static void SET_DEBUGGER_METHOD_NAME(end)() {
    debug_context.debugMode = 0;
}

fdebugger getKitDebugger() {
    fdebugger kit = {
        .log = SET_DEBUGGER_METHOD_NAME(log),
        .start = SET_DEBUGGER_METHOD_NAME(start),
        .end = SET_DEBUGGER_METHOD_NAME(end),
        .setMemory = SET_DEBUGGER_METHOD_NAME(setMemory),
    };
    return kit;
}

#include "Debugger.h"
#include <stdarg.h>
#include <string.h>

#define SET_DEBUGGER_METHOD_NAME(name) __DEBUGGERTOOL__FUNCTION__##name
#define DEBUG_LOG(format, args...) printf("%d:" format, __LINE__, args )
#define DEBUG_ERROR_LOG(format, args...) DEBUG_LOG(" ERROR :" format, args)
#define DEBUG_PUT(string) DEBUG_LOG("%s", string)
#define DEBUG_ERROR_PUT(string) DEBUG_ERROR_LOG("%s", string)


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
    struct {
        size_t size;
        char* ptr;
    } put;
} debug_context = {
    .debugMode = 0,
};

static struct struct_put_struct {
    char* ptr;
    char* low;
    size_t max_size;
    size_t size;
    int fall;
};


static struct struct_put_struct get_put_struct(char* low, char* high) {
    struct struct_put_struct unit;
    unit.ptr = debug_context.memory.ptr + debug_context.memory.top;
    unit.max_size = debug_context.memory.size - debug_context.memory.top;
    unit.size = high - low;
    unit.fall = unit.max_size < unit.size;
    return unit;
}

static int debug_context_memory_write(char* low, char* high) {
    struct struct_put_struct unit = get_put_struct(low, high);
    if( unit.fall ) {
        DEBUG_ERROR_PUT("error: out of memory in debugger ");
        return -1;
    }
    memcpy(unit.low, unit.ptr, unit.size);
    debug_context.memory.top += unit.size;
    return unit.size;
}

static int debug_context_memory_write_printf(char* low, char* high, va_list list ) {
    struct struct_put_struct unit = get_put_struct(low, high);
    int count = 0; va_list list_cp; va_copy(list_cp, list);
    char* space = debug_context.put.ptr;
    size_t space_size = debug_context.put.size;
    if( space_size < unit.size + 1 ) {
        DEBUG_ERROR_PUT("error: out of memory in debugger ");
        return -1;
    }
    memcpy(unit.low, space, unit.size);
    space[unit.size] = '\0';
    size_t input_size = vsnprintf(NULL, 0, space, list_cp);
    va_end(list_cp);
    if( unit.max_size < input_size + 1 ) {
        DEBUG_ERROR_PUT("error: out of memory in debugger ");
        return -1;
    }
    count = vsnprintf(unit.ptr, input_size + 1, space, list);
    return count;
}

static int debug_printf_engine(char* ch) {
    switch( debug_context.engine.line ) {
        default:
        if( strchr("-+0 #", *ch) == NULL ) {

        } else { 
            
            debug_context.engine.line = __LINE__; break; } case __LINE__:
        if( '0' <= *ch && *ch <= '9' ) {

            break;
        } else { 
            debug_context.engine.line = __LINE__; /*  */ } case __LINE__:
        if( '.' != *ch ) {

        } else {
            debug_context.engine.line = __LINE__; break; } case __LINE__:
        if( strchr("-+0 #", *ch) == NULL ) {

        } else { 
            debug_context.engine.line = __LINE__; break; } case __LINE__:
        if( *ch == 'h' ) {
            debug_context.engine.line = __LINE__; break; case __LINE__:
        } else
        if( *ch == 'l' ) {
            debug_context.engine.line = __LINE__; break; case __LINE__:
            if( *ch == 'l') {
                debug_context.engine.line = __LINE__; break; case __LINE__:
            }
        }
        if( strchr("diufeEgGcsoxXp", *ch) == NULL ) {
            if( *ch == '%' ) {
                debug_context.engine.line = 0;
                return 2; // print %
            }
        } else {

            return 1; // print start
        }

        //debug_context.engine.line = __LINE__; break; case __LINE__:
        //debug_context.engine.line = __LINE__; break; case __LINE__:
        //debug_context.engine.line = __LINE__; break; case __LINE__:
    }
    return 0; // no print
}

static void SET_DEBUGGER_METHOD_NAME(setMemory)(char* ptr, size_t size) {
    debug_context.memory.ptr = ptr;
    debug_context.memory.size = size;
    /* debug_context.put.ptr = ptr + size - 32;
    debug_context.put.size = 32; */
}

static int SET_DEBUGGER_METHOD_NAME(log)(const char* format, ...) {
    if(debug_context.debugMode == 0) return 0;
    int count = 0;
    char* corser_low = (char*)format;
    char* corser_high = (char*)format;
    size_t line = 0;
    while(*corser_high) {
        char* hcode = corser_high++;

        switch(line) {
            default:
            if( *hcode != '%' ) continue;
            {
                debug_context_memory_write(corser_low, hcode);
                corser_low = hcode;
            }
            line = __LINE__; break; case __LINE__:
            switch( debug_printf_engine(hcode) ) {
                case 2: { count += debug_context_memory_write(corser_low + 1, hcode); } break; case 1: {
                    count += debug_context_memory_write_printf(corser_low, corser_high);
                } break; case 0: continue;
            }

        }
    }
    return 0;
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
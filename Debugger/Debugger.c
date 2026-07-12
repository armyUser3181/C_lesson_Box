
#include "Debugger.h"
#include <stdarg.h>
#include <string.h>

#define SET_DEBUGGER_METHOD_NAME(name) __DEBUGGERTOOL__FUNCTION__##name
#define DEBUG_LOG(format, args...) printf("%d:" format, __LINE__, args )
#define DEBUG_ERROR_LOG(format, args...) DEBUG_LOG(" ERROR :" format, args)
#define DEBUG_PUT(string) DEBUG_LOG("%s\n", string)
#define DEBUG_ERROR_PUT(string) DEBUG_ERROR_LOG("%s\n", string)
#define MEMORY_DESIGN_SIZE(size) 128 * size

static struct {
    struct {
        char* ptr;
        size_t size;
        char* top;
        char* last;
    } memory;
    struct {
        size_t table;
        size_t stream;
        size_t put;
    } line;
    struct {
        char* table;
        char* stream;
        char* put;
    } point;
    struct {
        size_t table;
        size_t stream;
        size_t put;
    } size;
} memory_design = {
    .size.table = 256,
    .line.stream = 256,
    .size.stream = MEMORY_DESIGN_SIZE(16),
    .line.put = 256 + MEMORY_DESIGN_SIZE(16),
    .size.put = MEMORY_DESIGN_SIZE(2),
};

static struct {
    size_t debugMode;
    struct {
        size_t line;
    } engine;
    struct {
        size_t top;
        size_t size;
        char* ptr;
    } stream;
    struct {
        size_t size;
        char* ptr;
    } put;
    struct {
        size_t size;
        char* ptr;
    } table;
    
} debug_context = {
    .stream.ptr = NULL,
    .put.ptr = NULL,
    .table.ptr = NULL,
    .table.size = 0,
};

struct struct_put_struct {
    char* ptr;
    char* low;
    size_t max_size;
    size_t size;
    int fall;
};


static struct struct_put_struct get_put_struct(char* low, char* high) {
    struct struct_put_struct unit;
    unit.ptr = debug_context.stream.ptr + debug_context.stream.top;
    unit.low = low;
    unit.max_size = debug_context.stream.size - debug_context.stream.top;
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
    memcpy(unit.ptr, unit.low, unit.size);
    //DEBUG_ERROR_PUT(unit.ptr);
    debug_context.stream.top += unit.size;
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
    memcpy(space, unit.low, unit.size);
    space[unit.size] = '\0';
    size_t input_size = vsnprintf(NULL, 0, space, list_cp);
    va_end(list_cp);
    if( unit.max_size < input_size + 1 ) {
        DEBUG_ERROR_PUT("error: out of memory in debugger ");
        return -1;
    }
    count = vsnprintf(unit.ptr, input_size + 1, space, list);
    debug_context.stream.top += count;
    return count;
}

static int debug_printf_engine(char* ich) { // priss
    unsigned char* ch = (unsigned char*)ich;
    
    switch(debug_context.engine.line) {
        default: 
        if( debug_context.table.ptr[*ch] & debug_context.table.ptr['-'] ) { 
            debug_context.engine.line = __LINE__; // break; case __LINE__: 
        }
        if( debug_context.table.ptr[*ch] & debug_context.table.ptr['*'] ) {
            debug_context.engine.line = __LINE__; break; case __LINE__:
        } else {
            debug_context.engine.line = __LINE__; case __LINE__:
            if( debug_context.table.ptr[*ch] & debug_context.table.ptr['1'] ) break;
        }
        if( debug_context.table.ptr[*ch] & debug_context.table.ptr['.'] ) {
            debug_context.engine.line = __LINE__; break; case __LINE__:
            if( debug_context.table.ptr[*ch] & debug_context.table.ptr['*'] ) {
                debug_context.engine.line = __LINE__; break; case __LINE__:
            } else {
                debug_context.engine.line = __LINE__; case __LINE__:
                if( debug_context.table.ptr[*ch] & debug_context.table.ptr['1'] ) break;
            }
        }
        if( debug_context.table.ptr[*ch] & debug_context.table.ptr['l'] ) {
            debug_context.engine.line = __LINE__; break; case __LINE__: 
        }
        if( debug_context.table.ptr[*ch] & ( debug_context.table.ptr['l'] | debug_context.table.ptr['h'] ) ) {
            debug_context.engine.line = __LINE__; break; case __LINE__: 
        }
        if( debug_context.table.ptr[*ch] & debug_context.table.ptr['d'] ) { 
            debug_context.engine.line = 0;
            return 1; // read true
        }
        if( *ch == '%') {
            return 2; // % read
        }
        return -1; // false
    }
    return 0; // no read
}

static void settingTable(char* ptr, size_t size) {
    const char* curser = NULL;
    if(256 > size) return;
    curser = "-+0# ";
    while(*curser) {
        ptr[(unsigned char)*curser++] |= 1; // 첫번째 분기
    }
    curser = "0123456789";
    while(*curser) {
        ptr[(unsigned char)*curser++] |= 2; // 숫자 분기
    }
    curser = "*";
    while(*curser) {
        ptr[(unsigned char)*curser++] |= 4; // * 분기
    }
    curser = ".";
    while(*curser) {
        ptr[(unsigned char)*curser++] |= 8; // . 분기
    }
    curser = "hz";
    while(*curser) {
        ptr[(unsigned char)*curser++] |= 16; // 크기 분기
    }
    curser = "l";
    while(*curser) {
        ptr[(unsigned char)*curser++] |= 32; // 크기 분기 2
    }
    curser = "diufeEgGcsoxXp";
    while(*curser) {
        ptr[(unsigned char)*curser++] |= 64; // 타입 분기
    }
}

static void SET_DEBUGGER_METHOD_NAME(setMemory)(char* ptr, size_t size) {
    memory_design.memory.ptr = ptr;
    memory_design.memory.size = size; // 4096
    memory_design.point.table = ptr + memory_design.line.table;
    memory_design.point.stream = ptr + memory_design.line.stream;
    memory_design.point.put = ptr + memory_design.line.put;
    memory_design.memory.last = ptr + size;
    memory_design.memory.top = ptr + memory_design.line.put + memory_design.size.put;
    debug_context.stream.ptr = memory_design.point.stream;
    debug_context.put.ptr = memory_design.point.put;
    debug_context.stream.size = memory_design.size.stream;
    debug_context.put.size = memory_design.size.put;
    debug_context.table.ptr = memory_design.point.table;
    debug_context.table.size = memory_design.size.table;
    settingTable(debug_context.table.ptr, debug_context.table.size);
}

static int SET_DEBUGGER_METHOD_NAME(log)(const char* format, ...) {
    if(debug_context.debugMode == 0) return 0;
    int count = 0;
    char* corser_low = (char*)format;
    char* corser_high = (char*)format;
    size_t line = 0;
    va_list list;
    va_start(list, format);
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
                case 2: { 
                    count += debug_context_memory_write(corser_low + 1, hcode); 
                    corser_low = corser_high;
                    line = 0; 
                } break; case 1: {
                    count += debug_context_memory_write_printf(corser_low, corser_high, list);
                    corser_low = corser_high;
                    /* char ps[1024] = {0};
                    memcpy(ps, corser_low, 1024);
                    vprintf(ps, list); */
                    line = 0;
                } break; case 0: break;
            }
        }
    }
    debug_context_memory_write(corser_low, corser_high);
    va_end(list);
    printf("%s", debug_context.stream.ptr);
    debug_context.stream.top = 0;
    return count;
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
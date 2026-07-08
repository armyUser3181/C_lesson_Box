
#include <stdio.h>

typedef struct fdebugger {
    size_t (*log)(const char*, ...);
    void (*start)();
    void (*end)();
} fdebugger;

extern fdebugger getKitDebugger();

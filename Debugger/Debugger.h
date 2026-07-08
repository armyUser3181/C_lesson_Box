
#include <stdio.h>

typedef struct fdebugger {
    size_t (*log)(const char*, ...);
    void (*start)();
    void (*end)();
    void (*setMemory)(char*, size_t);
} fdebugger;

extern fdebugger getKitDebugger();

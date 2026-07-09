
#include <stdio.h>

typedef struct fdebugger {
    int (*log)(const char*, ...);
    void (*start)();
    void (*end)();
    void (*setMemory)(char*, size_t);
} fdebugger;

extern fdebugger getKitDebugger();

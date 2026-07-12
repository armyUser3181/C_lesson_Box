
#include <stdio.h>

typedef struct fdebugger {
    int (*log)(const char*, ...);
    int (*logln)(const char*, ...);
    void (*start)();
    void (*stop)();
    void (*end)();
    void (*setMemory)(char*, size_t);
} fdebugger;

extern fdebugger getKitDebugger();

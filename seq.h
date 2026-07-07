#define SEQ static _Thread_local unsigned long long int SEQ__POINT__LINE = __LINE__; switch( SEQ__POINT__LINE ) { case __LINE__:
#define YED( value ) SEQ__POINT__LINE = __LINE__; return value; case __LINE__:
#define END }

typedef int (*LoopFunction)(int argc, char** argv);

typedef struct {
    LoopFunction function;
    int argc;
    char **argv;
    
} LoopFunctionStruct;
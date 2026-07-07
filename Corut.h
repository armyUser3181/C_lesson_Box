
#define YED return __LINE__; case __LINE__

typedef unsigned long long size_t;

struct Corut;
typedef size_t (*CorutFunction)(struct Corut*);

typedef struct {
    size_t line;
    size_t argc;
    char** argv;
    CorutFunction func;
} Corut;


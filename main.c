#include <stdio.h>
#include 'Node.h'

#define YED return __LINE__; case __LINE__



struct Corut;
typedef (*CorutFunction)(struct Corut*);

typedef struct {
    size_t line;
    size_t argc;
    char** argv;
    CorutFunction func;
} Corut;

typedef struct {
    size_t corutc;
    Corut* corutv;
    size_t order;
} Engine;




int settingMemory() {
    return ;
}

int start() {
    return 0;
}

int run() {
    return 0;
}

int tast(Corut* cor) {
    switch ( cor->line ) {
        default:
        printf("hello world\n");
        printf("%s\n", cor->argv[0]);
        YED:
        printf("%s\n", cor->argv[1]);
        YED:
        printf("%s\n", cor->argv[2]);

    }
}

int main(int argc, char** argv) {
    char* args[] = {"hello world 1", "hello world 2", "hello world 3"};
    Corut cor = {
        .line = 0,
        .argc = 3,
        .argv = args,
    };
    for(int i = 0; i < 3; i++) {
        cor.line = tast(&cor);
    }
    return 0;
}


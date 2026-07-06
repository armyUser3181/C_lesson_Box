#include <stdio.h>

#define SEQ static _Thread_local unsigned long long int SEQ__POINT__LINE = __LINE__; switch( SEQ__POINT__LINE ) { case __LINE__:
#define YED( value ) SEQ__POINT__LINE = __LINE__; return value; case __LINE__:
#define END }


typedef int (*LoopFunction)(int argc, char** argv);

typedef struct {
    LoopFunction function;
    int argc;
    char **argv;
    
} LoopFunctionStruct;



int settingMemory() {

}

int start() {

}

int run() {

}

int seqTast() {
    SEQ
        printf("hello world 1 \n");
        YED( 1 )
        printf("hello world 2 \n");
        YED( 2 )
        printf("hello world 3 \n");
        YED( 3 )
        printf("hello world 4 \n");
    END
        return 4;
}

int main(int argc, char** argv) {
    for(int i = 0; i < 5; i++) {
        seqTast();
    }
    return 0;
}


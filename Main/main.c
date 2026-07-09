#include <stdio.h>
#include "../Node/Node.h"
//#include "Corut.h"

#define REY context.line = __LINE__; return; case __LINE__

enum Flow {
    Flow_Main,
    Flow_StackUp,
    Flow_StackDone,
    Flow_End,
};

static struct {
    size_t line;
    enum Flow flow;
    fstack stack;
    Node* node;
} context;



void mainEngine() {
    switch( context.line ) {
        default:
        printf("1hello world\n");
        context.flow = Flow_StackUp;
        REY:
        printf("2hello world\n");
        context.flow = Flow_StackUp;
        REY:
        printf("3hello world\n");
        context.stack.getInt(context.node)[0] = 100;
        context.flow = Flow_StackUp;
        REY: {
            Node* next = context.node;
            printf("next: %p seek: %p\n", next, context.stack.seek(next));
            while( (next = context.stack.seek(next)) ) {
                int* i = context.stack.getInt(next);
                char* c = context.stack.getChar(next);
                printf("i: %d, c: %c\n", *i, *c);
            }
            printf("4hello world\n");
        }
        context.flow = Flow_End;
    }
}

void stackEngine() {
    Node node = {0};
    printf("next: %p\n", &node);
    context.node = context.stack.push(context.node, &node);
    while(1) switch(context.flow) {
        case Flow_Main: mainEngine();
        break;
        case Flow_StackUp: context.flow = Flow_Main;
        stackEngine();
        break;
        case Flow_StackDone: context.flow = Flow_Main;
        context.node = context.stack.seek(context.node);
        return;
        break;
        case Flow_End:
        return;
    }
}

//int main(int argc, char** argv)
int main(void) {
    context.flow = Flow_Main;
    context.line = 0;
    context.node = NULL;
    context.stack = getKitStack();
    stackEngine();
    return 0;
}


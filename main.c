#include <stdio.h>
#include "Node.h"
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
    swtich( context.line ) {
        default:
        printf("1hello world\n");
        REY:
        printf("2hello world\n");
        REY:
        printf("3hello world\n");
        REY:
        context.flow = Flow_End;
    };
}

void stackEngine() {
    Node node = {0};
    context.node = context.stack.push(context.node, &node);
    while(1) switch(context.flow) {
        case Flow_Main: mainEngine();
        break;
        case Flow_StackUp: context.flow = Flow_Main;
        stackEngine();
        break;
        case Flow_StackDone: context.flow = Flow_Main;
        return;
        break;
        case Flow_End:
        return;
    };
}

int main(int argc, char** argv) {
    context.flow = Flow_Main;
    context.line = 0;
    context.stack = getKitStack();
    stackEngine();
    return 0;
}


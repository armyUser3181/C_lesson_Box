

#include "Node.h"

#define SET_STACKTOOL_METHOD_NAME(name) __STACKTOOL__FUNCTION__##name

static Node* SET_STACKTOOL_METHOD_NAME(push)(Node* node, Node* next) {
    return node->next = next;
}

static Node* SET_STACKTOOL_METHOD_NAME(seek)(Node* node) {
    return node->next;
}

static int* SET_STACKTOOL_METHOD_NAME(getInt)(Node* node) {
    return node->data.i;
}

static char* SET_STACKTOOL_METHOD_NAME(getChar)(Node* node) {
    return node->data.c;
}

extern stack getStackTool() {
    stack kit = {
        .push = SET_STACKTOOL_METHOD_NAME(push),
        .seek = SET_STACKTOOL_METHOD_NAME(seek),
        .getChar = SET_STACKTOOL_METHOD_NAME(getChar),
        .getInt = SET_STACKTOOL_METHOD_NAME(getInt),
    }
}
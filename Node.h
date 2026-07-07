
typedef struct Node {
    union {
        char c[56];
        int i[23];
    } data;
    struct Node* next;
} Node;

typedef struct stack {
    Node* (*push)(Node*, Node*);
    Node* (*seek)(Node*);
    int* (*getInt)(Node*);
    char* (*getChar)(Node*);
} stack;

extern stack getStackTool();
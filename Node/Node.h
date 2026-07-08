
typedef struct Node {
    union {
        char c[56];
        int i[14];
        void* v[7];
    } data;
    struct Node* next;
} Node;

typedef struct fstack {
    Node* (*push)(Node*, Node*);
    Node* (*seek)(Node*);
    int* (*getInt)(Node*);
    char* (*getChar)(Node*);
} fstack;

extern fstack getKitStack();

#include "../Node/Node.h"
#include "../Container.h"

typedef struct {
    Container Container;
    
    Node* head;
    Node* tail;
    Node** list;
    size_t size;
} Auque;
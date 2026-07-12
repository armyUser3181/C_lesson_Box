
#define definedContainerClass(name, append); typedef struct { size_t size; char* ptr; } name;

definedContainerClass(Container, );

#define definedContainer(name) definedContainerClass(name, \
    \
);
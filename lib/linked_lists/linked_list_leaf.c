#include "linked_list_leaf.h"


// node structure definition
typedef struct _LIST_NODE_LEAF {
    LEAF* child_leaf_pointer;
    LIST_NODE_LEAF* next_node;
} LIST_NODE_LEAF;

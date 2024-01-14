// #ifndef _HEADER_LL
// #define _HEADER_LL

// typedef unsigned int INDEX;

// #endif


#ifndef _HEADER_LL_LEAF
#define _HEADER_LL_LEAF


// #include <stdio.h>
// #include <stdlib.h>

#include "..\types.h"
// #include "..\dungeon.h"


// structures
// typedef struct _LEAF LEAF;
// typedef struct _LIST_NODE_LEAF {
//     LEAF* pointer_leaf;
//     struct _LIST_NODE_LEAF* next_node;
// } LIST_NODE_LEAF;
// typedef struct _LIST_LEAF {
//     LIST_NODE_LEAF* first_node;
// } LIST_LEAF;


// functions
LIST_LEAF lll_create_empty_list();
INDEX lll_length(LIST_LEAF linked_list);
void lll_append(LIST_LEAF* linked_list, LEAF value);
LEAF* lll_get_value_pointer(LIST_LEAF linked_list, INDEX index);
void lll_erase_content(LIST_LEAF* linked_list);


#endif

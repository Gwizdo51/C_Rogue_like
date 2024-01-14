// #ifndef _HEADER_LL
// #define _HEADER_LL

// typedef unsigned int INDEX;

// #endif


#ifndef _HEADER_LL_EDGE
#define _HEADER_LL_EDGE


// #include <stdio.h>
// #include <stdlib.h>

#include "..\types.h"
// #include "..\dungeon.h"


// structures
// typedef struct _LIST_NODE_GRAPH_EDGE {
//     GRAPH_EDGE graph_edge;
//     struct _LIST_NODE_GRAPH_EDGE* next_node;
// } LIST_NODE_GRAPH_EDGE;
// typedef struct _LIST_GRAPH_EDGE {
//     LIST_NODE_GRAPH_EDGE* first_node;
// } LIST_GRAPH_EDGE;


// functions
LIST_GRAPH_EDGE lle_create_empty_list();
INDEX lle_length(LIST_GRAPH_EDGE linked_list);
void lle_append(LIST_GRAPH_EDGE* linked_list, GRAPH_EDGE value);
GRAPH_EDGE* lle_get_value_pointer(LIST_GRAPH_EDGE linked_list, INDEX index);
void lle_erase_content(LIST_GRAPH_EDGE* linked_list);


#endif

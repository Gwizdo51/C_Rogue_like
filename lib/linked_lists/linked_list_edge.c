#include "linked_list_edge.h"


// node structure definition
typedef struct _LIST_NODE_GRAPH_EDGE {
    GRAPH_EDGE graph_edge;
    LIST_NODE_GRAPH_EDGE* next_node;
} LIST_NODE_GRAPH_EDGE;


LIST_GRAPH_EDGE lle_create_empty_list() {
    LIST_GRAPH_EDGE linked_list = {.first_node = NULL};
    return linked_list;
}


// INDEX lle_length(LIST_GRAPH_EDGE linked_list) {

// }


// void lle_append(LIST_GRAPH_EDGE* linked_list, GRAPH_EDGE value) {

// }


// GRAPH_EDGE* lle_get_value_pointer(LIST_GRAPH_EDGE* linked_list, INDEX index) {

// }


// void lle_erase_content(LIST_GRAPH_EDGE* linked_list) {

// }

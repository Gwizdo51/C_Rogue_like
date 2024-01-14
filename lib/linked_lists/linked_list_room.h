// #ifndef _HEADER_LL
// #define _HEADER_LL

// typedef unsigned int INDEX;

// #endif


#ifndef _HEADER_LL_ROOM
#define _HEADER_LL_ROOM


// #include <stdio.h>
// #include <stdlib.h>

#include "..\types.h"
// #include "..\dungeon.h"


// structures
// typedef struct _LIST_NODE_ROOM {
//     ROOM room;
//     struct _LIST_NODE_ROOM* next_node;
// } LIST_NODE_ROOM;
// typedef struct _LIST_ROOM {
//     LIST_NODE_ROOM* first_node;
// } LIST_ROOM;


// functions
LIST_ROOM llr_create_empty_list();
INDEX llr_length(LIST_ROOM linked_list);
void llr_append(LIST_ROOM* linked_list, ROOM room);
ROOM* llr_get_value_pointer(LIST_ROOM linked_list, INDEX index);
void llr_erase_content(LIST_ROOM* linked_list);


#endif

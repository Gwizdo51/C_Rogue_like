// #ifndef _HEADER_LL
// #define _HEADER_LL

// typedef unsigned int INDEX;

// #endif


#ifndef _HEADER_LL_INDEX
#define _HEADER_LL_INDEX


// #include <stdio.h>
// #include <stdlib.h>

#include "..\types.h"
// #include "..\dungeon.h"


// functions
LIST_INDEX lli_create_empty_list();
INDEX lli_length(LIST_INDEX linked_list);
void lli_append(LIST_INDEX* linked_list, INDEX value);
INDEX lli_get_value(LIST_INDEX linked_list, INDEX index);
void lli_remove_by_index(LIST_INDEX* linked_list, INDEX index);
void lli_erase_content(LIST_INDEX* linked_list);


#endif

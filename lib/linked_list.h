#ifndef _HEADER_LINKED_LIST
#define _HEADER_LINKED_LIST

#include "types.h"

// functions
LIST ll_create(size_t data_size);
INDEX ll_length(LIST *linked_list);
void ll_append(LIST *linked_list, void *new_data);
void * ll_get(LIST *linked_list, INDEX index);
void ll_swap(LIST *linked_list, INDEX index_1, INDEX index_2);
void ll_remove(LIST *linked_list, INDEX index);
void ll_free(LIST *linked_list);

#endif

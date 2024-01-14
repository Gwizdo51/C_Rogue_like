#ifndef _HEADER_LINKED_LIST
#define _HEADER_LINKED_LIST

#include "types.h"

// functions

/*
Returns an empty linked list.

PARAMETERS
----------
size_t data_size
    The size of the data for each node of the list, in bytes.
*/
LIST ll_create(size_t data_size);

/*
Returns the length (the number of nodes) of a linked list.

PARAMETERS
----------
LIST *linked_list
    The pointer to the linked list.

RETURNS
-------
INDEX
    The length of the linked list.
*/
INDEX ll_length(LIST *linked_list);

/*
Adds a new node with the given data at the end of a linked list.

PARAMETERS
----------
LIST *linked_list
    The pointer to the linked list.
void *new_data
    The pointer to the data to add to the list.
    The new data is copied in the new node.
*/
void ll_append(LIST *linked_list, void *new_data);

/*
Returns the pointer to the data at the node with the given index.
The pointer returned is a void pointer, and needs to be cast to the appropriate pointer type.
If the index is out range, the program exits with a failure code.

PARAMETERS
----------
LIST *linked_list
    The pointer to the linked list.
INDEX index
    The index of the node from which to get the data pointer.

RETURNS
-------
void *
    The pointer to the data contained in the node.
*/
void *ll_get(LIST *linked_list, INDEX index);

/*
Swaps the nodes at the given indices.
If either index is out range, the program exits with a failure code.

PARAMETERS
----------
LIST *linked_list
    The pointer to the linked list.
INDEX index_1
    The index of the first node.
INDEX index_2
    The index of the second node.
*/
void ll_swap(LIST *linked_list, INDEX index_1, INDEX index_2);

/*
Removes the node at the given index.
If the index is out range, the program exits with a failure code.

PARAMETERS
----------
LIST *linked_list
    The pointer to the linked list.
INDEX index
    The index of the node to remove.
*/
void ll_remove(LIST *linked_list, INDEX index);

/*
Erases and frees the content of a linked list.

PARAMETERS
----------
LIST *linked_list
    The pointer to the linked list.
*/
void ll_free(LIST *linked_list);

#endif

// https://www.geeksforgeeks.org/generic-linked-list-in-c-2/
// https://medium.com/@fabiano.salles/generic-linked-list-in-c-157dc49767bc
#include "linked_list.h"


// node structure definition
typedef struct _LIST_NODE {
    void *data_pointer;
    LIST_NODE *next_node;
} LIST_NODE;


LIST ll_create(size_t data_size) {
    LIST linked_list = {
        .first_node = NULL,
        .data_size = data_size
    };
    return linked_list;
}

INDEX ll_length(LIST *linked_list) {
    INDEX list_length = 0;
    LIST_NODE *current_node = linked_list->first_node;
    while (current_node) {
        list_length++;
        current_node = current_node->next_node;
    }
    return list_length;
}

void ll_append(LIST *linked_list, void *new_data) {
    // create a new node with the new data
    // int i;
    LIST_NODE *new_node = (LIST_NODE*) malloc(sizeof(LIST_NODE));
    new_node->next_node = NULL;
    new_node->data_pointer = malloc(linked_list->data_size);
    // copy the data byte per byte (a char is 1 byte) -> use memcpy() instead
    // for (i=0; i<data_size; i++) {
    //     *(char*)(new_node->data_pointer + i) = *(char*)(new_data + i);
    // }
    memcpy(new_node->data_pointer, new_data, linked_list->data_size);
    // add the new node at the end of the list
    if (!linked_list->first_node) {
        // if the list is empty, the new node is the first node
        linked_list->first_node = new_node;
    }
    else {
        // otherwise, add the new node after the last node
        LIST_NODE *last_node = linked_list->first_node;
        while (last_node->next_node) {
            last_node = last_node->next_node;
        }
        last_node->next_node = new_node;
    }
}

void *ll_get(LIST *linked_list, INDEX index) {
    // exit with a failure code if the index is out of range
    if (index >= ll_length(linked_list)) {
        exit(EXIT_FAILURE);
    }
    // look for the node at the given index
    INDEX current_index = 0;
    LIST_NODE *current_node = linked_list->first_node;
    while (current_index != index) {
        current_node = current_node->next_node;
        current_index++;
    }
    // return the pointer to the data contained in the node
    return current_node->data_pointer;
}

void ll_swap(LIST *linked_list, INDEX index_1, INDEX index_2) {
    // exit with a failure code if either index is out of range
    INDEX list_length = ll_length(linked_list);
    if (index_1 >= list_length) {
        exit(EXIT_FAILURE);
    }
    if (index_2 >= list_length) {
        exit(EXIT_FAILURE);
    }
    // swap the data contained in the nodes
    void *data_buffer = malloc(linked_list->data_size);
    // memcpy(destination, source, size)
    memcpy(data_buffer, ll_get(linked_list, index_1), linked_list->data_size);
    memcpy(ll_get(linked_list, index_1), ll_get(linked_list, index_2), linked_list->data_size);
    memcpy(ll_get(linked_list, index_2), data_buffer, linked_list->data_size);
    free(data_buffer);
}

void ll_remove(LIST *linked_list, INDEX index) {
    // exit with a failure code if the index is out of range
    if (index >= ll_length(linked_list)) {
        exit(EXIT_FAILURE);
    }
    LIST_NODE *node_to_remove;
    if (index == 0) {
        // set the list first node as the second node (possibly NULL)
        node_to_remove = linked_list->first_node;
        linked_list->first_node = node_to_remove->next_node;
    }
    else {
        // get the node before and the node after (possibly NULL) the node to remove
        LIST_NODE *previous_node = linked_list->first_node;
        INDEX current_index = 0;
        while (current_index != index - 1) {
            previous_node = previous_node->next_node;
            current_index++;
        }
        node_to_remove = previous_node->next_node;
        LIST_NODE *next_node = node_to_remove->next_node;
        // link the previous and the next nodes together
        previous_node->next_node = next_node;
    }
    // free the node data
    free(node_to_remove->data_pointer);
    // free the removed node
    free(node_to_remove);
}

void ll_free(LIST *linked_list) {
    LIST_NODE *current_node = linked_list->first_node, *next_node;
    // free every node of the list
    while (current_node) {
        next_node = current_node->next_node;
        free(current_node->data_pointer);
        free(current_node);
        current_node = next_node;
    }
    // set the first node to NULL
    linked_list->first_node = NULL;
}

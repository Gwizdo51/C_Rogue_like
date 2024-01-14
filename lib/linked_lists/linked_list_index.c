#include "linked_list_index.h"


// node structure definition
typedef struct _LIST_NODE_INDEX {
    INDEX value;
    LIST_NODE_INDEX* next_node;
} LIST_NODE_INDEX;


LIST_INDEX lli_create_empty_list() {
    LIST_INDEX linked_list = {.first_node = NULL};
    return linked_list;
}


INDEX lli_length(LIST_INDEX linked_list) {
    INDEX list_length = 0;
    LIST_NODE_INDEX* current_node = linked_list.first_node;
    while (current_node) {
        list_length++;
        current_node = current_node->next_node;
    }
    return list_length;
}


void lli_append(LIST_INDEX* linked_list, INDEX value) {
    if (!linked_list->first_node) {
        // if the list is empty, return a new link with the provided value
        linked_list->first_node = (LIST_NODE_INDEX*) malloc(sizeof(LIST_NODE_INDEX));
        linked_list->first_node->value = value;
        linked_list->first_node->next_node = NULL;
    }
    else {
        // otherwise, look for the last link of the list
        LIST_NODE_INDEX* last_node = linked_list->first_node;
        while (last_node->next_node) {
            last_node = last_node->next_node;
        }
        // add a new link with the provided value
        last_node->next_node = (LIST_NODE_INDEX*) malloc(sizeof(LIST_NODE_INDEX));
        last_node->next_node->value = value;
        last_node->next_node->next_node = NULL;
    }
}


INDEX lli_get_value(LIST_INDEX linked_list, INDEX index) {
    if (index >= lli_length(linked_list)) {
        // raise_error("get_node", "index \"%u\" out of range", index);
        exit(EXIT_FAILURE);
    }
    INDEX current_index = 0;
    LIST_NODE_INDEX* current_node = linked_list.first_node;
    while (current_index != index) {
        current_node = current_node->next_node;
        current_index++;
    }
    return current_node->value;
}


void lli_remove_by_index(LIST_INDEX* linked_list, INDEX index) {
    if (index >= lli_length(*linked_list)) {
        // raise_error("remove_index", "the index \"%u\" is out of range\n", index);
        exit(EXIT_FAILURE);
    }
    LIST_NODE_INDEX* node_to_remove;
    if (index == 0) {
        node_to_remove = linked_list->first_node;
        linked_list->first_node = node_to_remove->next_node;
    }
    else {
        // to remove any other link, get the link itself, the one before and after it
        LIST_NODE_INDEX* previous_node = linked_list->first_node;
        INDEX current_index = 0;
        while (current_index != index - 1) {
            previous_node = previous_node->next_node;
            current_index++;
        }
        node_to_remove = previous_node->next_node;
        LIST_NODE_INDEX* next_node = node_to_remove->next_node;
        // link the preceding and the next link together
        previous_node->next_node = next_node;
    }
    // free the removed link
    free(node_to_remove);
}


void lli_erase_content(LIST_INDEX* linked_list) {
    LIST_NODE_INDEX* current_node = linked_list->first_node, *next_node;
    while (current_node) {
        next_node = current_node->next_node;
        free(current_node);
        current_node = next_node;
    }
    linked_list->first_node = NULL;
}

#include "linked_list_room.h"


// node structure definition
typedef struct _LIST_NODE_ROOM {
    ROOM room;
    LIST_NODE_ROOM* next_node;
} LIST_NODE_ROOM;


LIST_ROOM llr_create_empty_list() {
    LIST_ROOM linked_list = {.first_node = NULL};
    return linked_list;
}


INDEX llr_length(LIST_ROOM linked_list) {
    INDEX list_length = 0;
    LIST_NODE_ROOM* current_node = linked_list.first_node;
    while (current_node) {
        list_length++;
        current_node = current_node->next_node;
    }
    return list_length;
}


void llr_append(LIST_ROOM* linked_list, ROOM room) {
    if (!linked_list->first_node) {
        // if the list is empty, return a new link with the provided value
        linked_list->first_node = (LIST_NODE_ROOM*) malloc(sizeof(LIST_NODE_ROOM));
        linked_list->first_node->room = room;
        linked_list->first_node->next_node = NULL;
    }
    else {
        // otherwise, look for the last link of the list
        LIST_NODE_ROOM* last_node = linked_list->first_node;
        while (last_node->next_node) {
            last_node = last_node->next_node;
        }
        // add a new link with the provided value
        last_node->next_node = (LIST_NODE_ROOM*) malloc(sizeof(LIST_NODE_ROOM));
        last_node->next_node->room = room;
        last_node->next_node->next_node = NULL;
    }
}


ROOM* llr_get_value_pointer(LIST_ROOM linked_list, INDEX index) {
    if (index >= llr_length(linked_list)) {
        // raise_error("get_node", "index \"%u\" out of range", index);
        exit(EXIT_FAILURE);
    }
    INDEX current_index = 0;
    LIST_NODE_ROOM* current_node = linked_list.first_node;
    while (current_index != index) {
        current_node = current_node->next_node;
        current_index++;
    }
    return &(current_node->room);
}


void llr_erase_content(LIST_ROOM* linked_list) {
    LIST_NODE_ROOM* current_node = linked_list->first_node, *next_node;
    while (current_node) {
        next_node = current_node->next_node;
        free(current_node);
        current_node = next_node;
    }
    linked_list->first_node = NULL;
}

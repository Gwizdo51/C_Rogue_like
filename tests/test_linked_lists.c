// #include "..\lib\linked_lists\linked_list_index.h"
#include "..\lib\linked_list.h"


int main() {
    // LIST_INDEX index_list;
    // LIST_ROOM room_list;
    LIST int_list, coord_list;
    int my_int;
    // void* data_pointer;
    ROOM room_to_append;
    COORD coordinates;
    INDEX index;

    /*
    printf("LIST_INDEX tests\n\n");

    printf("Create an empty list\n");
    index_list = lli_create_empty_list();
    printf("len(index_list) = %u\n", lli_length(index_list));
    printf("\n");

    printf("Add indices to the list\n");
    index_to_append = 5;
    lli_append(&index_list, index_to_append);
    index_to_append = 10;
    lli_append(&index_list, index_to_append);
    index_to_append = 2;
    lli_append(&index_list, index_to_append);
    printf("len(index_list) = %u\n", lli_length(index_list));
    printf("\n");

    printf("Get the element at a given index\n");
    index = 1;
    printf("index_list[%u] = %u\n", index, lli_get_value(index_list, index));
    printf("\n");

    printf("Remove an element from the list\n");
    index = 1;
    lli_remove_by_index(&index_list, index);
    index = 0;
    printf("index_list[%u] = %u\n", index, lli_get_value(index_list, index));
    printf("len(index_list) = %u\n", lli_length(index_list));
    printf("\n");

    printf("Erase the contents of the list\n");
    lli_erase_content(&index_list);
    printf("len(index_list) = %u\n", lli_length(index_list));
    printf("\n");

    printf("\nLIST_ROOM tests\n\n");

    printf("Create an empty list\n");
    room_list = llr_create_empty_list();
    printf("len(room_list) = %u\n", llr_length(room_list));
    printf("\n");

    printf("Add rooms to the list\n");
    room_origin.X = 1;
    room_origin.Y = 2;
    room_to_append.origin = room_origin;
    room_to_append.width = 5;
    room_to_append.height = 2;
    room_to_append.added_to_MST = FALSE;
    room_to_append.placed_on_map = FALSE;
    llr_append(&room_list, room_to_append);
    room_origin.X = 10;
    room_origin.Y = 12;
    room_to_append.origin = room_origin;
    room_to_append.width = 3;
    room_to_append.height = 4;
    room_to_append.added_to_MST = FALSE;
    room_to_append.placed_on_map = TRUE;
    llr_append(&room_list, room_to_append);
    room_origin.X = 20;
    room_origin.Y = 25;
    room_to_append.origin = room_origin;
    room_to_append.width = 8;
    room_to_append.height = 10;
    room_to_append.added_to_MST = TRUE;
    room_to_append.placed_on_map = TRUE;
    llr_append(&room_list, room_to_append);
    printf("len(room_list) = %u\n", llr_length(room_list));
    printf("\n");
    // */

    printf("LIST tests\n\n");

    printf("Create an empty list of integers\n");
    int_list = ll_create(sizeof(int));
    printf("len(int_list) = %u\n", ll_length(&int_list));
    printf("\n");

    printf("Add some integers to the list\n");
    my_int = 10;
    ll_append(&int_list, &my_int);
    my_int = 5;
    ll_append(&int_list, &my_int);
    my_int = -17;
    ll_append(&int_list, &my_int);
    printf("len(int_list) = %u\n", ll_length(&int_list));
    printf("\n");

    printf("Get an int at a given index\n");
    index = 0;
    // data_pointer = ll_get(int_list, index);
    // my_int = *((int*) data_pointer);
    my_int = *(int*) ll_get(&int_list, index);
    printf("int_list[%u] = %d\n", index, my_int);
    index = 1;
    my_int = *(int*) ll_get(&int_list, index);
    printf("int_list[%u] = %d\n", index, my_int);
    index = 2;
    my_int = *(int*) ll_get(&int_list, index);
    printf("int_list[%u] = %d\n", index, my_int);
    printf("\n");

    printf("Swap two nodes\n");
    ll_swap(&int_list, 1, 2);
    index = 0;
    my_int = *(int*) ll_get(&int_list, index);
    printf("int_list[%u] = %d\n", index, my_int);
    index = 1;
    my_int = *(int*) ll_get(&int_list, index);
    printf("int_list[%u] = %d\n", index, my_int);
    index = 2;
    my_int = *(int*) ll_get(&int_list, index);
    printf("int_list[%u] = %d\n", index, my_int);
    printf("\n");

    printf("Remove an int from the list\n");
    index = 2;
    ll_remove(&int_list, index);
    printf("len(int_list) = %u\n", ll_length(&int_list));
    index = 0;
    my_int = *(int*) ll_get(&int_list, index);
    printf("int_list[%u] = %d\n", index, my_int);
    index = 1;
    my_int = *(int*) ll_get(&int_list, index);
    printf("int_list[%u] = %d\n", index, my_int);
    printf("\n");

    printf("Erase the list contents\n");
    ll_free(&int_list);
    printf("len(index_list) = %u\n", ll_length(&int_list));
    printf("\n");

    printf("\nCreate an empty list of cordinates (COORD)\n");
    coord_list = ll_create(sizeof(COORD));
    printf("len(coord_list) = %u\n", ll_length(&coord_list));
    printf("\n");

    printf("Add some coords to the list\n");
    coordinates.X = 0;
    coordinates.Y = 0;
    ll_append(&coord_list, &coordinates);
    coordinates.X = 5;
    coordinates.Y = -10;
    ll_append(&coord_list, &coordinates);
    coordinates.X = 50;
    coordinates.Y = 32;
    ll_append(&coord_list, &coordinates);
    printf("len(coord_list) = %u\n", ll_length(&coord_list));
    printf("\n");

    printf("Get a coord at a given index\n");
    index = 0;
    coordinates = *(COORD*) ll_get(&coord_list, index);
    printf("coord_list[%u].X = %d\n", index, coordinates.X);
    printf("coord_list[%u].Y = %d\n", index, coordinates.Y);
    index = 1;
    coordinates = *(COORD*) ll_get(&coord_list, index);
    printf("coord_list[%u].X = %d\n", index, coordinates.X);
    printf("coord_list[%u].Y = %d\n", index, coordinates.Y);
    index = 2;
    coordinates = *(COORD*) ll_get(&coord_list, index);
    printf("coord_list[%u].X = %d\n", index, coordinates.X);
    printf("coord_list[%u].Y = %d\n", index, coordinates.Y);
    printf("\n");

    printf("Swap two nodes\n");
    ll_swap(&coord_list, 2, 2);
    index = 0;
    coordinates = *(COORD*) ll_get(&coord_list, index);
    printf("coord_list[%u].X = %d\n", index, coordinates.X);
    printf("coord_list[%u].Y = %d\n", index, coordinates.Y);
    index = 1;
    coordinates = *(COORD*) ll_get(&coord_list, index);
    printf("coord_list[%u].X = %d\n", index, coordinates.X);
    printf("coord_list[%u].Y = %d\n", index, coordinates.Y);
    index = 2;
    coordinates = *(COORD*) ll_get(&coord_list, index);
    printf("coord_list[%u].X = %d\n", index, coordinates.X);
    printf("coord_list[%u].Y = %d\n", index, coordinates.Y);
    printf("\n");

    printf("Remove a coord from the list\n");
    index = 0;
    ll_remove(&coord_list, index);
    printf("len(coordinates) = %u\n", ll_length(&coord_list));
    index = 0;
    coordinates = *(COORD*) ll_get(&coord_list, index);
    printf("coord_list[%u].X = %d\n", index, coordinates.X);
    printf("coord_list[%u].Y = %d\n", index, coordinates.Y);
    index = 1;
    coordinates = *(COORD*) ll_get(&coord_list, index);
    printf("coord_list[%u].X = %d\n", index, coordinates.X);
    printf("coord_list[%u].Y = %d\n", index, coordinates.Y);
    printf("\n");

    printf("Erase the list contents\n");
    ll_free(&coord_list);
    printf("len(coord_list) = %u\n", ll_length(&coord_list));
    printf("\n");

    return EXIT_SUCCESS;
}

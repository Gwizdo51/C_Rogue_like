#include "..\lib\types.h"
#include "..\lib\display.h"
#include "..\lib\dungeon.h"
#include "..\lib\utils.h"
// #include "..\src\main.h"
#include "..\lib\game.h"


void test_rand() {
    short i;
    printf("time : %ld\n", time(NULL));
    // set a random seed
    srand((unsigned int) time(NULL));
    // generate some random numbers to break the patterns
    for (i = 0; i < 100; i++) {
        rand();
    }
    printf("random number generated: %d\n", rand());
    printf("random number generated: %d\n", rand());
    printf("random number generated: %d\n", rand());
    printf("random number generated: %d\n", rand());
    printf("random number generated: %d\n", rand());
}


void test_unsigned_char() {
    unsigned char uchar_test;
    char char_test;
    // char_test = -1;
    char_test = 255;
    printf("char_test = %d\n", char_test);
    uchar_test = -1;
    printf("uchar_test = %d\n", uchar_test);
}


void test_modulo() {
    int a = 10;
    printf("%d %% 2 = %d\n", a, a % 2);
}


void test_random_numbers() {
    INDEX min = 3, max = 15;
    init_rand();
    printf("random odd between included boundaries\n");
    printf("%u\n", rand_odd_range(min, max));
    printf("%u\n", rand_odd_range(min, max));
    printf("%u\n", rand_odd_range(min, max));
    printf("%u\n", rand_odd_range(min, max));
    printf("%u\n", rand_odd_range(min, max));

    printf("random number between included boundaries\n");
    printf("%u\n", rand_range(min, max));
    printf("%u\n", rand_range(min, max));
    printf("%u\n", rand_range(min, max));
    printf("%u\n", rand_range(min, max));
    printf("%u\n", rand_range(min, max));
}


void test_rectangle_intersection() {
    RECTANGLE rect_1 = {
        .origin.X = 1,
        .origin.Y = 6,
        .width = 6,
        .height = 3
    }, rect_2 = {
        .origin.X = 6,
        .origin.Y = 3,
        .width = 3,
        .height = 3
    };
    printf("X = %d, Y = %d, width = %d, height = %d\n", rect_1.origin.X, rect_1.origin.Y, rect_1.width, rect_1.height);
    printf("X = %d, Y = %d, width = %d, height = %d\n", rect_2.origin.X, rect_2.origin.Y, rect_2.width, rect_2.height);
    if (rect_intersect(rect_1, rect_2)) {
        printf("the rectangles intersect\n");
    }
    else {
        printf("the rectangles don't intersect\n");
    }
}


void test_sort_room_list() {
    LIST list_rooms = ll_create(sizeof(ROOM));
    ROOM room_buffer;
    INDEX i;
    // short surface_print;
    // add rooms to the list
    room_buffer.rectangle.width = 5;
    room_buffer.rectangle.height = 3;
    room_buffer.rectangle.surface = room_buffer.rectangle.width * room_buffer.rectangle.height;
    ll_append(&list_rooms, &room_buffer);
    room_buffer.rectangle.width = 3;
    room_buffer.rectangle.height = 3;
    room_buffer.rectangle.surface = room_buffer.rectangle.width * room_buffer.rectangle.height;
    ll_append(&list_rooms, &room_buffer);
    room_buffer.rectangle.width = 9;
    room_buffer.rectangle.height = 3;
    room_buffer.rectangle.surface = room_buffer.rectangle.width * room_buffer.rectangle.height;
    ll_append(&list_rooms, &room_buffer);
    room_buffer.rectangle.width = 7;
    room_buffer.rectangle.height = 3;
    room_buffer.rectangle.surface = room_buffer.rectangle.width * room_buffer.rectangle.height;
    ll_append(&list_rooms, &room_buffer);
    printf("before sorting:\n");
    for (i = 0; i < ll_length(&list_rooms); i++) {
        // surface_print = (*(ROOM*) ll_get(list_rooms, i)).rectangle.surface;
        printf("list_rooms[%u].rectangle.surface = %d\n", i, (*(ROOM*) ll_get(&list_rooms, i)).rectangle.surface);
    }
    printf("\n");
    // sort the list by size
    sort_rooms_by_size(&list_rooms);
    printf("after sorting:\n");
    for (i = 0; i < ll_length(&list_rooms); i++) {
        // surface_print = (*(ROOM*) ll_get(list_rooms, i)).rectangle.surface;
        printf("list_rooms[%u].rectangle.surface = %d\n", i, (*(ROOM*) ll_get(&list_rooms, i)).rectangle.surface);
    }
    printf("\n");
    ll_free(&list_rooms);
}


void test_room_center_distance() {
    ROOM room_1 = {
        .rectangle.origin.X = 5,
        .rectangle.origin.Y = 5,
        .rectangle.width = 5,
        .rectangle.height = 5
    };
    ROOM room_2 = {
        .rectangle.origin.X = 11,
        .rectangle.origin.Y = 5,
        .rectangle.width = 3,
        .rectangle.height = 5
    };
    COORD room_center;
    room_center = get_room_center(&room_1);
    printf("room_1 center:\n");
    printf("\tX = %d\n", room_center.X);
    printf("\tY = %d\n", room_center.Y);
    room_center = get_room_center(&room_2);
    printf("room_2 center:\n");
    printf("\tX = %d\n", room_center.X);
    printf("\tY = %d\n", room_center.Y);
    printf("room distance = %.2f\n", room_distance(&room_1, &room_2));
}


void test_rooms_added_to_mst() {
    LIST list_rooms = ll_create(sizeof(ROOM));
    ROOM room;
    // room.added_to_MST = TRUE;
    room.flags = 0;
    room.flags |= FLAG_ROOM_ADDED_TO_MST;
    ll_append(&list_rooms, &room);
    // room.added_to_MST = TRUE;
    room.flags = 0;
    room.flags |= FLAG_ROOM_ADDED_TO_MST;
    ll_append(&list_rooms, &room);
    if (all_rooms_added_to_mst(&list_rooms)) {
        printf("all rooms added\n");
    }
    else {
        printf("not all rooms added\n");
    }
    ll_free(&list_rooms);
}


void test_room_walls_characters() {
    char char_to_display;
    int counter;
    // door
    char_to_display = 206;
    // char_to_display = CHAR_
    printf("door: %c\n", char_to_display);
    // vertical wall
    char_to_display = 186;
    printf("vertical wall: %c\n", char_to_display);
    // horizontal wall
    char_to_display = 205;
    printf("horizontal wall: %c\n", char_to_display);
    // top left corner
    char_to_display = 201;
    printf("top left corner: %c\n", char_to_display);
    // top right corner
    char_to_display = 187;
    printf("top right corner: %c\n", char_to_display);
    // bottom left corner
    char_to_display = 200;
    printf("bottom left corner: %c\n", char_to_display);
    // bottom right corner
    char_to_display = 188;
    printf("bottom right corner: %c\n", char_to_display);
    // horizontal with top wall
    char_to_display = 202;
    printf("horizontal with top wall: %c\n", char_to_display);
    // horizontal with bottom wall
    char_to_display = 203;
    printf("horizontal with bottom wall: %c\n", char_to_display);
    // vertical with left wall
    char_to_display = 185;
    printf("vertical with left wall: %c\n", char_to_display);
    // vertical with right wall
    char_to_display = 204;
    printf("vertical with right wall: %c\n", char_to_display);
    // tests corridor chars
    char_to_display = 176;
    printf("test #0: %c\n", char_to_display);
    char_to_display = 177;
    printf("test #1: %c\n", char_to_display);
    char_to_display = 178;
    printf("test #2: %c\n", char_to_display);
    printf("\n");
    // cmd prompt code page: 850
    // ('chcp' in cmd)
    printf("all chars:\n");
    for (counter = 0; counter < 256; counter++) {
        printf("char #%d: %c\n", counter, (char) counter);
    }
    printf("\n");
    system("pause");
}


void test_color() {
    unsigned char foreground, background;
    // const HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("default text\n\n");
    // for (k = 0; k < 256; k++) {
    //     SetConsoleTextAttribute(hStdout, k);
    //     printf("%3u: super exemple\n", k);
    // }
    for (background = 0; background < 16; background++) {
        for (foreground = 0; foreground < 16; foreground++) {
            set_color(foreground, background);
            printf("%3u: super exemple\n", foreground + 16 * background);
        }
    }
    printf("\n");
    reset_color();
    system("pause");
}

/*
remove a flag:
flags = 1011
flag_to_remove = 0010
~flag_to_remove = 1101
flags &= ~flags_to_remove <-> flags = 1011 & 1101 = 1001

check if a flag is off:
flags = 0101
flag = 0010
*/
void test_flags() {
    unsigned int flag_0 = 1,
        flag_1 = 2,
        flag_2 = 4,
        flag_3 = 8,
        // all_flags_on = flag_0 | flag_1 | flag_2 | flag_3,
        // all_flags_on = ~0,
        flags = 0;
    printf("turn on bit 0, 1 and 3\n");
    flags |= flag_0 | flag_1 | flag_3;
    printf("flags = %u\n", flags);
    flags |= flag_3;
    printf("flags = %u\n", flags);
    printf("check if bits are ON\n");
    if (flags & flag_0) {
        printf("bit 0 is ON\n");
    }
    else {
        printf("bit 0 is OFF\n");
    }
    if (flags & flag_1) {
        printf("bit 1 is ON\n");
    }
    else {
        printf("bit 1 is OFF\n");
    }
    if (flags & flag_2) {
        printf("bit 2 is ON\n");
    }
    else {
        printf("bit 2 is OFF\n");
    }
    if (flags & flag_3) {
        printf("bit 3 is ON\n");
    }
    else {
        printf("bit 3 is OFF\n");
    }
    printf("flags = %u\n", flags);
    printf("turn off bit 1\n");
    // flags &= all_flags_on - flag_1;
    flags &= ~flag_1;
    printf("flags = %u\n", flags);
    flags &= ~flag_1;
    printf("flags = %u\n", flags);
    if (flags & flag_0) {
        printf("bit 0 is ON\n");
    }
    else {
        printf("bit 0 is OFF\n");
    }
    if (flags & flag_1) {
        printf("bit 1 is ON\n");
    }
    else {
        printf("bit 1 is OFF\n");
    }
    if (flags & flag_2) {
        printf("bit 2 is ON\n");
    }
    else {
        printf("bit 2 is OFF\n");
    }
    if (flags & flag_3) {
        printf("bit 3 is ON\n");
    }
    else {
        printf("bit 3 is OFF\n");
    }
}


void test_sizeof() {
    int int_test = 4;
    int *int_pointer = &int_test;
    short short_test = 8;
    short *short_pointer = &short_test;
    GRAPH_EDGE graph_edge_test;
    GRAPH_EDGE *graph_edge_pointer = &graph_edge_test;
    printf("sizeof(int) = %u\n", sizeof (int));
    printf("sizeof(int_test) = %u\n", sizeof int_test);
    printf("sizeof(int*) = %u\n", sizeof (int*));
    printf("sizeof(int_pointer) = %u\n", sizeof int_pointer);
    printf("sizeof(short) = %u\n", sizeof(short));
    printf("sizeof(short_test) = %u\n", sizeof(short_test));
    printf("sizeof(short*) = %u\n", sizeof(short*));
    printf("sizeof(short_pointer) = %u\n", sizeof(short_pointer));
    printf("sizeof(GRAPH_EDGE) = %u\n", sizeof(GRAPH_EDGE));
    printf("sizeof(graph_edge_test) = %u\n", sizeof(graph_edge_test));
    printf("sizeof(GRAPH_EDGE*) = %u\n", sizeof(GRAPH_EDGE*));
    printf("sizeof(graph_edge_pointer) = %u\n", sizeof(graph_edge_pointer));
    printf("sizeof (unsigned char*) * 10 = %u\n", sizeof (unsigned char*) * 10);
    printf("10 * sizeof (unsigned char*) = %u\n", 10 * sizeof (unsigned char*));
}


void test_pointer_value() {
    int *int_pointer = NULL;
    if (int_pointer) {
        printf("int_pointer is not NULL\n");
    }
    else {
        printf("int_pointer is NULL\n");
    }
}


void test_clear_map() {
    GAME game_state;
    unsigned short X, Y;
    // THING *current_thing_pointer;
    init_game_state(&game_state);
    // add random things to the map
    // *(*(game_state.map_things + 3) + 2) = (THING*) malloc(sizeof(THING));
    // (*(*(game_state.map_things + 3) + 2))->position.X = 2;
    // (*(*(game_state.map_things + 3) + 2))->position.Y = 3;
    // (*(*(game_state.map_things + 3) + 2))->type = 0;
    // for (Y = 0; Y < MAP_HEIGHT; Y++) {
    //     for (X = 0; X < MAP_WIDTH; X++) {
    //         current_thing_pointer = *(*(game_state.map_things + Y) + X);
    //         if (current_thing_pointer) {
    //             printf("thing type %u found at X = %u, Y = %u\n", current_thing_pointer->type, X, Y);
    //         }
    //     }
    // }
    clear_map(&game_state);
    *(*(game_state.map_things + 3) + 2) = THING_STAIRS;
    for (Y = 0; Y < MAP_HEIGHT; Y++) {
        for (X = 0; X < MAP_WIDTH; X++) {
            if (*(*(game_state.map_things + Y) + X) != THING_NONE) {
                printf("thing type %u found at X = %u, Y = %u\n", *(*(game_state.map_things + Y) + X), X, Y);
            }
        }
    }
    clear_map(&game_state);
    for (Y = 0; Y < MAP_HEIGHT; Y++) {
        for (X = 0; X < MAP_WIDTH; X++) {
            if (*(*(game_state.map_things + Y) + X) != THING_NONE) {
                printf("thing type %u found at X = %u, Y = %u\n", *(*(game_state.map_things + Y) + X), X, Y);
            }
        }
    }
}


void test_highest_value() {
    char s_char = ~0;
    unsigned char u_char = ~0;
    unsigned short u_short = ~0;
    unsigned int u_int = ~0;
    printf("s_char = %d\n", s_char);
    printf("u_char = %u\n", u_char);
    printf("u_short = %u\n", u_short);
    printf("u_int = %u\n", u_int);
}


void test_global_variables() {
    GAME game_state;
    init_game_state(&game_state);
    if (fow_toggle) {
        printf("fow is ON\n");
    }
    else {
        printf("fow is OFF\n");
    }
}


void test_char_equality() {
    char char_test;
    char_test = CHAR_HORIZONTAL_WALL;
    if (char_test == (char) CHAR_HORIZONTAL_WALL) {
        printf("can compare\n");
    }
    else {
        printf("can't compare\n");
    }
}


void test_conio() {
    // for special keys, _getch must be called twice:
    // once for the "224" special key code
    // and another for the key code associated
    // ENTER: \r
    // ESCAPE: \e
    // TAP: \t
    int key, key_code;
    key = _getch();
    printf("key = %d\n", key);
    if (key == 0 || key == 224) {
        key_code = _getch();
        printf("key code = %d\n", key_code);
    }
    if (key == '\t') {
        printf("TAB pressed\n");
    }
    system("pause");
}


void test_malloc() {
    unsigned int *map_1;
    unsigned short *map_2;
    INDEX i;
    // malloc the maps
    map_1 = (unsigned int*) malloc(10 * sizeof (unsigned int));
    map_2 = (unsigned short*) malloc(sizeof (unsigned short) * 10);
    for (i = 0; i < 10; i++) {
        *(map_1 + i) = i;
        *(map_2 + i) = 10 - i;
    }
    for (i = 0; i < 10; i++) {
        printf("map_1[%u] = %u\n", i, *(map_1 + i));
        printf("map_2[%u] = %u\n", i, *(map_2 + i));
    }
}


void test_calloc() {
    unsigned int *map_1;
    INDEX i;
    // malloc the maps
    // map_1 = (unsigned int*) malloc(10 * sizeof (unsigned int));
    map_1 = (unsigned int*) calloc(10, sizeof (unsigned int));
    // for (i = 0; i < 10; i++) {
    //     *(map_1 + i) = i;
    // }
    for (i = 0; i < 10; i++) {
        printf("map_1[%u] = %u\n", i, *(map_1 + i));
    }
}


int main() {
    // unsigned char **map;
    init_rand();

    // test_rand();
    // test_unsigned_char();
    // test_modulo();
    // test_random_numbers();
    // test_rectangle_intersection();
    // test_sort_room_list();
    // test_room_center_distance();
    // test_rooms_added_to_mst();
    // test_room_walls_characters();
    // test_color();
    // test_flags();
    // test_sizeof();
    // test_pointer_value();
    // test_clear_map();
    // test_highest_value();
    // test_global_variables();
    // test_char_equality();
    // test_conio();
    // test_malloc();
    test_calloc();

    // generate_dungeon(map);

    return EXIT_SUCCESS;
}

#ifndef _HEADER_DUNGEON
#define _HEADER_DUNGEON


#include "types.h"
#include "display.h"
#include "linked_list.h"
#include "utils.h"


// room parameters
#define MIN_ROOMS 3
#define MAX_ROOMS 9
#define ROOM_MIN_WIDTH 3
#define ROOM_MAX_WIDTH 19
#define ROOM_MIN_HEIGHT 3
#define ROOM_MAX_HEIGHT 7

// room flags
#define FLAG_ROOM_PLACED_ON_MAP (1 << 0)
#define FLAG_ROOM_ADDED_TO_MST (1 << 1)
#define FLAG_ROOM_SPAWN_PLAYER (1 << 2)
#define FLAG_ROOM_SPAWN_STAIRS (1 << 3)
// #define FLAG_ROOM_DISCOVERED (1 << 4)
// #define FLAG_ROOM_VISIBLE (1 << 5)

// spawn parameters
#define CHANCE_0_GOLD 20
#define CHANCE_1_GOLD 60

// map tiles
#define TILE_FILL 0
#define TILE_ROOM_FLOOR 1
#define TILE_CORRIDOR_FLOOR 2
#define TILE_ROOM_WALL 3
#define TILE_DOOR 4

// things
#define THING_NONE 0
#define THING_STAIRS 1
#define THING_GOLD 2


// functions
void generate_dungeon(GAME *game_state);
void clear_map(GAME *game_state);
void generate_rooms(LIST *list_rooms);
void sort_rooms_by_size(LIST *list_rooms);
void place_rooms(LIST *list_rooms);
BOOL rect_intersect(RECTANGLE rect_1, RECTANGLE rect_2);
void remove_not_placed_rooms(LIST *list_rooms);
void generate_corridors(LIST *list_rooms, LIST *list_graph_edges);
void generate_graph(LIST *list_rooms, LIST *list_graph_edges);
float room_distance(ROOM *room_1, ROOM *room_2);
COORD get_room_center(ROOM *room);
void generate_mst(LIST *list_rooms, LIST *list_graph_edges);
BOOL all_rooms_added_to_mst(LIST *list_rooms);
void add_random_corridors(LIST *list_graph_edges);
void draw_dungeon_on_map(LIST *list_rooms, LIST *list_graph_edges, unsigned char **map);
COORD get_room_center_snapped(ROOM *room);
void generate_things(LIST *list_rooms, GAME *game_state);


#endif

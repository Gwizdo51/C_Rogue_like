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

/*
Creates a new dungeon.

PARAMETERS
----------
GAME *game_state
    The pointer to the current game state.
*/
void generate_dungeon(GAME *game_state);

/*
Clears the dungeon map, the map of things and the fog of war map.

PARAMETERS
----------
GAME *game_state
    The pointer to the current game state.
*/
void clear_map(GAME *game_state);

/*
Places a random number of rooms with random sizes on the map.
The generated rooms will not intersect.

PARAMETERS
----------
LIST *list_rooms
    The pointer to the list of rooms on the dungeon map.
*/
void generate_rooms(LIST *list_rooms);

/*
Sorts the list of rooms by room size.

PARAMETERS
----------
LIST *list_rooms
    The pointer to the list of rooms on the dungeon map.
*/
void sort_rooms_by_size(LIST *list_rooms);

/*
Places the generated rooms on the map. The rooms will be placed
in a random location where they won't collide with other rooms.

PARAMETERS
----------
LIST *list_rooms
    The pointer to the list of rooms on the dungeon map.
*/
void place_rooms(LIST *list_rooms);

/*
Returns whether a rectangle intersects with another rectangle.

PARAMETERS
----------
RECTANGLE rect_1
    The first rectangle.
RECTANGLE rect_2
    The second rectangle.

RETURNS
-------
BOOL
    Whether the rectangles intersect.
*/
BOOL rect_intersect(RECTANGLE rect_1, RECTANGLE rect_2);

/*
Removes from the list of rooms all the rooms that were not placed on the map.

PARAMETERS
----------
LIST *list_rooms
    The pointer to the list of rooms on the dungeon map.
*/
void remove_not_placed_rooms(LIST *list_rooms);

/*
Connects the generated rooms with corridors. The rooms are connected according
to the minimum spanning tree between the room centers, using Prim's algorithm.
Some more corridors are randomly added to increase the randomness of the map.

PARAMETERS
----------
LIST *list_rooms
    The pointer to the list of rooms on the dungeon map (the graph vertices).
LIST *list_graph_edges
    The pointer to the list of all the possible corridors (the graph edges).
*/
void generate_corridors(LIST *list_rooms, LIST *list_graph_edges);

/*
Generates all the possible corridors between the rooms.

PARAMETERS
----------
LIST *list_rooms
    The pointer to the list of rooms on the dungeon map (the graph vertices).
LIST *list_graph_edges
    The pointer to the list of all the possible corridors (the graph edges).
*/
void generate_graph(LIST *list_rooms, LIST *list_graph_edges);

/*
Returns the distance between the centers of two rooms.

PARAMETERS
----------
ROOM *room_1
    The pointer to the first room.
ROOM *room_2
    The pointer to the second room.

RETURNS
-------
float
    The distance between the room centers.
*/
float room_distance(ROOM *room_1, ROOM *room_2);

/*
Returns the coordinates of the center of a room.

PARAMETERS
----------
ROOM *room
    The pointer to the room of which to get the center.

RETURNS
-------
COORD
    The coordinates of the room center.
*/
COORD get_room_center(ROOM *room);

/*
Applies Prim's algorithm to the graph generated. All the graph edges
belonging to the MST are flagged as being corridors.

PARAMETERS
----------
LIST *list_rooms
    The pointer to the list of rooms on the dungeon map (the graph vertices).
LIST *list_graph_edges
    The pointer to the list of all the possible corridors (the graph edges).
*/
void generate_mst(LIST *list_rooms, LIST *list_graph_edges);

/*
Returns whether every room has been connected via the MST.

PARAMETERS
----------
LIST *list_rooms
    The pointer to the list of rooms on the dungeon map.

RETURNS
-------
BOOL
    TRUE if every room has been added to the MST, FALSE otherwise.
*/
BOOL all_rooms_added_to_mst(LIST *list_rooms);

/*
Adds a random number of additional corridors to the map.

PARAMETERS
----------
LIST *list_graph_edges
    The pointer to the list of all the possible corridors.
*/
void add_random_corridors(LIST *list_graph_edges);

/*
Draws the rooms and the corridors on the dungeon map.

PARAMETERS
----------
LIST *list_rooms
    The pointer to the list of rooms on the dungeon map.
LIST *list_graph_edges
    The pointer to the list of all the possible corridors.
unsigned char **map
    The dungeon map.
*/
void draw_dungeon_on_map(LIST *list_rooms, LIST *list_graph_edges, unsigned char **map);

/*
Returns the center of a room, randomly snapped on the corridors grid
(the corridor grid is made of all the points of the map with odd coordinates ;
the corridors are drawn by moving moving from one point of the grid to the next one ;
this ensures the corridors align nicely with the rooms).

PARAMETERS
----------
ROOM *room
    The pointer of the room from which to get the "snapped" center.

RETURNS
-------
COORD
    A "snapped" version of the center of the room.
*/
COORD get_room_center_snapped(ROOM *room);

/*
Generates the player, the stairs and the gold in the dungeon.

PARAMETERS
----------
GAME *game_state
    The pointer to the current game state.
*/
void generate_things(GAME *game_state);


#endif

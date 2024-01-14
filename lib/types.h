#ifndef _HEADER_TYPES
#define _HEADER_TYPES


// standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <math.h>


// types definition

// index type for linked lists
typedef unsigned int INDEX;

// generic linked lists
typedef struct _LIST_NODE LIST_NODE;
typedef struct _LIST {
    LIST_NODE *first_node;
    size_t data_size;
} LIST;

// rectangle
typedef struct _RECTANGLE {
    // top left corner
    COORD origin;
    short width, height, surface;
} RECTANGLE;

// room
typedef struct _ROOM {
    RECTANGLE rectangle;
    // flags
    char flags;
} ROOM;

// edge of the graph
typedef struct _GRAPH_EDGE {
    ROOM *room_1_pointer,
         *room_2_pointer;
    float distance;
    // flags
    BOOL is_a_corridor;
} GRAPH_EDGE;

// generic (n-ary) tree leaf
// typedef struct _LEAF {
//     struct _LEAF * parent;
//     float distance_to_parent;
//     ROOM * room_pointer;
//     LIST childs;
// } LEAF;

typedef struct _PLAYER {
    COORD position;
    unsigned int money;
    // unsigned int hit_points;
    // LIST items;
} PLAYER;

typedef struct _SCREEN {
    char **current,
         **new;
} SCREEN;

typedef struct _GAME {
    // the player
    PLAYER player;
    // the dungeon map (rooms and corridors) as a matrix of tiles (unsigned characters)
    unsigned char **map_dungeon;
    // the list of rooms in the dungeon
    LIST list_rooms;
    // the map of things in the dungeon (gold and stairs) as a matrix of things (unsigned shorts)
    unsigned short **map_things;
    // the map of the fog of war
    unsigned char **map_fow;
    SCREEN screen;
    INDEX level_counter;
    // BOOL exit;
} GAME;


#endif

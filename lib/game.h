#ifndef _HEADER_GAME
#define _HEADER_GAME

#include "types.h"
#include "display.h"
#include "linked_list.h"


// game options
// fog of war toggle: TRUE = ON, FALSE = OFF
extern BOOL fow_toggle;

// fog of war flags
#define FLAG_FOW_DISCOVERED (1 << 0)
#define FLAG_FOW_VISIBLE (1 << 1)


// direction type
typedef enum _DIRECTION {
    UP, DOWN, LEFT, RIGHT
} DIRECTION;


// functions

/*
Initialises the game state.

PARAMETERS
----------
GAME *game_state
    The pointer to the current game state
*/
void init_game_state(GAME *game_state);

/*
Handles the gameplay of the current level.

PARAMETERS
----------
GAME *game_state
    The pointer to the the current game state

RETURNS
-------
BOOL
    whether to exit the game
*/
BOOL play_level(GAME *game_state);

/*
Try to move the player character in the given direction.

PARAMETERS
----------
GAME *game_state
    The pointer to the the current game state
DIRECTION direction
    The direction in which the player attempts to move its character

RETURNS
-------
BOOL
    whether the player character moved.
*/
BOOL move_player(GAME *game_state, DIRECTION direction);

/*
Updates the fog of war according to the player position.

PARAMETERS
----------
GAME *game_state
    The pointer to the the current game state
*/
void update_fow(GAME *game_state);

/*
Returns the visibility rectangle of a room. The visibility rectangle is the room
rectangle + 1 tile in every direction, to account for the room walls and doors.

PARAMETERS
----------
ROOM *current_room_pointer
    The pointer to the room to get the visibility rectangle from.

RETURNS
-------
RECTANGLE
    The visibility rectangle of the room.
*/
RECTANGLE get_room_visibility_rectangle(ROOM *current_room_pointer);

/*
Whether a set of coordinates is inside a rectangle.

PARAMETERS
----------
COORD coords
    The coordinates of the point to check
RECTANGLE rect
    The rectangle to check against the coordinates

RETURNS
-------
BOOL
    Whether the coordinates are inside the rectangle
*/
BOOL is_inside_rect(COORD coords, RECTANGLE rect);


#endif

#ifndef _HEADER_DISPLAY
#define _HEADER_DISPLAY


#include "types.h"
#include "dungeon.h"
#include "game.h"


// sizes
#define DISPLAY_WIDTH 80
#define DISPLAY_HEIGHT 39
#define DISPLAY_HORIZONTAL_PADDING 2
#define DISPLAY_VERTICAL_PADDING 1
#define MAP_HORIZONTAL_PADDING 0
#define MAP_VERTICAL_PADDING 2
#define CONSOLE_WIDTH (DISPLAY_WIDTH + 2*DISPLAY_HORIZONTAL_PADDING)
#define CONSOLE_HEIGHT (DISPLAY_HEIGHT + 2*DISPLAY_VERTICAL_PADDING)
#define MAP_WIDTH (DISPLAY_WIDTH - 2*MAP_HORIZONTAL_PADDING)
#define MAP_HEIGHT (DISPLAY_HEIGHT - 2*MAP_VERTICAL_PADDING)

// map characters
#define CHAR_FILL ' '
#define CHAR_MAP_LIMIT '~'
#define CHAR_ROOM_FLOOR '.'
#define CHAR_CORRIDOR_FLOOR 177
#define CHAR_DOOR 206
#define CHAR_HORIZONTAL_WALL 205
#define CHAR_VERTICAL_WALL 186
#define CHAR_TOP_LEFT_CORNER 201
#define CHAR_TOP_RIGHT_CORNER 187
#define CHAR_BOTTOM_LEFT_CORNER 200
#define CHAR_BOTTOM_RIGHT_CORNER 188
#define CHAR_HORIZONTAL_TOP_WALL 202
#define CHAR_HORIZONTAL_BOTTOM_WALL 203
#define CHAR_VERTICAL_LEFT_WALL 185
#define CHAR_VERTICAL_RIGHT_WALL 204

// things characters
// #define CHAR_PLAYER '0'
#define CHAR_THING_PLAYER 2
// #define CHAR_STAIRS '¤'
#define CHAR_THING_STAIRS 207
#define CHAR_THING_GOLD '$'

// colors
#define COLOR_BLACK 0
#define COLOR_BLUE 1
#define COLOR_GREEN 2
#define COLOR_CYAN 3
#define COLOR_RED 4
#define COLOR_MAGENTA 5
#define COLOR_YELLOW 6
#define COLOR_WHITE 7
#define COLOR_BRIGHT_BLACK 8
#define COLOR_BRIGHT_BLUE 9
#define COLOR_BRIGHT_GREEN 10
#define COLOR_BRIGHT_CYAN 11
#define COLOR_BRIGHT_RED 12
#define COLOR_BRIGHT_MAGENTA 13
#define COLOR_BRIGHT_YELLOW 14
#define COLOR_BRIGHT_WHITE 15

// character colors
#define COLOR_ROOM_FLOOR COLOR_CYAN
#define COLOR_ROOM_WALL COLOR_YELLOW
#define COLOR_CORRIDOR_FLOOR COLOR_BRIGHT_BLACK
#define COLOR_PLAYER COLOR_BRIGHT_YELLOW
#define COLOR_GOLD COLOR_BRIGHT_GREEN
#define COLOR_STAIRS COLOR_RED

// wall connection flags
#define FLAG_WALL_CONNECT_TOP (1 << 0)
#define FLAG_WALL_CONNECT_RIGHT (1 << 1)
#define FLAG_WALL_CONNECT_BOTTOM (1 << 2)
#define FLAG_WALL_CONNECT_LEFT (1 << 3)


// functions

/*
Initialises the console window with the correct size.
*/
void init_window();

/*
Places the cursor at the given coordinates on the console.

PARAMETERS
----------
int x
    The X coordinate to give the cursor
int y
    The Y coordinate to give the cursor
*/
void set_cursor_position(int x, int y);

/*
Sets the text and background color for the next characters to be printed on the console.

PARAMETERS
----------
unsigned char text_color
    The number of the color to give to the text
unsigned char background_color
    The number of the color to give to the background
*/
void set_color(unsigned char text_color, unsigned char background_color);

/*
Reset the text and background color for the next characters to be printed
on the console to the default color.
*/
void reset_color();

/*
Initialises the screen character matrices.

PARAMETERS
----------
char ***current
    The pointer to the "current" map of characters to display
char ***new
    The pointer to the "new" map of characters to display
*/
void init_screen_chars_matrices(char ***current, char ***new);

/*
Draws the game on the "new" screen character matrix.

PARAMETERS
----------
GAME *game_state
    The pointer to the the current game state
*/
void draw_game_on_screen(GAME *game_state);

/*

*/
char generate_wall_char(unsigned char top_tile, unsigned char bottom_tile, unsigned char left_tile, unsigned char right_tile);
void update_screen(GAME *game_state);
void set_char_color(char char_to_display);


#endif

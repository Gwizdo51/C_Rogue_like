// https://stackoverflow.com/questions/17160553/making-the-console-window-bigger-in-c
// https://stackoverflow.com/questions/18028808/remove-blinking-underscore-on-console-cmd-prompt

// #include "rogue.h"
#include "display.h"


// void ShowConsoleCursor(BOOL showFlag)
// {
//     const HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
//     CONSOLE_CURSOR_INFO cursorInfo;

//     GetConsoleCursorInfo(hStdout, &cursorInfo);
//     cursorInfo.bVisible = showFlag; // set the cursor visibility
//     SetConsoleCursorInfo(hStdout, &cursorInfo);
// }


void init_window() {
    COORD coord;
    SMALL_RECT console_window;
    // HANDLE hStdout;
    const HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    // BOOL ok;
    CONSOLE_CURSOR_INFO cursorInfo;

    // console width
    coord.X = CONSOLE_WIDTH;
    // console height
    coord.Y = CONSOLE_HEIGHT;

    console_window.Left = 0;
    console_window.Top = 0;
    console_window.Right = coord.X-1;
    console_window.Bottom = coord.Y-1;

    SetConsoleScreenBufferSize(hStdout, coord);
    SetConsoleWindowInfo(hStdout, TRUE, &console_window);
    SetConsoleScreenBufferSize(hStdout, coord);

    // hide cursor
    GetConsoleCursorInfo(hStdout, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdout, &cursorInfo);
}


void cls() {
    const HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = { 0, 0 };
    DWORD length, written;

    // get the info of the console screen buffer
    GetConsoleScreenBufferInfo(hStdout, &csbi);
    // fill the buffer with spaces
    length = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hStdout, TEXT(' '), length, topLeft, &written);
    // reset the color attributes
    FillConsoleOutputAttribute(hStdout, csbi.wAttributes, length, topLeft, &written);
    // place the cursor on at the top left of the screen
    SetConsoleCursorPosition(hStdout, topLeft);
}


void set_cursor_position(int x, int y) {
    const HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {
        .X = (SHORT) x,
        .Y = (SHORT) y
    };
    SetConsoleCursorPosition(hStdout, coord);
}


void set_color(unsigned char text_color, unsigned char background_color) {
    const HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, text_color + background_color * 16);
}


void reset_color() {
    set_color(COLOR_WHITE, COLOR_BLACK);
}


void init_screen_chars_matrices(char ***current, char ***new) {
    INDEX index_line_display, index_column_display;
    // init lines
    *current = (char**) malloc(DISPLAY_HEIGHT * sizeof (char*));
    *new = (char**) malloc(DISPLAY_HEIGHT * sizeof (char*));
    // allocate lines length
    for (index_line_display = 0; index_line_display < DISPLAY_HEIGHT; index_line_display++) {
        *(*current + index_line_display) = (char*) malloc(DISPLAY_WIDTH * sizeof (char));
        *(*new + index_line_display) = (char*) malloc(DISPLAY_WIDTH * sizeof (char));
        // put spaces on every characters of the screens
        for (index_column_display = 0; index_column_display < DISPLAY_WIDTH; index_column_display++) {
            *(*(*current + index_line_display) + index_column_display) = CHAR_FILL;
            *(*(*new + index_line_display) + index_column_display) = CHAR_FILL;
        }
    }
}


void draw_game_on_screen(GAME *game_state) {
    INDEX index_line_display, index_column_display;
    short X_map, Y_map;
    unsigned char **map_dungeon = game_state->map_dungeon;
    unsigned short **map_things = game_state->map_things;
    unsigned char **map_fow = game_state->map_fow;
    unsigned char tile, top_tile, bottom_tile, left_tile, right_tile;
    unsigned short thing;
    char **new_screen = game_state->screen.new;
    for (index_line_display = MAP_VERTICAL_PADDING; index_line_display < MAP_VERTICAL_PADDING + MAP_HEIGHT; index_line_display++) {
        for (index_column_display = MAP_HORIZONTAL_PADDING; index_column_display < MAP_HORIZONTAL_PADDING + MAP_WIDTH; index_column_display++) {
            Y_map = index_line_display - MAP_VERTICAL_PADDING;
            X_map = index_column_display - MAP_HORIZONTAL_PADDING;
            // if the tile is not discovered, place a FILL character
            if ((*(*(map_fow + Y_map) + X_map) & FLAG_FOW_DISCOVERED) == 0 && fow_toggle) {
                *(*(new_screen + index_line_display) + index_column_display) = CHAR_FILL;
            }
            else {
                tile = *(*(map_dungeon + Y_map) + X_map);
                if (tile == TILE_FILL) {
                    *(*(new_screen + index_line_display) + index_column_display) = CHAR_FILL;
                }
                else if (tile == TILE_ROOM_FLOOR) {
                    // check if the player is on the tile
                    if (X_map == game_state->player.position.X && Y_map == game_state->player.position.Y) {
                        *(*(new_screen + index_line_display) + index_column_display) = CHAR_THING_PLAYER;
                    }
                    else {
                        // check if a thing is on the tile
                        thing = *(*(map_things + Y_map) + X_map);
                        if (thing == THING_NONE) {
                            // hide the tile if it is not visible
                            if ((*(*(map_fow + Y_map) + X_map) & FLAG_FOW_VISIBLE) != 0 || !fow_toggle) {
                                *(*(new_screen + index_line_display) + index_column_display) = CHAR_ROOM_FLOOR;
                            }
                            else {
                                *(*(new_screen + index_line_display) + index_column_display) = CHAR_FILL;
                            }
                        }
                        else if (thing == THING_GOLD) {
                            // hide the tile if it is not visible
                            if ((*(*(map_fow + Y_map) + X_map) & FLAG_FOW_VISIBLE) != 0 || !fow_toggle) {
                                *(*(new_screen + index_line_display) + index_column_display) = CHAR_THING_GOLD;
                            }
                            else {
                                *(*(new_screen + index_line_display) + index_column_display) = CHAR_FILL;
                            }
                        }
                        else if (thing == THING_STAIRS) {
                            *(*(new_screen + index_line_display) + index_column_display) = CHAR_THING_STAIRS;
                        }
                    }
                }
                else if (tile == TILE_CORRIDOR_FLOOR) {
                    // check if the player is on the tile
                    if (X_map == game_state->player.position.X && Y_map == game_state->player.position.Y) {
                        *(*(new_screen + index_line_display) + index_column_display) = CHAR_THING_PLAYER;
                    }
                    else {
                        *(*(new_screen + index_line_display) + index_column_display) = CHAR_CORRIDOR_FLOOR;
                    }
                }
                else if (tile == TILE_DOOR) {
                    // check if the player is on the tile
                    if (X_map == game_state->player.position.X && Y_map == game_state->player.position.Y) {
                        *(*(new_screen + index_line_display) + index_column_display) = CHAR_THING_PLAYER;
                    }
                    else {
                        *(*(new_screen + index_line_display) + index_column_display) = CHAR_DOOR;
                    }
                }
                else if (tile == TILE_ROOM_WALL) {
                    // get the top, bottom, left and right tile from the current tile
                    // top_tile = *(*(map + Y - 1) + X);
                    if (Y_map == 0 || ((*(*(map_fow + Y_map - 1) + X_map) & FLAG_FOW_DISCOVERED) == 0 && fow_toggle)) {top_tile = TILE_FILL;}
                    else {top_tile = *(*(map_dungeon + Y_map - 1) + X_map);}
                    // bottom_tile = *(*(map + Y + 1) + X);
                    if (Y_map == MAP_HEIGHT - 1 || ((*(*(map_fow + Y_map + 1) + X_map) & FLAG_FOW_DISCOVERED) == 0 && fow_toggle)) {bottom_tile = TILE_FILL;}
                    else {bottom_tile = *(*(map_dungeon + Y_map + 1) + X_map);}
                    // left_tile = *(*(map + Y) + X - 1);
                    if (X_map == 0 || ((*(*(map_fow + Y_map) + X_map - 1) & FLAG_FOW_DISCOVERED) == 0 && fow_toggle)) {left_tile = TILE_FILL;}
                    else {left_tile = *(*(map_dungeon + Y_map) + X_map - 1);}
                    // right_tile = *(*(map + Y) + X + 1);
                    if (X_map == MAP_WIDTH - 1 || ((*(*(map_fow + Y_map) + X_map + 1) & FLAG_FOW_DISCOVERED) == 0 && fow_toggle)) {right_tile = TILE_FILL;}
                    else {right_tile = *(*(map_dungeon + Y_map) + X_map + 1);}
                    *(*(new_screen + index_line_display) + index_column_display) = generate_wall_char(top_tile, bottom_tile, left_tile, right_tile);
                }
            }
        }
    }
    // print the level counter on top and the gold counter on the bottom
    sprintf(*new_screen, "LEVEL %u", game_state->level_counter);
    sprintf(*(new_screen + DISPLAY_HEIGHT - 1), "GOLD: %u", game_state->player.money);
}


char generate_wall_char(unsigned char top_tile, unsigned char bottom_tile, unsigned char left_tile, unsigned char right_tile) {
    char wall_char;
    unsigned char flags_connections = 0;
    // create a byte to hold flags that represent how the current wall connects to adjacent tiles
    if (top_tile == TILE_ROOM_WALL || top_tile == TILE_DOOR) {
        flags_connections |= FLAG_WALL_CONNECT_TOP;
    }
    if (bottom_tile == TILE_ROOM_WALL || bottom_tile == TILE_DOOR) {
        flags_connections |= FLAG_WALL_CONNECT_BOTTOM;
    }
    if (left_tile == TILE_ROOM_WALL || left_tile == TILE_DOOR) {
        flags_connections |= FLAG_WALL_CONNECT_LEFT;
    }
    if (right_tile == TILE_ROOM_WALL || right_tile == TILE_DOOR) {
        flags_connections |= FLAG_WALL_CONNECT_RIGHT;
    }
    // generate a wall character depending on the connections
    // straight walls
    if (flags_connections == (FLAG_WALL_CONNECT_TOP | FLAG_WALL_CONNECT_BOTTOM)) {
        wall_char = CHAR_VERTICAL_WALL;
    }
    else if (flags_connections == (FLAG_WALL_CONNECT_LEFT | FLAG_WALL_CONNECT_RIGHT)) {
        wall_char = CHAR_HORIZONTAL_WALL;
    }
    // corners
    else if (flags_connections == (FLAG_WALL_CONNECT_RIGHT | FLAG_WALL_CONNECT_BOTTOM)) {
        wall_char = CHAR_TOP_LEFT_CORNER;
    }
    else if (flags_connections == (FLAG_WALL_CONNECT_LEFT | FLAG_WALL_CONNECT_BOTTOM)) {
        wall_char = CHAR_TOP_RIGHT_CORNER;
    }
    else if (flags_connections == (FLAG_WALL_CONNECT_RIGHT | FLAG_WALL_CONNECT_TOP)) {
        wall_char = CHAR_BOTTOM_LEFT_CORNER;
    }
    else if (flags_connections == (FLAG_WALL_CONNECT_LEFT | FLAG_WALL_CONNECT_TOP)) {
        wall_char = CHAR_BOTTOM_RIGHT_CORNER;
    }
    // 3 walls connection
    else if (flags_connections == (FLAG_WALL_CONNECT_TOP | FLAG_WALL_CONNECT_BOTTOM | FLAG_WALL_CONNECT_LEFT)) {
        wall_char = CHAR_VERTICAL_LEFT_WALL;
    }
    else if (flags_connections == (FLAG_WALL_CONNECT_TOP | FLAG_WALL_CONNECT_BOTTOM | FLAG_WALL_CONNECT_RIGHT)) {
        wall_char = CHAR_VERTICAL_RIGHT_WALL;
    }
    else if (flags_connections == (FLAG_WALL_CONNECT_LEFT | FLAG_WALL_CONNECT_RIGHT | FLAG_WALL_CONNECT_TOP)) {
        wall_char = CHAR_HORIZONTAL_TOP_WALL;
    }
    else if (flags_connections == (FLAG_WALL_CONNECT_LEFT | FLAG_WALL_CONNECT_RIGHT | FLAG_WALL_CONNECT_BOTTOM)) {
        wall_char = CHAR_HORIZONTAL_BOTTOM_WALL;
    }
    // 4 walls connection
    else if (flags_connections == (FLAG_WALL_CONNECT_TOP | FLAG_WALL_CONNECT_BOTTOM | FLAG_WALL_CONNECT_LEFT | FLAG_WALL_CONNECT_RIGHT)) {
        wall_char = CHAR_DOOR;
    }
    return wall_char;
}


// void display_full_screen(char **screen) {
//     // int index_line_display, index_column_display;
//     INDEX index_line_display;
//     for (index_line_display=0; index_line_display < DISPLAY_HEIGHT; index_line_display++) {
//         set_cursor_position(DISPLAY_HORIZONTAL_PADDING, DISPLAY_VERTICAL_PADDING + index_line_display);
//         // for (index_column_display = 0 ; index_column_display < DISPLAY_WIDTH ; index_column_display++) {
//         //     printf("%c", *(*(screen_chars + index_line_display) + index_column_display));
//         // }
//         printf("%s", *(screen + index_line_display));
//     }
// }


void update_screen(GAME *game_state) {
    INDEX index_line_display, index_column_display;
    // for each characters of new, if it is different from the same
    // character in current, display the character and place it in current
    for (index_line_display = 0; index_line_display < DISPLAY_HEIGHT; index_line_display++) {
        for (index_column_display = 0 ; index_column_display < DISPLAY_WIDTH ; index_column_display++) {
            if (*(*(game_state->screen.new + index_line_display) + index_column_display) != *(*(game_state->screen.current + index_line_display) + index_column_display)) {
                // display the character at his position
                set_cursor_position(DISPLAY_HORIZONTAL_PADDING + index_column_display, DISPLAY_VERTICAL_PADDING + index_line_display);
                if (
                    index_line_display >= MAP_VERTICAL_PADDING &&
                    index_line_display < MAP_VERTICAL_PADDING + MAP_HEIGHT // &&
                    // index_column_display >= MAP_HORIZONTAL_PADDING &&
                    // index_column_display < MAP_HORIZONTAL_PADDING + MAP_WIDTH
                ) {
                    // if the character is on the map,
                    // choose the color for the map character to display
                    set_char_color(*(*(game_state->screen.new + index_line_display) + index_column_display));
                    // display the character
                    printf("%c", *(*(game_state->screen.new + index_line_display) + index_column_display));
                    // reset the color
                    reset_color();
                }
                else {
                    // otherwise, display the character in default color
                    printf("%c", *(*(game_state->screen.new + index_line_display) + index_column_display));
                }
                // place it in current
                *(*(game_state->screen.current + index_line_display) + index_column_display) = *(*(game_state->screen.new + index_line_display) + index_column_display);
            }
        }
    }
}


void set_char_color(char char_to_display) {
    unsigned char text_color;
    if (char_to_display != (char) CHAR_FILL) {
        if (char_to_display == (char) CHAR_ROOM_FLOOR) {
            text_color = COLOR_ROOM_FLOOR;
        }
        else if (char_to_display == (char) CHAR_CORRIDOR_FLOOR) {
            text_color = COLOR_CORRIDOR_FLOOR;
        }
        else if (char_to_display == (char) CHAR_THING_PLAYER) {
            text_color = COLOR_PLAYER;
        }
        else if (char_to_display == (char) CHAR_THING_GOLD) {
            text_color = COLOR_GOLD;
        }
        else if (char_to_display == (char) CHAR_THING_STAIRS) {
            text_color = COLOR_STAIRS;
        }
        else {
            text_color = COLOR_ROOM_WALL;
        }
        set_color(text_color, COLOR_BLACK);
    }
}


// void update_screen_no_display(char **current, char **new) {
//     INDEX index_line_display, index_column_display;
//     // copy new into current
//     for (index_line_display = 0; index_line_display < DISPLAY_HEIGHT; index_line_display++) {
//         for (index_column_display = 0 ; index_column_display < DISPLAY_WIDTH ; index_column_display++) {
//             *(*(current + index_line_display) + index_column_display) = *(*(new + index_line_display) + index_column_display);
//         }
//     }
// }

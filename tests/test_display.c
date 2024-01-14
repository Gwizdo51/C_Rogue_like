#include "..\lib\types.h"
#include "..\lib\display.h"


int main() {

    // characters array to display on the screen
    // char **screen_chars_current, **screen_chars_new;
    short index_line_display, index_column_display;
    short starting_pos_X = 62, starting_pos_Y = 17;
    // PLAYER player;
    char input_key;
    // BOOL quit_game;
    GAME game_state;
    // SHORT X, Y;

    // start the console window
    init_window();

    // allocate memory for the characters matrices
    // init_screen_chars_matrices(&screen_chars_current, &screen_chars_new);
    init_screen_chars_matrices(&game_state.screen.current, &game_state.screen.new);

    /*
    // fill array with a char
    for (index_line_display = 0 ; index_line_display < DISPLAY_HEIGHT ; index_line_display++) {
        for (index_column_display = 0 ; index_column_display < DISPLAY_WIDTH ; index_column_display++) {
            *(*(screen_chars_current + index_line_display) + index_column_display) = '\\';
        }
        *(*(screen_chars_current + index_line_display) + DISPLAY_WIDTH) = '\0';
    }
    // print all lines
    display_full_screen(screen_chars_current);
    getch();

    // fill with another char
    for (index_line_display = 0 ; index_line_display < DISPLAY_HEIGHT ; index_line_display++) {
        for (index_column_display = 0 ; index_column_display < DISPLAY_WIDTH ; index_column_display++) {
            *(*(screen_chars_current + index_line_display) + index_column_display) = '/';
        }
        *(*(screen_chars_current + index_line_display) + DISPLAY_WIDTH) = '\0';
    }
    display_full_screen(screen_chars_current);
    getch();
    // */

    /*
    // create walls
    for (index_line_display = 0; index_line_display < DISPLAY_HEIGHT; index_line_display++) {
        for (index_column_display = 0 ; index_column_display < DISPLAY_WIDTH ; index_column_display++) {
            if (index_line_display == 0 || index_line_display == DISPLAY_HEIGHT - 1 || index_column_display == 0 || index_column_display == DISPLAY_WIDTH - 1) {
                // place walls at each edge of the screen
                *(*(screen_chars_current + index_line_display) + index_column_display) = ROOM_WALL_CHAR;
                *(*(screen_chars_new + index_line_display) + index_column_display) = ROOM_WALL_CHAR;
            }
            else {
                // place spaces everywhere else
                *(*(screen_chars_current + index_line_display) + index_column_display) = FLOOR_CHAR;
                *(*(screen_chars_new + index_line_display) + index_column_display) = FLOOR_CHAR;
            }
        }
    }
    // add the player
    player.position.X = starting_pos_X;
    player.position.Y = starting_pos_Y;
    *(*(screen_chars_current + player.position.Y) + player.position.X) = PLAYER_CHAR;
    *(*(screen_chars_new + player.position.Y) + player.position.X) = PLAYER_CHAR;
    display_full_screen(screen_chars_current);
    // getch();
    // */

    /*
    // create random stuff to test updating screen
    *(*(screen_chars_new + 5) + 2) = 'A';
    *(*(screen_chars_new + 10) + 26) = 'B';
    *(*(screen_chars_new + 15) + 72) = 'C';
    *(*(screen_chars_new + 20) + 103) = 'D';
    *(*(screen_chars_new + 25) + 54) = 'E';
    update_screen(&screen_chars_current, screen_chars_new);
    getch();
    // */

    /*
    play area: 80 width, 35 height
    1 line to write stuff above, 1 line to write stuff below
    // */
    for (index_line_display = 0; index_line_display < DISPLAY_HEIGHT; index_line_display++) {
        if (index_line_display == MAP_VERTICAL_PADDING - 1 || index_line_display == MAP_VERTICAL_PADDING + MAP_HEIGHT) {
            // add '~' at the top and bottom of the playing field
            for (index_column_display = 0; index_column_display < DISPLAY_WIDTH; index_column_display++) {
                // *(*(screen_chars_current + index_line_display) + index_column_display) = PLAYFIELD_LIMIT_CHAR;
                *(*(game_state.screen.current + index_line_display) + index_column_display) = CHAR_MAP_LIMIT;
            }
        }
        else if (index_line_display >= MAP_VERTICAL_PADDING && index_line_display < MAP_VERTICAL_PADDING + MAP_HEIGHT) {
            // fill the playing field with a floor char
            for (index_column_display = 0; index_column_display < DISPLAY_WIDTH; index_column_display++) {
                *(*(game_state.screen.current + index_line_display) + index_column_display) = CHAR_ROOM_FLOOR;
            }
        }
        // add a sentence at the top and the bottom
        else if (index_line_display == 0) {
            strcpy(*(game_state.screen.current + index_line_display), "this is the top sentence");
        }
        else if (index_line_display == MAP_VERTICAL_PADDING + MAP_HEIGHT + 1) {
            strcpy(*(game_state.screen.current + index_line_display), "this is the bottom sentence");
        }
    }
    display_full_screen(game_state.screen.current);
    getch();
    // add the player
    // ...

    /*
    // game loop
    quit_game = FALSE;
    while (TRUE) {
        input_key = getch();
        switch (input_key) {
            case 'z':
                // move up
                *(*(screen_chars_new + player.position.Y) + player.position.X) = FLOOR_CHAR;
                player.position.Y--;
                *(*(screen_chars_new + player.position.Y) + player.position.X) = PLAYER_CHAR;
            break;
            case 'q':
                // move left
                *(*(screen_chars_new + player.position.Y) + player.position.X) = FLOOR_CHAR;
                player.position.X--;
                *(*(screen_chars_new + player.position.Y) + player.position.X) = PLAYER_CHAR;
            break;
            case 's':
                // move down
                *(*(screen_chars_new + player.position.Y) + player.position.X) = FLOOR_CHAR;
                player.position.Y++;
                *(*(screen_chars_new + player.position.Y) + player.position.X) = PLAYER_CHAR;
            break;
            case 'd':
                // move right
                *(*(screen_chars_new + player.position.Y) + player.position.X) = FLOOR_CHAR;
                player.position.X++;
                *(*(screen_chars_new + player.position.Y) + player.position.X) = PLAYER_CHAR;
            break;
            case ' ':
                // quit game
                quit_game = TRUE;
            break;
            default:
            break;
        }
        if (quit_game) {
            break;
        }
        update_screen(&screen_chars_current, screen_chars_new);
    }
    // */

    return EXIT_SUCCESS;
}

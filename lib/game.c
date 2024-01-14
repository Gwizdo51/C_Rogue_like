#include "game.h"


BOOL fow_toggle;


void init_game_state(GAME *game_state) {
    INDEX index_column_display, index_line_map;
    // allocate memory for the screen matrices
    init_screen_chars_matrices(&game_state->screen.current, &game_state->screen.new);
    // draw map delimiters
    // add '~' at the top and bottom of the playing field
    for (index_column_display = 0; index_column_display < MAP_WIDTH; index_column_display++) {
        *(*(game_state->screen.new + MAP_VERTICAL_PADDING - 1) + index_column_display) = CHAR_MAP_LIMIT;
        *(*(game_state->screen.new + MAP_VERTICAL_PADDING + MAP_HEIGHT) + index_column_display) = CHAR_MAP_LIMIT;
    }
    // allocate memory for the dungeon map, the things map and the FOW map
    game_state->map_dungeon = (unsigned char**) malloc(MAP_HEIGHT * sizeof (unsigned char*));
    game_state->map_things = (unsigned short**) malloc(MAP_HEIGHT * sizeof (unsigned short*));
    game_state->map_fow = (unsigned char**) malloc(MAP_HEIGHT * sizeof (unsigned char*));
    for (index_line_map = 0; index_line_map < MAP_HEIGHT; index_line_map++) {
        *(game_state->map_dungeon + index_line_map) = (unsigned char*) malloc(MAP_WIDTH * sizeof (unsigned char));
        *(game_state->map_things + index_line_map) = (unsigned short*) malloc(MAP_WIDTH * sizeof (unsigned short));
        *(game_state->map_fow + index_line_map) = (unsigned char*) malloc(MAP_WIDTH * sizeof (unsigned char));
    }
    // initialise list_rooms as an empty list
    game_state->list_rooms = ll_create(sizeof(ROOM));
    // initialise the player money
    game_state->player.money = 0;
    // initialise the level counter to 0
    game_state->level_counter = 0;
    // initialise the FOW toggle to TRUE
    fow_toggle = TRUE;
}


BOOL play_level(GAME *game_state) {
    BOOL flag_quit_game = FALSE,
         flag_level_over = FALSE,
         flag_update_screen;
    char input_key;
    // while the level isn't over ...
    while (!flag_level_over) {
        flag_update_screen = FALSE;
        // wait for the player input
        input_key = _getch();
        switch (input_key) {
        case 'z':
            // try to move the player character up
            flag_update_screen = move_player(game_state, UP);
            break;
        case 'q':
            // try to move the player character left
            flag_update_screen = move_player(game_state, LEFT);
            break;
        case 's':
            // try to move the player character down
            flag_update_screen = move_player(game_state, DOWN);
            break;
        case 'd':
            // try to move the player character right
            flag_update_screen = move_player(game_state, RIGHT);
            break;
        case '\r': // ENTER
            // try to enter the stairs
            if (*(*(game_state->map_things + game_state->player.position.Y) + game_state->player.position.X) == THING_STAIRS) {
                flag_level_over = TRUE;
            }
            break;
        case 'r':
            // auto win the level
            flag_level_over = TRUE;
            break;
        case 'f':
            // toggle the fow of war
            if (fow_toggle) {
                fow_toggle = FALSE;
            }
            else {
                fow_toggle = TRUE;
            }
            // update the screen
            flag_update_screen = TRUE;
            break;
        case '\e': // ESC
            // quit the game
            flag_level_over = TRUE;
            flag_quit_game = TRUE;
            break;
        default:
            break;
        }
        if (flag_level_over) {
            break;
        }
        if (flag_update_screen) {
            // update the fog of war map
            update_fow(game_state);
            // update the screen
            draw_game_on_screen(game_state);
            update_screen(game_state);
        }
    }
    return flag_quit_game;
}


BOOL move_player(GAME *game_state, DIRECTION direction) {
    BOOL movement_possible = TRUE;
    unsigned char tile_destination;
    // check if the player can move, i.e. there are no walls in the direction chosen
    switch (direction) {
    case UP:
        tile_destination = *(*(game_state->map_dungeon + game_state->player.position.Y - 1) + game_state->player.position.X);
        break;
    case DOWN:
        tile_destination = *(*(game_state->map_dungeon + game_state->player.position.Y + 1) + game_state->player.position.X);
        break;
    case LEFT:
        tile_destination = *(*(game_state->map_dungeon + game_state->player.position.Y) + game_state->player.position.X - 1);
        break;
    case RIGHT:
        tile_destination = *(*(game_state->map_dungeon + game_state->player.position.Y) + game_state->player.position.X + 1);
        break;
    }
    if (tile_destination == TILE_FILL || tile_destination == TILE_ROOM_WALL) {
        movement_possible = FALSE;
    }
    // if the move is possible ..
    if (movement_possible) {
        // move the player
        switch (direction) {
        case UP:
            game_state->player.position.Y--;
            break;
        case DOWN:
            game_state->player.position.Y++;
            break;
        case LEFT:
            game_state->player.position.X--;
            break;
        case RIGHT:
            game_state->player.position.X++;
            break;
        }
        // if there is something at the new player's position, collect it
        if (*(*(game_state->map_things + game_state->player.position.Y) + game_state->player.position.X) == THING_GOLD) {
            *(*(game_state->map_things + game_state->player.position.Y) + game_state->player.position.X) = THING_NONE;
            game_state->player.money++;
        }
    }
    return movement_possible;
}


/*
Updates the fog of war according to the player position.
*/
/*
void update_fow(GAME *game_state) {
    short X, Y;
    INDEX index_room;
    ROOM *current_room_pointer;
    RECTANGLE current_room_visibility_rectangle, player_visibility_rectangle;
    // BOOL player_sees_room;
    unsigned char current_tile;
    // set all tiles to not visible
    for (X = 0; X < MAP_WIDTH; X++) {
        for (Y = 0; Y < MAP_HEIGHT; Y++) {
            *(*(game_state->map_fow + Y) + X) &= ~FLAG_FOW_VISIBLE;
        }
    }
    // for every room, check if the player sees the room
    for (index_room = 0; index_room < ll_length(&game_state->list_rooms); index_room++) {
        // the player sees the room if the player is inside the room rectangle + 1 tile in every direction
        // (the player sees the inside of the room in the doorways)
        current_room_pointer = (ROOM*) ll_get(&game_state->list_rooms, index_room);
        current_room_visibility_rectangle = get_room_visibility_rectangle(current_room_pointer);
        // player_sees_room = is_inside_rect(game_state->player.position, current_room_visibility_rectangle);
        if (is_inside_rect(game_state->player.position, current_room_visibility_rectangle)) {
            // if so, set all floor, wall and door tiles of the room to visible and discovered
            for (
                X = current_room_visibility_rectangle.origin.X;
                X < current_room_visibility_rectangle.origin.X + current_room_visibility_rectangle.width;
                X++
            ) {
                for (
                    Y = current_room_visibility_rectangle.origin.Y;
                    Y < current_room_visibility_rectangle.origin.Y + current_room_visibility_rectangle.height;
                    Y++
                ) {
                    *(*(game_state->map_fow + Y) + X) |= (FLAG_FOW_VISIBLE | FLAG_FOW_DISCOVERED);
                }
            }
        }
    }
    // set all corridor and door tiles in a 3x3 square around the player to visible and discovered
    player_visibility_rectangle.origin = game_state->player.position;
    player_visibility_rectangle.origin.X--;
    player_visibility_rectangle.origin.Y--;
    player_visibility_rectangle.width = 3;
    player_visibility_rectangle.height = 3;
    for (
        X = player_visibility_rectangle.origin.X;
        X < player_visibility_rectangle.origin.X + player_visibility_rectangle.width;
        X++
    ) {
        for (
            Y = player_visibility_rectangle.origin.Y;
            Y < player_visibility_rectangle.origin.Y + player_visibility_rectangle.height;
            Y++
        ) {
            current_tile = *(*(game_state->map_dungeon + Y) + X);
            if (current_tile == TILE_CORRIDOR_FLOOR || current_tile == TILE_DOOR) {
                *(*(game_state->map_fow + Y) + X) |= (FLAG_FOW_VISIBLE | FLAG_FOW_DISCOVERED);
            }
        }
    }
}
// */

//*
void update_fow(GAME *game_state) {
    INDEX index_room;
    ROOM *current_room_pointer;
    RECTANGLE current_room_visibility_rectangle, player_visibility_rectangle;
    short X, Y;
    // unsigned char current_tile;
    COORD current_coords;
    // set every room tiles (floor, doors and walls) to not visible if the player does not see the room
    // for every room ...
    for (index_room = 0; index_room < ll_length(&game_state->list_rooms); index_room++) {
        current_room_pointer = (ROOM*) ll_get(&game_state->list_rooms, index_room);
        current_room_visibility_rectangle = get_room_visibility_rectangle(current_room_pointer);
        // if the player character does not see the room ...
        if (!is_inside_rect(game_state->player.position, current_room_visibility_rectangle)) {
            // set every floor, wall and door tile of the room to not visible
            for (
                X = current_room_visibility_rectangle.origin.X;
                X < current_room_visibility_rectangle.origin.X + current_room_visibility_rectangle.width;
                X++
            ) {
                for (
                    Y = current_room_visibility_rectangle.origin.Y;
                    Y < current_room_visibility_rectangle.origin.Y + current_room_visibility_rectangle.height;
                    Y++
                ) {
                    *(*(game_state->map_fow + Y) + X) &= ~FLAG_FOW_VISIBLE;
                }
            }
        }
    }
    // set every room tiles (floor, doors and walls) to visible and discovered if the player sees the room
    // for every room ...
    for (index_room = 0; index_room < ll_length(&game_state->list_rooms); index_room++) {
        current_room_pointer = (ROOM*) ll_get(&game_state->list_rooms, index_room);
        current_room_visibility_rectangle = get_room_visibility_rectangle(current_room_pointer);
        // if the player character sees the room ...
        if (is_inside_rect(game_state->player.position, current_room_visibility_rectangle)) {
            // set all floor, wall and door tiles of the room to visible and discovered
            for (
                X = current_room_visibility_rectangle.origin.X;
                X < current_room_visibility_rectangle.origin.X + current_room_visibility_rectangle.width;
                X++
            ) {
                for (
                    Y = current_room_visibility_rectangle.origin.Y;
                    Y < current_room_visibility_rectangle.origin.Y + current_room_visibility_rectangle.height;
                    Y++
                ) {
                    *(*(game_state->map_fow + Y) + X) |= (FLAG_FOW_VISIBLE | FLAG_FOW_DISCOVERED);
                }
            }
        }
    }
    // set all corridor and door tiles in a 3x3 square around the player to visible and discovered
    player_visibility_rectangle.origin = game_state->player.position;
    player_visibility_rectangle.origin.X--;
    player_visibility_rectangle.origin.Y--;
    player_visibility_rectangle.width = 3;
    player_visibility_rectangle.height = 3;
    // for every tile on the map ...
    for (X = 0; X < MAP_WIDTH; X++) {
        for (Y = 0; Y < MAP_HEIGHT; Y++) {
            // if the tile is a corridor floor or a room door ...
            if (*(*(game_state->map_dungeon + Y) + X) == TILE_CORRIDOR_FLOOR || *(*(game_state->map_dungeon + Y) + X) == TILE_DOOR) {
                // check if the player is in the vicinity
                current_coords.X = X;
                current_coords.Y = Y;
                if (is_inside_rect(current_coords, player_visibility_rectangle)) {
                    // set the tile to visible and discovered
                    *(*(game_state->map_fow + Y) + X) |= (FLAG_FOW_VISIBLE | FLAG_FOW_DISCOVERED);
                }
                else {
                    // set the tile to not visible
                    *(*(game_state->map_fow + Y) + X) &= ~FLAG_FOW_VISIBLE;
                }
            }
        }
    }
}
// */


RECTANGLE get_room_visibility_rectangle(ROOM *current_room_pointer) {
    RECTANGLE visibility_rectangle = current_room_pointer->rectangle;
    visibility_rectangle.origin.X--;
    visibility_rectangle.origin.Y--;
    visibility_rectangle.width += 2;
    visibility_rectangle.height += 2;
    return visibility_rectangle;
}


BOOL is_inside_rect(COORD coords, RECTANGLE rect) {
    BOOL coords_inside_rect = FALSE;
    if (
        coords.X >= rect.origin.X &&
        coords.X < rect.origin.X + rect.width &&
        coords.Y >= rect.origin.Y &&
        coords.Y < rect.origin.Y + rect.height
    ) {
        coords_inside_rect = TRUE;
    }
    return coords_inside_rect;
}

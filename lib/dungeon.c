#include "dungeon.h"


/* dungeon generation:
place a random number of rooms with random sizes (biggest rooms first)
create a graph with the center of the rooms as vertices and their distances as edges
find the minimum spanning tree between the rooms with Prim's algorithm
create corridors between the rooms connected in the tree
add a random amount of additional corridors from the ones in the graph (total number of corridors not more than 2x the original number)
*/
void generate_dungeon(GAME *game_state) {
    LIST list_graph_edges = ll_create(sizeof(GRAPH_EDGE));
    // clear the dungeon map, the things map and the FOW map
    clear_map(game_state);
    // generate a random number of rooms
    generate_rooms(&game_state->list_rooms);
    /*
    INDEX index_room;
    ROOM *current_room_pointer;
    printf("dungeon rooms:\n");
    for (index_room = 0; index_room < ll_length(&list_rooms); index_room++) {
        current_room_pointer = (ROOM*) ll_get(&list_rooms, index_room);
        printf("\troom #%u:\n", index_room);
        printf("\t\tX = %d\n", current_room_pointer->rectangle.origin.X);
        printf("\t\tY = %d\n", current_room_pointer->rectangle.origin.Y);
        printf("\t\twidth = %d\n", current_room_pointer->rectangle.width);
        printf("\t\theight = %d\n", current_room_pointer->rectangle.height);
    }
    printf("\n");
    // */
    // generate the corridors between the rooms
    generate_corridors(&game_state->list_rooms, &list_graph_edges);
    // draw the dungeon on the map
    draw_dungeon_on_map(&game_state->list_rooms, &list_graph_edges, game_state->map_dungeon);
    // place the stairs and the player on the map
    // generate_things(&game_state->list_rooms, game_state);
    generate_things(game_state);
    ll_free(&list_graph_edges);
}


void clear_map(GAME *game_state) {
    unsigned short X, Y;
    for (Y = 0; Y < MAP_HEIGHT; Y++) {
        for (X = 0; X < MAP_WIDTH; X++) {
            // set all map tiles to FILL
            *(*(game_state->map_dungeon + Y) + X) = TILE_FILL;
            // set all things to THING_NONE
            *(*(game_state->map_things + Y) + X) = THING_NONE;
            // set all tiles to undiscovered
            *(*(game_state->map_fow + Y) + X) = 0;
        }
    }
    // empty the list of rooms
    ll_free(&game_state->list_rooms);
}


/* room placement:
create an empty list of rooms
create and add to the list a random number of new rooms with random sizes
sort the list by room size
for every room in the list:
    list the possible places where the room can fit
    if the list of places is empty:
        mark the room as not placed
    else:
        place the room at a random possible location
        mark the room as placed
index_room = 0
while TRUE:
    if list_rooms[index_room] not placed:
        delete the room from the list
    else:
        increment index_room
        if index_room = length(list_rooms):
            break
*/
void generate_rooms(LIST *list_rooms) {
    INDEX number_of_rooms, index_room;
    ROOM new_room;
    // init the room flags to all FALSE
    new_room.flags = 0;
    // add to the list a random number of rooms
    number_of_rooms = rand_range(MIN_ROOMS, MAX_ROOMS);
    for (index_room = 0; index_room < number_of_rooms; index_room++) {
        // create a new room with a random size
        // width and height are odd numbers so that the rooms always have an unambiguous center tile
        new_room.rectangle.width = rand_odd_range(ROOM_MIN_WIDTH, ROOM_MAX_WIDTH);
        new_room.rectangle.height = rand_odd_range(ROOM_MIN_HEIGHT, ROOM_MAX_HEIGHT);
        new_room.rectangle.surface = new_room.rectangle.width * new_room.rectangle.height;
        ll_append(list_rooms, &new_room);
    }
    // sort the list of rooms by size
    sort_rooms_by_size(list_rooms);
    // place the rooms on the map
    place_rooms(list_rooms);
    // remove all rooms not placed from the list of rooms
    remove_not_placed_rooms(list_rooms);
}


void sort_rooms_by_size(LIST *list_rooms) {
    // printf("sorting rooms by size ...\n");
    INDEX index_smallest_room, number_of_rooms, i, j;
    short smallest_room_size, current_room_size;
    // find the smallest room and put it first in the list
    number_of_rooms = ll_length(list_rooms);
    // for every room i in the list ...
    for (i = 0; i < number_of_rooms - 1; i++) {
        // set the smallest room as the room i
        index_smallest_room = i;
        smallest_room_size = ((ROOM*) ll_get(list_rooms, i))->rectangle.surface;
        // for every room j in the list, with j > i ...
        for (j = i + 1; j < number_of_rooms; j++) {
            // set j as the smallest room if it is
            current_room_size = ((ROOM*) ll_get(list_rooms, j))->rectangle.surface;
            if (current_room_size < smallest_room_size) {
                index_smallest_room = j;
                smallest_room_size = current_room_size;
            }
        }
        // swap the smallest room with the room i
        if (i != index_smallest_room) {
            ll_swap(list_rooms, i, index_smallest_room);
        }
    }
}


void place_rooms(LIST *list_rooms) {
    INDEX number_of_rooms, index_room_i, index_room_j, number_of_possible_origins;
    ROOM *current_room_pointer, *other_room_pointer;
    RECTANGLE current_room_rectangle;
    short X, Y;
    BOOL room_collision;
    LIST list_possible_origins = ll_create(sizeof(COORD));
    number_of_rooms = ll_length(list_rooms);
    // for every room in the list ...
    for (index_room_i = 0; index_room_i < number_of_rooms; index_room_i++) {
        // list all the suitable coordinates for the origin of the room:
        // 1- to ensure the corridors and the rooms align nicely, the origin X and Y values can only be odd
        // 2- the room cannot collide with another room already placed
        // 3- some distance must be left from the map limits to place the room walls
        current_room_pointer = (ROOM*) ll_get(list_rooms, index_room_i);
        current_room_rectangle.width = current_room_pointer->rectangle.width;
        current_room_rectangle.height = current_room_pointer->rectangle.height;
        for (X = 1; X < MAP_WIDTH - current_room_rectangle.width; X += 2) {
            for (Y = 1; Y < MAP_HEIGHT - current_room_rectangle.height; Y += 2) {
                // check if the room would collide with any other room if placed at these coordinates
                room_collision = FALSE;
                current_room_rectangle.origin.X = X;
                current_room_rectangle.origin.Y = Y;
                for (index_room_j = 0; index_room_j < number_of_rooms; index_room_j++) {
                    other_room_pointer = (ROOM*) ll_get(list_rooms, index_room_j);
                    if ((other_room_pointer->flags & FLAG_ROOM_PLACED_ON_MAP) && rect_intersect(current_room_rectangle, other_room_pointer->rectangle)) {
                        room_collision = TRUE;
                        break;
                    }
                }
                if (!room_collision) {
                    ll_append(&list_possible_origins, &current_room_rectangle.origin);
                }
            }
        }
        // if there are suitable coordinates for the current room ...
        number_of_possible_origins = ll_length(&list_possible_origins);
        if (number_of_possible_origins > 0) {
            // choose a random origin for the room from the list of possible origins
            current_room_pointer->rectangle.origin = *(COORD*) ll_get(&list_possible_origins, rand_range(0, number_of_possible_origins - 1));
            // mark the room as placed
            current_room_pointer->flags |= FLAG_ROOM_PLACED_ON_MAP;
        }
        ll_free(&list_possible_origins);
    }
}


// https://stackoverflow.com/questions/31022269/collision-detection-between-two-rectangles-in-java
BOOL rect_intersect(RECTANGLE rect_1, RECTANGLE rect_2) {
    BOOL intersection = FALSE;
    if (
        // if the left side of rect_1 is less than the right side of rect_2 ...
        rect_1.origin.X < rect_2.origin.X + rect_2.width &&
        // and the right side of rect_1 is more than the left side of rect_2 ...
        rect_1.origin.X + rect_1.width > rect_2.origin.X &&
        // and the top of rect_1 is less than the bottom of rect_2 ...
        rect_1.origin.Y < rect_2.origin.Y + rect_2.height &&
        // and the bottom of rect_1 is more than the top of rect_2 ...
        rect_1.origin.Y + rect_1.height > rect_2.origin.Y
    ) {
        // the rectangles intersect
        intersection = TRUE;
    }
    return intersection;
}


void remove_not_placed_rooms(LIST *list_rooms) {
    INDEX index_room, initial_number_of_rooms;
    ROOM *current_room;
    initial_number_of_rooms = ll_length(list_rooms);
    for (index_room = 0; index_room < initial_number_of_rooms; index_room++) {
        // because the list will shrink from loop to loop, we must remove the rooms from the list starting from the end
        current_room = (ROOM*) ll_get(list_rooms, initial_number_of_rooms - 1 - index_room);
        if (!(current_room->flags & FLAG_ROOM_PLACED_ON_MAP)) {
            ll_remove(list_rooms, initial_number_of_rooms - 1 - index_room);
        }
    }
}


void generate_corridors(LIST *list_rooms, LIST *list_graph_edges) {
    // add all the possible graph edges to the list
    generate_graph(list_rooms, list_graph_edges);
    /*
    INDEX index_edge;
    GRAPH_EDGE *current_graph_edge_pointer;
    printf("graph edges:\n");
    for (index_edge = 0; index_edge < ll_length(list_graph_edges); index_edge++) {
        current_graph_edge_pointer = (GRAPH_EDGE*) ll_get(list_graph_edges, index_edge);
        printf("\tedge #%u: distance = %.2f\n", index_edge, current_graph_edge_pointer->distance);
    }
    printf("\n");
    // */
    // generate the minimum spanning tree between the rooms with Prim's algorithm
    generate_mst(list_rooms, list_graph_edges);
    /*
    INDEX index_room;
    ROOM *current_room_pointer;
    printf("dungeon rooms:\n");
    for (index_room = 0; index_room < ll_length(list_rooms); index_room++) {
        current_room_pointer = (ROOM*) ll_get(list_rooms, index_room);
        printf("\troom #%u:\n", index_room);
        printf("\t\tadded to mst: %d\n", current_room_pointer->added_to_MST);
        printf("\t\tspawn player = %d\n", current_room_pointer->spawn_player);
        printf("\t\tspawn stairs = %d\n", current_room_pointer->spawn_stairs);
    }
    printf("\n");
    printf("corridors:\n");
    for (index_edge = 0; index_edge < ll_length(list_graph_edges); index_edge++) {
        current_graph_edge_pointer = (GRAPH_EDGE*) ll_get(list_graph_edges, index_edge);
        if (current_graph_edge_pointer->is_a_corridor) {
            printf("edge #%u is a corridor\n", index_edge);
        }
    }
    printf("\n");
    // */
    // add some additional corridors -> between 0 and original_number_of_corridors / 4
    add_random_corridors(list_graph_edges);
}


/* graph generation:
(create a list of tree leaves (acting as vertices) corresponding to each room)
-> just use the list of rooms
(create a list of distances between each room (acting as edges))
create an empty list of graph edges
for index_room_i from 0 to length(list_rooms)-2:
    for index_room_j from index_room_i+1 to length(list_rooms)-1:
        add the edge between index_room_i and index_room_j to the list of edges
*/
void generate_graph(LIST *list_rooms, LIST *list_graph_edges) {
    INDEX number_of_rooms, index_room_i, index_room_j;
    GRAPH_EDGE graph_edge;
    number_of_rooms = ll_length(list_rooms);
    for (index_room_i = 0; index_room_i < number_of_rooms - 1; index_room_i++) {
        for (index_room_j = index_room_i + 1; index_room_j < number_of_rooms; index_room_j++) {
            // add a new edge from the room i to the room j
            // printf("adding edge between rooms %u and %u\n", index_room_i, index_room_j);
            graph_edge.room_1_pointer = (ROOM*) ll_get(list_rooms, index_room_i);
            graph_edge.room_2_pointer = (ROOM*) ll_get(list_rooms, index_room_j);
            graph_edge.distance = room_distance(graph_edge.room_1_pointer, graph_edge.room_2_pointer);
            graph_edge.is_a_corridor = FALSE;
            ll_append(list_graph_edges, &graph_edge);
        }
    }
}


float room_distance(ROOM *room_1, ROOM *room_2) {
    COORD center_room_1 = get_room_center(room_1),
          center_room_2 = get_room_center(room_2);
    float X1 = (float) center_room_1.X,
          Y1 = (float) center_room_1.Y,
          X2 = (float) center_room_2.X,
          Y2 = (float) center_room_2.Y;
    // give more weight to the Y axis in the distance calculation
    // to account for characters display size on the cmd prompt
    // cmd prompt char pixel width: 7
    // cmd prompt char pixel height: 16
    float distance = sqrtf(powf(X2 - X1, 2) + powf((Y2 - Y1) * 16 / 7, 2));
    return distance;
}


COORD get_room_center(ROOM *room) {
    COORD center_room = {
        .X = room->rectangle.origin.X + (room->rectangle.width - 1) / 2,
        .Y = room->rectangle.origin.Y + (room->rectangle.height - 1) / 2
    };
    return center_room;
}


/* Prim's MST:
set the first leaf in the list as the tree root
while there are leaves that are not in the tree:
    list the indices of all the edges that connect the tree to leaves not in the tree yet
    find the edge with the minimum distance
    connect the corresponding leaf to the tree
*/
void generate_mst(LIST *list_rooms, LIST *list_graph_edges) {
    // printf("generate_mst begin\n");
    INDEX index_room, index_edge, index_edge_minimum_distance, index;
    ROOM *room_pointer, *last_added_room_pointer;
    GRAPH_EDGE *graph_edge_pointer;
    LIST list_indices_possible_connections = ll_create(sizeof(INDEX));
    float minimum_distance, current_edge_distance;
    // choose a random room and set it as the tree root
    index_room = rand_range(0, ll_length(list_rooms) - 1);
    room_pointer = (ROOM*) ll_get(list_rooms, index_room);
    room_pointer->flags |= FLAG_ROOM_ADDED_TO_MST;
    // spawn the player in this room
    room_pointer->flags |= FLAG_ROOM_SPAWN_PLAYER;
    // printf("1st room chosen: #%u \n", index_room);
    // while there are rooms not connected to the tree yet ...
    while (!all_rooms_added_to_mst(list_rooms)) {
        // printf("all rooms not yet added, looping ...\n");
        // list the indices of all the edges that connect the tree to rooms not in the tree yet
        // printf("listing all indices of edges that connect lone rooms to tree ...\n");
        for (index_edge = 0; index_edge < ll_length(list_graph_edges); index_edge++) {
            graph_edge_pointer = (GRAPH_EDGE*) ll_get(list_graph_edges, index_edge);
            // printf("edge #%u:\n", index_edge);
            // printf("\troom 1 in mst: %d\n", graph_edge_pointer->room_1_pointer->added_to_MST);
            // printf("\troom 2 in mst: %d\n", graph_edge_pointer->room_2_pointer->added_to_MST);
            if (
                ((graph_edge_pointer->room_1_pointer->flags & FLAG_ROOM_ADDED_TO_MST) != 0 && (graph_edge_pointer->room_2_pointer->flags & FLAG_ROOM_ADDED_TO_MST) == 0) ||
                ((graph_edge_pointer->room_1_pointer->flags & FLAG_ROOM_ADDED_TO_MST) == 0 && (graph_edge_pointer->room_2_pointer->flags & FLAG_ROOM_ADDED_TO_MST) != 0)
            ) {
                // printf("\tpossible connection\n");
                ll_append(&list_indices_possible_connections, &index_edge);
            }
        }
        // find the index of the edge with the minimum distance
        // printf("finding the edge with the minimum distance ...\n");
        index_edge_minimum_distance = *(INDEX*) ll_get(&list_indices_possible_connections, 0);
        minimum_distance = ((GRAPH_EDGE*) ll_get(list_graph_edges, index_edge_minimum_distance))->distance;
        for (index = 1; index < ll_length(&list_indices_possible_connections); index++) {
            index_edge = *(INDEX*) ll_get(&list_indices_possible_connections, index);
            current_edge_distance = ((GRAPH_EDGE*) ll_get(list_graph_edges, index_edge))->distance;
            if (current_edge_distance < minimum_distance) {
                index_edge_minimum_distance = index_edge;
                minimum_distance = current_edge_distance;
            }
        }
        // printf("edge #%u has the minimum distance\n", index_edge_minimum_distance);
        // set the edge as a corridor
        graph_edge_pointer = (GRAPH_EDGE*) ll_get(list_graph_edges, index_edge_minimum_distance);
        graph_edge_pointer->is_a_corridor = TRUE;
        // mark the room as added to the tree
        if ((graph_edge_pointer->room_1_pointer->flags & FLAG_ROOM_ADDED_TO_MST) != 0) {
            graph_edge_pointer->room_2_pointer->flags |= FLAG_ROOM_ADDED_TO_MST;
            last_added_room_pointer = graph_edge_pointer->room_2_pointer;
        }
        else {
            graph_edge_pointer->room_1_pointer->flags |= FLAG_ROOM_ADDED_TO_MST;
            last_added_room_pointer = graph_edge_pointer->room_1_pointer;
        }
        // free the list of indices
        ll_free(&list_indices_possible_connections);
    }
    // spawn the stairs in the last room added
    last_added_room_pointer->flags |= FLAG_ROOM_SPAWN_STAIRS;
    // printf("generate_mst end\n");
}


BOOL all_rooms_added_to_mst(LIST *list_rooms) {
    BOOL all_rooms_connected = TRUE;
    INDEX index_room;
    for (index_room = 0; index_room < ll_length(list_rooms); index_room++) {
        if ((((ROOM*) ll_get(list_rooms, index_room))->flags & FLAG_ROOM_ADDED_TO_MST) == 0) {
            all_rooms_connected = FALSE;
            break;
        }
    }
    return all_rooms_connected;
}


/* corridor generation:
create a list of all the edges in the MSP (list of indices)
create a list of all the edges not in the MSP (list of indices)
add some additional edges (not more than 1x more) -> transfert some indices from one list to the other
for each edge in the list:
    count the number of vertical and horizontal steps the corridor must take to go from one room center to the other
    while there are still steps to take:
        chose a random step to take among those still available
*/


void add_random_corridors(LIST *list_graph_edges) {
    INDEX number_corridors_original = 0, index_edge, number_new_corridors,  counter, index;
    LIST list_graph_edge_indices_not_corridors = ll_create(sizeof(INDEX));
    GRAPH_EDGE *current_graph_edge_pointer;
    for (index_edge = 0; index_edge < ll_length(list_graph_edges); index_edge++) {
        // get the original number of corridors and list the graph edges that are not corridors yet
        current_graph_edge_pointer = (GRAPH_EDGE*) ll_get(list_graph_edges, index_edge);
        if (current_graph_edge_pointer->is_a_corridor) {
            number_corridors_original++;
        }
        else {
            ll_append(&list_graph_edge_indices_not_corridors, &index_edge);
        }
    }
    // choose a random number of new corridors to add
    number_new_corridors = (INDEX) roundf((float) number_corridors_original / 4);
    number_new_corridors = rand_range(0, number_new_corridors);
    for (counter = 0; counter < number_new_corridors; counter++) {
        // choose a random index in the created list
        index = rand_range(0, ll_length(&list_graph_edge_indices_not_corridors) - 1);
        index_edge = *(INDEX*) ll_get(&list_graph_edge_indices_not_corridors, index);
        current_graph_edge_pointer = (GRAPH_EDGE*) ll_get(list_graph_edges, index_edge);
        // set the edge as a corridor
        current_graph_edge_pointer->is_a_corridor = TRUE;
        // remove the index from the list
        ll_remove(&list_graph_edge_indices_not_corridors, index);
    }
    ll_free(&list_graph_edge_indices_not_corridors);
}


void draw_dungeon_on_map(LIST *list_rooms, LIST *list_graph_edges, unsigned char **map) {
    INDEX index_room, index_edge, index_step_picked;
    short X, Y, steps_X, steps_Y, index_step;
    ROOM *current_room_pointer;
    GRAPH_EDGE *current_graph_edge_pointer;
    COORD center_room_1, center_room_2, cursor_position;
    char step;
    LIST list_steps = ll_create(sizeof(char));
    // draw corridors
    for (index_edge = 0; index_edge < ll_length(list_graph_edges); index_edge++) {
        current_graph_edge_pointer = (GRAPH_EDGE*) ll_get(list_graph_edges, index_edge);
        if (current_graph_edge_pointer->is_a_corridor) {
            // draw a corridor from the center of the room 1 to the center of the room 2
            // snap the center of the rooms to the corridor grid
            center_room_1 = get_room_center_snapped(current_graph_edge_pointer->room_1_pointer);
            center_room_2 = get_room_center_snapped(current_graph_edge_pointer->room_2_pointer);
            // count the number of horizontal and vertical steps that must be taken to go
            // from one snapped center to the other (1 step == 2 tiles)
            steps_X = (center_room_2.X - center_room_1.X) / 2;
            steps_Y = (center_room_2.Y - center_room_1.Y) / 2;
            // create a list of steps
            // 0: X positive
            // 1: X negative
            // 2: Y positive
            // 3: Y negative
            if (steps_X >= 0) {
                // towards positive X
                step = 0;
                for (index_step = 0; index_step < steps_X; index_step++) {
                    ll_append(&list_steps, &step);
                }
            }
            else {
                // towards negative X
                step = 1;
                for (index_step = 0; index_step < -steps_X; index_step++) {
                    ll_append(&list_steps, &step);
                }
            }
            if (steps_Y >= 0) {
                // towards positive Y
                step = 2;
                for (index_step = 0; index_step < steps_Y; index_step++) {
                    ll_append(&list_steps, &step);
                }
            }
            else {
                // towards negative Y
                step = 3;
                for (index_step = 0; index_step < -steps_Y; index_step++) {
                    ll_append(&list_steps, &step);
                }
            }
            cursor_position = center_room_1;
            // while there are steps in the list ...
            while (ll_length(&list_steps) > 0) {
                // pick a random step from the list
                index_step_picked = rand_range(0, ll_length(&list_steps) - 1);
                step = *(char*) ll_get(&list_steps, index_step_picked);
                ll_remove(&list_steps, index_step_picked);
                if (step == 0) {
                    cursor_position.X++;
                    *(*(map + cursor_position.Y) + cursor_position.X) = TILE_CORRIDOR_FLOOR;
                    cursor_position.X++;
                    *(*(map + cursor_position.Y) + cursor_position.X) = TILE_CORRIDOR_FLOOR;
                }
                else if (step == 1) {
                    cursor_position.X--;
                    *(*(map + cursor_position.Y) + cursor_position.X) = TILE_CORRIDOR_FLOOR;
                    cursor_position.X--;
                    *(*(map + cursor_position.Y) + cursor_position.X) = TILE_CORRIDOR_FLOOR;
                }
                else if (step == 2) {
                    cursor_position.Y++;
                    *(*(map + cursor_position.Y) + cursor_position.X) = TILE_CORRIDOR_FLOOR;
                    cursor_position.Y++;
                    *(*(map + cursor_position.Y) + cursor_position.X) = TILE_CORRIDOR_FLOOR;
                }
                else {
                    cursor_position.Y--;
                    *(*(map + cursor_position.Y) + cursor_position.X) = TILE_CORRIDOR_FLOOR;
                    cursor_position.Y--;
                    *(*(map + cursor_position.Y) + cursor_position.X) = TILE_CORRIDOR_FLOOR;
                }
            }
        }
    }
    // draw rooms
    for (index_room = 0; index_room < ll_length(list_rooms); index_room++) {
        current_room_pointer = (ROOM*) ll_get(list_rooms, index_room);
        // draw the room floor
        for (
            X = current_room_pointer->rectangle.origin.X;
            X < current_room_pointer->rectangle.origin.X + current_room_pointer->rectangle.width;
            X++
        ) {
            for (
                Y = current_room_pointer->rectangle.origin.Y;
                Y < current_room_pointer->rectangle.origin.Y + current_room_pointer->rectangle.height;
                Y++
            ) {
                *(*(map + Y) + X) = TILE_ROOM_FLOOR;
            }
        }
        // draw the room walls and doors
        // -> for each tile around the room, if it's a corridor, then it's a door, otherwise it's a wall
        // draw the top and bottom walls
        for (
            X = current_room_pointer->rectangle.origin.X;
            X < current_room_pointer->rectangle.origin.X + current_room_pointer->rectangle.width;
            X++
        ) {
            // top wall
            if (*(*(map + current_room_pointer->rectangle.origin.Y - 1) + X) == TILE_CORRIDOR_FLOOR) {
                *(*(map + current_room_pointer->rectangle.origin.Y - 1) + X) = TILE_DOOR;
            }
            else if (*(*(map + current_room_pointer->rectangle.origin.Y - 1) + X) == TILE_FILL) {
                *(*(map + current_room_pointer->rectangle.origin.Y - 1) + X) = TILE_ROOM_WALL;
            }
            // bottom wall
            if (*(*(map + current_room_pointer->rectangle.origin.Y + current_room_pointer->rectangle.height) + X) == TILE_CORRIDOR_FLOOR) {
                *(*(map + current_room_pointer->rectangle.origin.Y + current_room_pointer->rectangle.height) + X) = TILE_DOOR;
            }
            else if (*(*(map + current_room_pointer->rectangle.origin.Y + current_room_pointer->rectangle.height) + X) == TILE_FILL) {
                *(*(map + current_room_pointer->rectangle.origin.Y + current_room_pointer->rectangle.height) + X) = TILE_ROOM_WALL;
            }
        }
        // draw the left and right walls
        for (
            Y = current_room_pointer->rectangle.origin.Y;
            Y < current_room_pointer->rectangle.origin.Y + current_room_pointer->rectangle.height;
            Y++
        ) {
            // left wall
            if (*(*(map + Y) + current_room_pointer->rectangle.origin.X - 1) == TILE_CORRIDOR_FLOOR) {
                *(*(map + Y) + current_room_pointer->rectangle.origin.X - 1) = TILE_DOOR;
            }
            else if (*(*(map + Y) + current_room_pointer->rectangle.origin.X - 1) == TILE_FILL) {
                *(*(map + Y) + current_room_pointer->rectangle.origin.X - 1) = TILE_ROOM_WALL;
            }
            // right wall
            if (*(*(map + Y) + current_room_pointer->rectangle.origin.X + current_room_pointer->rectangle.width) == TILE_CORRIDOR_FLOOR) {
                *(*(map + Y) + current_room_pointer->rectangle.origin.X + current_room_pointer->rectangle.width) = TILE_DOOR;
            }
            else if (*(*(map + Y) + current_room_pointer->rectangle.origin.X + current_room_pointer->rectangle.width) == TILE_FILL) {
                *(*(map + Y) + current_room_pointer->rectangle.origin.X + current_room_pointer->rectangle.width) = TILE_ROOM_WALL;
            }
        }
        // draw the corners
        // top left
        *(*(map + current_room_pointer->rectangle.origin.Y - 1) + current_room_pointer->rectangle.origin.X - 1) = TILE_ROOM_WALL;
        // top right
        *(*(map + current_room_pointer->rectangle.origin.Y - 1) + current_room_pointer->rectangle.origin.X + current_room_pointer->rectangle.width) = TILE_ROOM_WALL;
        // bottom left
        *(*(map + current_room_pointer->rectangle.origin.Y + current_room_pointer->rectangle.height) + current_room_pointer->rectangle.origin.X - 1) = TILE_ROOM_WALL;
        // bottom right
        *(*(map + current_room_pointer->rectangle.origin.Y + current_room_pointer->rectangle.height) + current_room_pointer->rectangle.origin.X + current_room_pointer->rectangle.width) = TILE_ROOM_WALL;
    }
}


COORD get_room_center_snapped(ROOM *room) {
    COORD room_center_snapped = get_room_center(room);
    if (room_center_snapped.X % 2 == 0) {
        // add or remove 1
        if (rand_range(0, 1) == 1) {room_center_snapped.X++;}
        else {room_center_snapped.X--;}
    }
    if (room_center_snapped.Y % 2 == 0) {
        if (rand_range(0, 1) == 1) {room_center_snapped.Y++;}
        else {room_center_snapped.Y--;}
    }
    return room_center_snapped;
}


void generate_things(GAME *game_state) {
    INDEX index_room, index_tile, random_number;
    short X, Y;
    ROOM *current_room_pointer;
    COORD current_coord;
    LIST list_free_coords = ll_create(sizeof(COORD));
    for (index_room = 0; index_room < ll_length(&game_state->list_rooms); index_room++) {
        current_room_pointer = (ROOM*) ll_get(&game_state->list_rooms, index_room);
        // list the coordinates of all the free tiles of the room
        for (
            X = current_room_pointer->rectangle.origin.X;
            X < current_room_pointer->rectangle.origin.X + current_room_pointer->rectangle.width;
            X++
        ) {
            for (
                Y = current_room_pointer->rectangle.origin.Y;
                Y < current_room_pointer->rectangle.origin.Y + current_room_pointer->rectangle.height;
                Y++
            ) {
                // add the tile coordinates to the list if it is free
                if (*(*(game_state->map_things + Y) + X) == THING_NONE) {
                    current_coord.X = X;
                    current_coord.Y = Y;
                    ll_append(&list_free_coords, &current_coord);
                }
            }
        }
        // place gold coins
        // generate a random number between 0 and 99
        random_number = rand_range(0, 99);
        if ((random_number >= CHANCE_0_GOLD) && (random_number < CHANCE_0_GOLD + CHANCE_1_GOLD)) {
            // spawn a coin in the room
            index_tile = rand_range(0, ll_length(&list_free_coords) - 1);
            current_coord = *(COORD*) ll_get(&list_free_coords, index_tile);
            *(*(game_state->map_things + current_coord.Y) + current_coord.X) = THING_GOLD;
            // remove the tile from the list of free tiles
            ll_remove(&list_free_coords, index_tile);
        }
        else if (random_number >= CHANCE_0_GOLD + CHANCE_1_GOLD) {
            // spawn 2 coins in the room
            index_tile = rand_range(0, ll_length(&list_free_coords) - 1);
            current_coord = *(COORD*) ll_get(&list_free_coords, index_tile);
            *(*(game_state->map_things + current_coord.Y) + current_coord.X) = THING_GOLD;
            ll_remove(&list_free_coords, index_tile);
            index_tile = rand_range(0, ll_length(&list_free_coords) - 1);
            current_coord = *(COORD*) ll_get(&list_free_coords, index_tile);
            *(*(game_state->map_things + current_coord.Y) + current_coord.X) = THING_GOLD;
            ll_remove(&list_free_coords, index_tile);
        }
        if ((current_room_pointer->flags & (FLAG_ROOM_SPAWN_PLAYER | FLAG_ROOM_SPAWN_STAIRS)) != 0) {
            // choose a random free tile within the room and place the player or the stairs there
            index_tile = rand_range(0, ll_length(&list_free_coords) - 1);
            current_coord = *(COORD*) ll_get(&list_free_coords, index_tile);
            if ((current_room_pointer->flags & FLAG_ROOM_SPAWN_PLAYER) != 0) {
                game_state->player.position = current_coord;
            }
            else {
                *(*(game_state->map_things + current_coord.Y) + current_coord.X) = THING_STAIRS;
            }
        }
        // empty the list of free coords
        ll_free(&list_free_coords);
    }
}

// good source code example: https://github.com/Davidslv/rogue/tree/master
// no flickerfing screen: https://stackoverflow.com/questions/34842526/update-console-without-flickering-c
// procedural dungeon creation: https://github.com/pippinbarr/chogue/blob/master/Process/resources/Mark%20Damon%20Hughes%20-%20Game%20Design%20-%20Article%2007%20-%20Roguelike%20Dungeon%20Generation.pdf
// https://donjon.bin.sh/code/dungeon/
// https://weblog.jamisbuck.org/2011/1/12/maze-generation-recursive-division-algorithm.html
// https://www.reddit.com/r/roguelikedev/comments/6df0aw/my_implementation_of_a_bunch_of_dungeon_algorithms/
// https://journal.stuffwithstuff.com/2014/12/21/rooms-and-mazes/
// https://www.reddit.com/r/roguelikedev/comments/2brhl8/comment/cj87umz/
// https://www.odedwelgreen.com/karcero/
// https://www.gamedeveloper.com/programming/procedural-dungeon-generation-algorithm#close-modal

#include "main.h"


int main() {

    GAME game_state;
    BOOL quit_game;

    // init the random number generator
    init_rand();

    // start the console window
    init_window();

    // init the game state
    init_game_state(&game_state);
    // clear the screen
    cls();

    quit_game = FALSE;
    // while the game is not over exited ...
    while (!quit_game) {
        game_state.level_counter++;
        // generate a new dungeon map
        generate_dungeon(&game_state);
        // clear the fog of war in the player spawning room
        update_fow(&game_state);
        // draw the map on the screen matrix
        draw_game_on_screen(&game_state);
        // display the screen
        update_screen(&game_state);
        // play the level
        quit_game = play_level(&game_state);
    }

    cls();
    return EXIT_SUCCESS;
}

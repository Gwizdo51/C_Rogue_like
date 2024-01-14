#include "utils.h"


/*
Initialises the random number generator
*/
void init_rand() {
    short i;
    // set a random seed
    srand((unsigned int) time(NULL));
    // generate some random numbers to break the patterns
    for (i = 0; i < 100; i++) {
        rand();
    }
}


/*
Returns a random number between 2 boundaries (included)
*/
INDEX rand_range(INDEX min, INDEX max) {
    return (INDEX) rand() % (max - min + 1) + min;
}


/*
Returns a random odd number between 2 boundaries (included if odds)
*/
INDEX rand_odd_range(INDEX min, INDEX max) {
    INDEX result;
    // if min is even, add 1 to it
    if (min % 2 == 0) {
        min++;
    }
    // if max is even, remove 1 to it
    if (max % 2 == 0) {
        max--;
    }
    result = (rand() % ((max - min) / 2 + 1)) * 2 + min;
    return result;
}

/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
	int i;
    int seed = 1000;
    int numPlayer = 2;
    int r;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
  
    int response;

    printf ("TESTING isGameOver():\n");
    
#if (NOISY_TEST == 1)
    printf("Test IsGameOver() Returns True with > 2 Supply Piles Empty\n");
#endif

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
    for (i = 0; i < 27; i++) {
	    G.supplyCount[i] = 10;
    }

    for (i = 0; i < 3; i++) {
	    G.supplyCount[i] = 0;
    }
    
    response = isGameOver(&G);
    assert(response == 1);

#if (NOISY_TEST == 1)
    printf("Test IsGameOver() Returns True with Province Piles Empty\n");
#endif
    response = 0;
    G.supplyCount[province] = 0;

    response = isGameOver(&G);
    assert(response == 1);

#if (NOISY_TEST == 1)
    printf("Test IsGameOver() Returns False with < 3 Piles Empty\n");
#endif
    response = 0;
    G.supplyCount[curse] = 1;
    G.supplyCount[province] = 1;
    G.supplyCount[duchy] = 0;
    G.supplyCount[estate] = 0;

    response = isGameOver(&G);
    assert(response == 0);
    
    printf("All tests passed!\n");

    return 0;
}

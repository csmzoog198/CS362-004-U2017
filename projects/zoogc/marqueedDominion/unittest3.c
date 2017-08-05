/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
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
    int p, r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState Before;
    struct gameState After;

    int response;

    int sameFlag = 0;
    int differentFlag = 0;


    printf ("TESTING shuffle():\n");
    for (p = 0; p < numPlayer; p++)
    {

#if (NOISY_TEST == 1)
	    printf("Test Shuffle With Empty Deck\n");
#endif
	    memset(&Before, 23, sizeof(struct gameState));   // clear the game states
	    memset(&After, 23, sizeof(struct gameState));   // clear the game states
	    r = initializeGame(numPlayer, k, seed, &Before); // initialize a new game
	    r = initializeGame(numPlayer, k, seed, &After); // initialize a new game
	    After.handCount[p] = handCount;                 // set the number of cards on hand

	    After.deckCount[p] = 0;


	    response = shuffle(p, &After);

	    assert(response == -1);

	    After.deckCount[p] = Before.deckCount[p];		// Reset Deck Count
    }

#if (NOISY_TEST == 1)
    printf("Compare Deck Positions Before and After\n"); 
#endif

    shuffle(0, &After);
    shuffle(0, &After);

    for (i = 0; i < After.deckCount[0]; i++) {

	    if (After.deck[0][i] == Before.deck[0][i]) {
		    sameFlag += 1;
	    }
	    
	    else {
		    differentFlag += 1;
	    }
    }
    
    assert(differentFlag > 0);
    
    printf("All tests passed!\n");

    return 0;
}

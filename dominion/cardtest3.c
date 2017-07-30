/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
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

    // array of all cards
    int hand[5] = {adventurer, smithy, village, great_hall, treasure_map};

    int seed = 1000;
    int numPlayer = 2;
    int r, handCount;
    int k[10] = { adventurer, council_room, feast, gardens, mine
	    , remodel, smithy, village, baron, great_hall };
    struct gameState Before;
    struct gameState After;

    int sameFlag = 0;
    int differentFlag = 0;

    printf("TESTING villageFunction():\n");

#if (NOISY_TEST == 1)
	    printf("Test Current Player Should Recieve Exactly 1 Card\n");
#endif
	    memset(&Before, 23, sizeof(struct gameState));   // clear the game states
	    memset(&After, 23, sizeof(struct gameState));   // clear the game states
	    r = initializeGame(numPlayer, k, seed, &Before); // initialize a new game
	    r = initializeGame(numPlayer, k, seed, &After); // initialize a new game
	    for (i = 0; i < 5; i++) {
		    Before.hand[0][i] = hand[i];
		    After.hand[0][i] = hand[i];
	    }
	    
	   
	    After.handCount[0] = handCount;                 // set the number of cards on hand
	    Before.handCount[0] = handCount;

	    greatHallFunction(&After, 3);

	    if (Before.handCount[0] != After.handCount[0]) {
		    printf("BUG: Card count off!\n");
		    sameFlag += 1;
	    }

#if (NOISY_TEST == 1)
	    printf("Current Player Should Receive 2 Actions\n");
#endif
	    if (Before.numActions != After.numActions + 2) {
		    printf("BUG: Action count off!\n");
		    sameFlag += 1;
	    }
	    
	      
#if (NOISY_TEST == 1)
    printf("1 Cards Should Be Taken From Player's Pile\n");
#endif
    if (Before.deckCount[0] != After.deckCount[0] + 1) {
	    printf("BUG: Deck count off!\n");
	    sameFlag += 1;
    }


#if (NOISY_TEST == 1)
    printf("No State Change in Opponent.\n", 28, -1);
#endif
    for (i = 0; i < 5; i++) {
	    assert(Before.hand[1][i] == After.hand[1][i]);
	    assert(Before.handCount[1] == After.handCount[1]);
    }
    

#if (NOISY_TEST == 1)
    printf("No State Change to Victory Cards or Kingdom Cards.\n");
#endif
    for (i = 0; i < 27; i++) {
	    assert(Before.supplyCount[i] == After.supplyCount[i]);
    }

#if (NOISY_TEST == 1)
    printf("HandCount Should Remain The Same.\n");
#endif
    
    if (Before.handCount[0] != After.handCount[0]) {
	    printf("BUG: Hand count off!\n");
	    sameFlag += 1;
    }

    if (sameFlag == 0) {
	    printf("All tests passed!\n");
    }
    else {
	    printf("BUGS FOUND!\n");
    }
    

    return 0;
}

/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
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
    int cost;

    // array of all cards
    int cards[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
    int costs[27] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};

    printf ("TESTING getCost():\n");
    
#if (NOISY_TEST == 1)
    for (i = 0; i < 27; i++) {
	    printf("Testing card %d with cost %d.\n", cards[i], costs[i]);
	    cost = getCost(cards[i]);
	    assert(costs[i] == cost);
    }
#endif


#if (NOISY_TEST == 0)
    for (i = 0; i < 27; i++) {
	    cost = getCost(cards[i]);
	    assert(costs[i] == cost);
    }
#endif
    

#if (NOISY_TEST == 1)
    printf("Low Boundary: Testing invalid card %d with cost %d.\n", -1, -1);
#endif
    cost = getCost(-1);
    assert(cost == -1);


#if (NOISY_TEST == 1)
    printf("High Boundary: Testing invalid card %d with cost %d.\n", 28, -1);
#endif
    cost = getCost(28);
    assert(cost == -1);

    printf("All tests passed!\n");

    return 0;
}

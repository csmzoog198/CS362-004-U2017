// This File Contains a Random Test Generator for the Village
// card belonging to the Dominion card game.

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {

	// Seed Random Generator
	srand(time(NULL));

	struct gameState stateAfter;
	struct gameState stateBefore;
	memset(&stateBefore, 23, sizeof(struct gameState));   // clear the game states
	memset(&stateAfter, 23, sizeof(struct gameState));   // clear the game states

	int card = village;
	int choice1 = rand() % 5 + 1;
	int choice2 = rand() % 5 + 1;
	int choice3 = rand() % 5 + 1;
	int handpos = 1;
	int z = 0;
	int *bonus;
	bonus = &z;

	int i;
	int j;
	int n;
	int p;

	int errorFlag = 0;

	for (n = 0; n < 2000; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&stateAfter)[i] = (rand() % 256);
		}
		p = floor(rand() % 2);
		stateAfter.numPlayers = 2;
		stateAfter.deckCount[p] = floor(rand() % 500);
		stateAfter.discardCount[p] = floor(rand() % 500);
		stateAfter.handCount[p] = floor(rand() % 5 + 1);
		stateAfter.numActions = 1;
		stateAfter.playedCardCount = rand() % 500;
		for (i = 0; i <= stateAfter.playedCardCount; i++) {
			stateAfter.playedCards[i] = rand() % 27;
		}
		stateAfter.whoseTurn = p;
		for (i = 0; i < 5; i++) {
			stateAfter.hand[p][i] = rand() % 27;
		}
		stateAfter.hand[p][1] = 14;


		stateBefore = stateAfter;

		printf("Iteration %d\n", n);
		printf("Card: %d\n", card);
		printf("Choice 1: %d\n", choice1);
		printf("Choice 2: %d\n", choice2);
		printf("Choice 3: %d\n", choice3);
		printf("Hand Pos: %d\n", handpos);
		printf("Bonus: %d\n", *bonus);
		//printf("Hand Pos: %d\n", handpos);


		// Call cardEffect
		cardEffect(card, choice1, choice2, choice3, &stateAfter, handpos, bonus);

// Compare State After to State Before (Tests)

		// Test - Player's Hand Count Remains the Same (Draw + Discard cancel out)
		if (stateAfter.handCount[p] == stateBefore.handCount[p]) {
			printf("TEST - Player's Hand Count Has Not Changed - PASSED\n");
		}
		else {
			printf("TEST - Player's Hand Count Has Not Changed - FAILED\n");
			errorFlag = 1;
		}

		// Test - Player's Deck Decreases By 1
		if (stateAfter.deckCount[p] == (stateBefore.deckCount[p] - 1)) {
			printf("TEST - Player's Deck Count Has Decreased By 1 - PASSED\n");
		}
		else {
			printf("TEST - Player's Deck Count Has Decreased By 1 - FAILED\n");
			errorFlag = 1;
		}

		// Test - Player's Played Card Count Increases By 1
		if (stateAfter.playedCardCount == (stateBefore.playedCardCount + 1)) {
			printf("TEST - Player's Played Card Count Has Increased By 1 - PASSED\n");
		}
		else {
			printf("TEST - Player's Played Card Count Has Increased By 1 - FAILED\n");
			errorFlag = 1;
		}

		// Test - Player's Actions Increase By 2
		if (stateAfter.numActions == (stateBefore.numActions + 2)) {
			printf("TEST - Player's Action Count Has Increased By 2 - PASSED\n");
		}
		else {
			printf("TEST - Player's Action Count Has Increased By 2 - FAILED\n");
			errorFlag = 1;
		}

		// Test - No Change to Victory Cards or Treasure Cards
		for (j = 0; j < 7; j++) {
			if (stateAfter.supplyCount[j] == stateBefore.supplyCount[j]) {
				printf("TEST - No Change To Card %d - PASSED\n", j);
			}
			else {
				printf("TEST - No Change To Card %d - FAILED\n", j);
				errorFlag = 1;
			}
		}


		// Test - No Change to Other Player's Deck
		if (stateAfter.deckCount[(p + 1) % 2] == (stateBefore.deckCount[(p + 1) % 2])) {
			printf("TEST - Opponet's Deck Has Not Changed - PASSED\n");
		}
		else {
			printf("TEST - Opponet's Deck Has Not Changed - FAILED\n");
			errorFlag = 1;
		}

		// Test - No Change to Other Player's Hand
		if (stateAfter.handCount[(p + 1) % 2] == (stateBefore.handCount[(p + 1) % 2])) {
			printf("TEST - Opponet's Hand Has Not Changed - PASSED\n");
		}
		else {
			printf("TEST - Opponet's Hand Has Not Changed - FAILED\n");
			errorFlag = 1;
		}

		// Test - No Change to Other Player's Discard
		if (stateAfter.discardCount[(p + 1) % 2] == (stateBefore.discardCount[(p + 1) % 2])) {
			printf("TEST - Opponet's Discard Has Not Changed - PASSED\n\n");
		}
		else {
			printf("TEST - Opponet's Discard Has Not Changed - FAILED\n\n");
			errorFlag = 1;
		}

	}

	if (errorFlag == 0) {
		printf("ALL TESTS PASSED\n\n");
	}
	else {
		printf("ERROR - SOME TESTS FAILED\n\n");
	}


	return 0;
}
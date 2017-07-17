/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
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
	int j;

	int curseFlag = 0;
	int provinceFlag = 0;
	int treasureFlag = 0;
	int nonsenseFlag = 0;
	int bugFlag = 0;
	int duplicateFlag = 0;
	int testFlag = 0;

	int* randArray1 = malloc(10 * sizeof(int));
	int* randArray2 = malloc(10 * sizeof(int));
	int* randArray3 = malloc(10 * sizeof(int));
	int* randArray4 = malloc(10 * sizeof(int));

	int* usedNumbs = malloc(5 * sizeof(int));

	int* arrayReturned1 = malloc(10 * sizeof(int));
	int* arrayReturned2 = malloc(10 * sizeof(int));
	int* arrayReturned3 = malloc(10 * sizeof(int));
	int* arrayReturned4 = malloc(10 * sizeof(int));


	for (i = 0; i < 10; i++) {
		randArray1[i] = i;
	}

	for (i = 0; i < 10; i++) {
		randArray2[i] = i + 10;
	}

	for (i = 0; i < 10; i++) {
		randArray3[i] = (i + 20) % 27;
	}

	for (i = 0; i < 10; i++) {
		randArray4[i] = i % 5;
	}

	printf("TESTING kingdomCards():\n");

#if (NOISY_TEST == 1)
	printf("Test if KingdomCards() Only Accepts Valid Cards\n");
#endif
	arrayReturned1 = kingdomCards(randArray1[0], randArray1[1], randArray1[2], randArray1[3], randArray1[4], randArray1[5], randArray1[6], randArray1[7], randArray1[8], randArray1[9]);
	for (i = 0; i < 10; i++) {
		if (arrayReturned1[i] == 0) {
			curseFlag = 1;
		}
		else if (arrayReturned1[i] > 0 && arrayReturned1[i] < 4) {
			provinceFlag = 1;
		}

		else if (arrayReturned1[i] > 4 && arrayReturned1[i] < 7) {
			treasureFlag = 1;
		}

		else if (arrayReturned1[i] > 0 || arrayReturned1[i] < 26) {
			nonsenseFlag = 1;
		}
	}

	if (curseFlag == 1) {
		bugFlag = 1;
		printf("BUG: KingdomCards() accepts Curse Cards\n");
	}

	if (provinceFlag == 1) {
		bugFlag = 1;
		printf("BUG: KingdomCards() accepts Territory Cards\n");
	}

	if (treasureFlag == 1) {
		bugFlag = 1;
		printf("BUG: KingdomCards() accepts Treasure Cards\n");
	}

	if (curseFlag == 1) {
		bugFlag = 1;
		printf("BUG: KingdomCards() accepts Curse Cards\n");
	}

	if (bugFlag == 0) {
		printf("Input Test Passed - KingdomCards() Only Accepts Valid Input\n");
	}

	else if (bugFlag == 1) {
		testFlag == 1;
	}

	bugFlag = 0;		// Reset Bug Flag

#if (NOISY_TEST == 1)
	printf("Test if KingdomCards() Places Cards At Correct Location\n");
#endif
	arrayReturned1 = kingdomCards(randArray1[0], randArray1[1], randArray1[2], randArray1[3], randArray1[4], randArray1[5], randArray1[6], randArray1[7], randArray1[8], randArray1[9]);
	arrayReturned2 = kingdomCards(randArray2[0], randArray2[1], randArray2[2], randArray2[3], randArray2[4], randArray2[5], randArray2[6], randArray2[7], randArray2[8], randArray2[9]);
	arrayReturned3 = kingdomCards(randArray3[0], randArray3[1], randArray3[2], randArray3[3], randArray3[4], randArray3[5], randArray3[6], randArray3[7], randArray3[8], randArray3[9]);
	for (i = 0; i < 10; i++) {
		if (arrayReturned1[i] != randArray1[i]) {
			bugFlag = 1;
		}

		if (arrayReturned2[i] != randArray2[i]) {
			bugFlag = 1;
		}

		if (arrayReturned3[i] != randArray3[i]) {
			bugFlag = 1;
		}
	}

	if (bugFlag == 0) {
		printf("Input Test Passed - KingdomCards() Places Cards At Correct Locations\n");
	}

	else if (bugFlag == 1) {
		testFlag = 1;
	}

	bugFlag = 0;

#if (NOISY_TEST == 1)
	printf("Test if KingdomCards() Accepts Duplicate Cards\n");
#endif
	arrayReturned4 = kingdomCards(randArray4[0], randArray4[1], randArray4[2], randArray4[3], randArray4[4], randArray4[5], randArray4[6], randArray4[7], randArray4[8], randArray4[9]);
	for (i = 0; i < 10; i++) {
		duplicateFlag = 0;
		for (j = 0; j < 5; j++) {
			if (arrayReturned4[i] == usedNumbs[j]) {
				duplicateFlag = 1;
			}
		}

		if (duplicateFlag = 1) {
			bugFlag = 1;
		}

		if (duplicateFlag == 0) {
			usedNumbs[i % 5] = arrayReturned4[i];
		}
	}

	if (bugFlag == 0) {
		printf("Input Test Passed - KingdomCards() Does Not Accept Duplicate Cards\n");
	}

	else if (bugFlag == 1) {
		testFlag = 1;
		printf("BUG: KingdomCards() Accepts Duplicate Cards\n");
	}

	bugFlag = 0;

#if (NOISY_TEST == 1)
	printf("Test if KingdomCards() Returns Correct Array\n");
#endif
	arrayReturned1 = kingdomCards(randArray1[0], randArray1[1], randArray1[2], randArray1[3], randArray1[4], randArray1[5], randArray1[6], randArray1[7], randArray1[8], randArray1[9]);
	arrayReturned2 = kingdomCards(randArray2[0], randArray2[1], randArray2[2], randArray2[3], randArray2[4], randArray2[5], randArray2[6], randArray2[7], randArray2[8], randArray2[9]);
	arrayReturned3 = kingdomCards(randArray3[0], randArray3[1], randArray3[2], randArray3[3], randArray3[4], randArray3[5], randArray3[6], randArray3[7], randArray3[8], randArray3[9]);
	for (i = 0; i < 10; i++) {
		if (arrayReturned1[i] != randArray1[i]) {
			bugFlag = 1;
		}

		if (arrayReturned2[i] != randArray2[i]) {
			bugFlag = 1;
		}

		if (arrayReturned3[i] != randArray3[i]) {
			bugFlag = 1;
		}
	}

	if (bugFlag == 0) {
		printf("Input Test Passed - KingdomCards() Returns Correct Array\n");
	}

	else if (bugFlag == 1) {
		printf("BUG: KingdomCards() Returns Incorrect Array\n");
	}

	if (testFlag == 0) {
		printf("All tests passed!\n");
		return 0;
	}
	else if (testFlag == 1) {
		printf("BUG: SOME TESTS FAILED!\n");
		return -1;
	}
}

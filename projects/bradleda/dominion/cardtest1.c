#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>


int failCounter = 0;

void assertTrue(int x, int y) {
	if(x == y) {
		printf("TEST SUCCESSFULLY COMPLETED\n");
	}

	else {
		printf("TEST FAILED");
		failCounter++;
	}
}


// Testing adventurer Function

int main() {

	int i, j, k;
	int seed = 2000;
	int handpos, choice1, choice2, choice3, bonus = 0;
	int remove1, remove2;
	int newCards = 0;
	int discarded = 1;
	int extraCoins = 0;
	int shuffledCards = 0;
	int playerCount = 2;
	int player = 0;
	int test = 0;
	int treasure, treasure_test = 0;

	struct gameState gameState, testState;


	int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, 
						great_hall, smithy, council_room};


	// Set the state of the game to empty
	printf("\nTESTING: playAdventurer()\n");
	memset(&gameState, 23, sizeof(struct gameState));
	memset(&testState, 23, sizeof(struct gameState));

	initializeGame(playerCount, kingdom, seed, &gameState);
	memcpy(&testState, &gameState, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &gameState, handpos, &bonus);
	printf("\nPlayer 1 gains 2 cards\n");
	assertTrue(gameState.handCount[0], testState.handCount[0] + 2);

	for(i = 0; i < gameState.handCount[0]; i++) {
		test = gameState.hand[0][i];

		if(test == copper || test == silver || test == gold)
			treasure++;
	}


	printf("\nPlayer 1 gets 2 treasure cards:");
	assertTrue(treasure_test + 2, treasure);


	printf("\nTest that victory card piles are same in both game states\n");
	assertTrue(gameState.supplyCount[province], testState.supplyCount[province]);
	assertTrue(gameState.supplyCount[duchy], testState.supplyCount[duchy]);
	assertTrue(gameState.supplyCount[estate], testState.supplyCount[estate]);

	printf("\nTest there was no changes to kingdom card piles\n");
	for(i = 0; i < 10; i++) {
		assertTrue(gameState.supplyCount[kingdom[i]], testState.supplyCount[kingdom[i]]);
	}

	printf("\nTest that player 1's hand and deck count were not affected\n");
	assertTrue(gameState.handCount[0], testState.handCount[0]);
	assertTrue(gameState.deckCount[0], testState.deckCount[0]);


	if(failCounter) 
		printf("\nFAILED TEST\n");
	else
		printf("\nSUCCESSFUL TEST\n");


	return 0;

}
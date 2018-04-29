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
		printf("TEST FAILED\n");
		failCounter++;
	}
}


// Testing Smithy Function

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
	printf("\nTESTING: playSmithy()\n");
	memset(&gameState, 23, sizeof(struct gameState));
	memset(&testState, 23, sizeof(struct gameState));

	initializeGame(playerCount, kingdom, seed, &gameState);
	memcpy(&testState, &gameState, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &gameState, handpos, &bonus);

	printf("\nIncrease player 1's card count by 3\n");
	assertTrue(gameState.handCount[0], testState.deckCount[0] + 2);

	printf("\nDecrease player 1's deck count by 3");
	assertTrue(gameState.deckCount[0], testState.deckCount[0] - 3);

	printf("\nCheck that there was no change to the victory card piles\n");
	assertTrue(gameState.supplyCount[province], testState.supplyCount[province]);
	assertTrue(gameState.supplyCount[duchy], testState.supplyCount[duchy]);
	assertTrue(gameState.supplyCount[estate], testState.supplyCount[estate]);


	printf("\nCheck to see if the player's hands were affected\n");
	assertTrue(gameState.handCount[0], testState.handCount[0]);
	assertTrue(gameState.deckCount[0], testState.deckCount[0]);

	if(failCounter) 
		printf("\nFAILED TEST\n");
	else
		printf("\nSUCCESSFUL TEST\n");


	return 0;

}

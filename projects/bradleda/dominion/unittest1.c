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


// Testing isGameOver Function

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

	struct gameState state, testState;
	int pre = 0;
	int post = 0;

	int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, 
						great_hall, smithy, council_room};


	// Set the state of the game to empty
	printf("\nTESTING: isGameOver()\n");
	memset(&state, 23, sizeof(struct gameState));
	initializeGame(playerCount, kingdom, seed, &state);


	// Make sure the province cards are empty, and check to
	// see if the game returns true as being over
	printf("\nSetting province cards to be empty\n");
	state.supplyCount[province] = 0;
	assertTrue(isGameOver(&state), 1);


	// Make the supply piles empty, and check to 
	// see if the game returns true as being over
	printf("\nSetting supply piles to be empty\n");
	state.supplyCount[province] = 1;
	state.supplyCount[0] = 0;
	state.supplyCount[1] = 0;
	state.supplyCount[2] = 0;
	assertTrue(isGameOver(&state), 1);


	// Set the supply piles to contain cards, and check to 
	// see if the game returns false as being over
	printf("\nSetting supply piles to not be empty\n");
	state.supplyCount[0] = 1;
	state.supplyCount[1] = 1;
	state.supplyCount[2] = 1;
	assertTrue(isGameOver(&state), 0);


	if(failCounter) 
		printf("\nFAILED TEST\n");
	else
		printf("\nSUCCESSFUL TEST\n");


	return 0;


}




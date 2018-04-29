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


// Testing getCost Function

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

	struct gameState gameState, testState;


	int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, 
						great_hall, smithy, council_room};


	// Set the state of the game to empty
	printf("\nTESTING: getCost()\n");
	memset(&gameState, 23, sizeof(struct gameState));
	initializeGame(playerCount, kingdom, seed, &gameState);

	// Testing values that are valid
	printf("\nTesting 3 correct values\n");
	
	//estate
	test = 1;
	assertTrue(getCost(test), 2);

	//adventurer
	test = 7;
	assertTrue(getCost(test), 6);

	//curse
	test = 0;
	assertTrue(getCost(test), 0);

	// Testing values that are invalid
	printf("\nTesting 1 incorrect value that should return FAIL, and 1 invalid value that should return SUCCESS:\n");
	
	//feast
	test = 9;
	assertTrue(getCost(test), 9);

	//invalid
	test = -1;
	assertTrue(getCost(test), -1);


	if(failCounter) 
		printf("\nFAILED TEST\n");
	else
		printf("\nSUCCESSFUL TEST\n");


	return 0;

}
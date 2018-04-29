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
	printf("\nTESTING: gainCard()\n");
	memset(&gameState, 23, sizeof(struct gameState));
	initializeGame(playerCount, kingdom, seed, &gameState);



	printf("\nTesting: Empty gold supply\n");
	gameState.supplyCount[gold] = 0;
	assertTrue(gainCard(gold, &gameState, 0, 0), -1);
	
	printf("\nRESET GOLD\n");
	gameState.supplyCount[gold] = 30;

	printf("\nTesting: Adding a card to the deck\n");
	test = gameState.deckCount[0];	
	gainCard(gold, &gameState, 1, 0);
	assertTrue(test + 1, gameState.deckCount[0]);

	printf("\nTesting: Adding a card to the deck\n");
	test = gameState.handCount[0];
	gainCard(gold, &gameState, 2, 0);
	assertTrue(test + 1, gameState.handCount[0]);


	printf("\nTesting: Adding a card to the discard pile\n");
	test = gameState.discardCount[0];
	gainCard(gold, &gameState, 0 , 0);
	assertTrue(test + 1, gameState.discardCount[0]);

	printf("\nTesting: Lessen gold count\n");
	test = gameState.supplyCount[gold];
	gainCard(gold, &gameState, 0 , 0);
	assertTrue(test - 1, gameState.supplyCount[gold]);



	if(failCounter) 
		printf("\nFAILED TEST\n");
	else
		printf("\nSUCCESSFUL TEST\n");


	return 0;

}
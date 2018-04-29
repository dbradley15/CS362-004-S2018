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


// Testing Shuffle Function

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

	struct gameState gameState, testState;
	int pre = 0;
	int post = 0;

	int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, 
						great_hall, smithy, council_room};

	printf("\nTESTING: shuffle()\n");

	//Set an empty state
	memset(&gameState, 23, sizeof(struct gameState));
	initializeGame(playerCount, kingdom, seed, &gameState);

	//Set deck count to be 0
	printf("\nDeck count is at 0\n");
	gameState.deckCount[player] = 0;
	assertTrue(shuffle(player, &gameState), -1);


	//-------------------------Test-----------------------------------


	//Test to see the deck is the same size before and after the shuffle
	printf("\nDeck count is 10 before and after shuffle\n");
	gameState.deckCount[player] = 10;
	shuffle(player, &gameState);
	assertTrue(gameState.deckCount[player], 10);


	printf("\nShuffle the cards\n");
	pre = gameState.deck[player][0];
	shuffle(player, &gameState);
	post = gameState.deck[player][0];

	if(pre != post)
		assertTrue(1, 1);
	else
		assertTrue(0, 1);

	if(failCounter) 
		printf("\nFAILED TEST\n");
	else
		printf("\nSUCCESSFUL TEST\n");


	return 0;

}



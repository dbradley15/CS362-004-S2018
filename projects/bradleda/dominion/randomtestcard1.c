#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>



int effectFailCounter, discardFailCounter, drawFailCounter, deckFailCounter = 0;


void testSmithy(int currentPlayer, struct gameState * altered) {

	int bonus = 0;
	int effect =  0;
	int a, b, c = 0;
	int discard =  0;
	struct gameState original;

	memcpy(&original, altered, sizeof(struct gameState));

	effect = cardEffect(smithy, 0, 0, 0, altered, 0, &bonus);
	a = drawCard(currentPlayer, &original);
	b = drawCard(currentPlayer, &original);
	c = drawCard(currentPlayer, &original);
	discard = discardCard(0, currentPlayer, &original, 0);


	int alteredHandCount = altered->handCount[currentPlayer];
	int alteredDeckCount = altered->deckCount[currentPlayer];
	int originalHandCount = original.handCount[currentPlayer];
	int originalDeckCount = original.deckCount[currentPlayer];

	if(a == -1 && original.deckCount[currentPlayer] != 0)
		drawFailCounter++;

	if(b == -1 && original.deckCount[currentPlayer] != 0)
		drawFailCounter++;

	if(c == -1 && original.deckCount[currentPlayer] != 0)
		drawFailCounter++;


	if(!(effect == 0 && discard == 0)) {

		if(effect)
			effectFailCounter++;

		if(discard)
			discardFailCounter++;
	}


	if(alteredHandCount != originalHandCount || alteredDeckCount != originalDeckCount)
		deckFailCounter++;

}



int main() {

	srand(time(NULL));
	int i, j = 0;
	int currentPlayer = 0;

	struct gameState state;

	printf("\nTESTING: smithy\n");


	for(i ; i < 10000; i++) {
		for(j; j < sizeof(struct gameState); j++) {
			((char*)&state)[i] = floor(Random() * 256);
		}

		currentPlayer = floor(Random() * MAX_PLAYERS);
		state.deckCount[currentPlayer] = floor(Random() * MAX_DECK);
		state.discardCount[currentPlayer] = floor(Random() * MAX_DECK);
		state.handCount[currentPlayer] = floor(Random() * MAX_HAND);
		state.playedCardCount = floor(Random() * (MAX_DECK - 1));
		state.whoseTurn = currentPlayer;

		testSmithy(currentPlayer, &state);

	}

	int failCount = effectFailCounter + discardFailCounter + drawFailCounter + deckFailCounter;

	if(failCount == 0)
		printf("\n TEST PASSED \n");

	else {

		printf("\n TEST FAILED \n");
		printf("Effect Card Failed %d times\n", effectFailCounter);
		printf("Discard Failed %d times\n", discardFailCounter);
		printf("Draw Card Failed %d times\n", drawFailCounter);
		printf("Card Count Failed %d times\n", deckFailCounter);

	}

	return 0;
}

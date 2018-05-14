#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

// Village increases actions by 2 and allows you to draw a card

int effectFailCounter, discardFailCounter, drawFailCounter, deckFailCounter, actionFailCounter = 0;
int playerFail = 0;


void testVillage(int currentPlayer, struct gameState * altered) {

	int bonus = 0;
	int effect =  0;
	int a, b, c, d, i, j = 0;
	int discard = 0;
	struct gameState original;

	memcpy(&original, altered, sizeof(struct gameState));

	printf("passed memcpy\n");

	effect = cardEffect(village, 0, 0, 0, altered, 0, &bonus);
	a = drawCard(currentPlayer, &original);
    original.numActions += 2;
    
    // Simulate drawing cards for each player
    for(i; i < original.numPlayers; i++) {
        if(i != currentPlayer) {
            j = drawCard(i, &original);
            
            if(j == -1 && original.deckCount[i] != 0) {
                drawFailCounter++;
            }
        }
    }

	printf("passed fail counter test\n");
    
	discard = discardCard(0, currentPlayer, &original, 0);


	int alteredHandCount = altered->handCount[currentPlayer];
	int alteredDeckCount = altered->deckCount[currentPlayer];
	int originalHandCount = original.handCount[currentPlayer];
	int originalDeckCount = original.deckCount[currentPlayer];
    
    
    if(original.numActions != altered->numActions)
        actionFailCounter++;

	if(a == -1 && original.deckCount[currentPlayer] != 0)
		drawFailCounter++;



	if(!(effect == 0 && discard == 0)) {

		if(effect)
			effectFailCounter++;

		if(discard)
			discardFailCounter++;
	}


	if(alteredHandCount != originalHandCount || alteredDeckCount != originalDeckCount)
		deckFailCounter++;
    
    
    for(i = 0; i < original.numPlayers; i++) {
        if(i != currentPlayer) {
            if(!(altered->handCount[i] == original.handCount[i] && altered->deckCount[i] == original.deckCount[i])) {
                playerFail++;
            }
        }
    }

}



int main() {

	srand(time(NULL));
	int i, j = 0;
	int currentPlayer = 0;

	struct gameState state;

	printf("\nTESTING: village\n");


	for(i = 0 ; i < 10000; i++) {
		for(j = 0; j < sizeof(struct gameState); j++) {
			((char*)&state)[j] = floor(Random() * 256);
		}

	printf("in main loop for-loop\n");
		currentPlayer = floor(Random() * MAX_PLAYERS);
		state.deckCount[currentPlayer] = floor(Random() * MAX_DECK);
		state.discardCount[currentPlayer] = floor(Random() * MAX_DECK);
		state.handCount[currentPlayer] = floor(Random() * MAX_HAND);
		state.playedCardCount = floor(Random() * (MAX_DECK - 1));
		state.whoseTurn = currentPlayer;

		testVillage(currentPlayer, &state);

	}

	printf("ran 1000 times in main\n");
	int failCount = effectFailCounter + discardFailCounter + drawFailCounter + deckFailCounter + actionFailCounter;

	if(failCount == 0)
		printf("\n TEST PASSED \n");

	else {

		printf("\n TEST FAILED \n");
		printf("Effect Card Failed %d times\n", effectFailCounter);
		printf("Discard Failed %d times\n", discardFailCounter);
		printf("Draw Card Failed %d times\n", drawFailCounter);
		printf("Card Count Failed %d times\n", deckFailCounter);
        printf("Action Count Failed %d times\n", actionFailCounter);

	}

	return 0;
}

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int effectFailCounter, treasureFailCounter, shuffleFailCounter, discardFailCounter, drawFailCounter, deckFailCounter = 0;

void testAdventurer(int currentPlayer, struct gameState * altered) {
    
    struct gameState original;
    int alteredTreasureCount, originalTreasureCount, drawnTreasure = 0;
    int temp[MAX_HAND];
    int cardDrawn, card = 0;
    int bonus, effect, sh = 0;
    int dc = 0;
    int i, z = 0;
    
    
    memcpy(&original,altered,sizeof(struct gameState));
    
    effect = cardEffect(adventurer,0,0,0,altered,0,&bonus);
    
    if (effect) {
        effectFailCounter++;
    }
    
    while(drawnTreasure < 2) {
        
        if (original.deckCount[currentPlayer] < 1) {
            
            sh = shuffle(currentPlayer, &original);

            if (sh == -1 && original.deckCount[currentPlayer] >= 1) {
                shuffleFailCounter++;
            }
        }
        
        dc = drawCard(currentPlayer, &original);
        
        if (dc == -1 && original.deckCount[currentPlayer] != 0) {
            drawFailCounter++;
        }
        
        cardDrawn = original.hand[currentPlayer][original.handCount[currentPlayer] - 1];
        
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
            drawnTreasure++;
        
        else{
            
            temp[z] = cardDrawn;
            original.handCount[currentPlayer]--;
            z++;
        }
    }
    
    while(z - 1 >= 0) {
        
        original.discard[currentPlayer][original.discardCount[currentPlayer]++] = temp[z - 1];
        z = z - 1;
    }
    
    for (i = 0; i < altered->handCount[currentPlayer]; i++) {
        card = altered->hand[currentPlayer][i];
        if (card == copper || card == silver || card == gold) {
            alteredTreasureCount++;
        }
    }

    for (i = 0; i < original.handCount[currentPlayer]; i++) {
        card = original.hand[currentPlayer][i];
        if (card == copper || card == silver || card == gold) {
            originalTreasureCount++;
        }
    }

    
    if (alteredTreasureCount != originalTreasureCount) {
        treasureFailCounter++;
    }
    
    int alteredHandCount = altered->handCount[currentPlayer];
    int alteredDeckCount = altered->deckCount[currentPlayer];
    int alteredDiscardCount = altered->discardCount[currentPlayer];
    int originalHandCount = original.handCount[currentPlayer];
    int originalDeckCount = original.deckCount[currentPlayer];
    int originalDiscardCount = original.discardCount[currentPlayer];
    
    if (!(alteredHandCount == originalHandCount && alteredDeckCount == originalDeckCount && alteredDiscardCount == originalDiscardCount)) {
        deckFailCounter++;
    }
}

int main () {
    
    srand(time(NULL));
    
    printf("\nTesting: adventurer\n");
    int treasures[] = {copper,silver,gold};
    int treasureCount;
    int i, j, k;
    int currentPlayer;
    struct gameState state;
    
    int min = 3;
    
    for (i = 0; i < 10000; i++) {
        for (j = 0; j < sizeof(struct gameState); j++) {
            ((char*)&state)[j] = floor(Random() * 256);
        }

        currentPlayer = floor(Random() * MAX_PLAYERS);
        state.deckCount[currentPlayer] = floor(Random() * ((MAX_DECK - min) + 1) + min);
        treasureCount = floor(Random() * ((state.deckCount[currentPlayer] - min) + 1) + min);
        
        // Place 3 treasures in the deck
        for (k = 0; k < treasureCount; k++) {
            state.deck[currentPlayer][k] = treasures[rand() % 3];
        }
        
        state.discardCount[currentPlayer] = 0;
        state.handCount[currentPlayer] = floor(Random() * ((MAX_HAND - min) + 1) + min);
        state.whoseTurn = currentPlayer;
        
        testAdventurer(currentPlayer, &state);
    }
    
    
    int failCount = effectFailCounter + drawFailCounter + shuffleFailCounter +
    deckFailCounter + treasureFailCounter;
    
    
    if (failCount == 0) {
        printf ("\n TEST PASSED \n");
    }
    
    else {
        printf("\nTEST FAILED\n");
        printf("Shuffle failed %d times\n", shuffleFailCounter);
        printf("Draw Card failed %d times\n", drawFailCounter);
        printf("Card Effect failed %d times\n", effectFailCounter);
        printf("Treasure Count failed %d times\n", treasureFailCounter);
        printf("Hand/Deck Count failed %d times\n", deckFailCounter);
    }
    
    return 0;
}

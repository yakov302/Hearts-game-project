#ifndef __DECK_H__
#define __DECK_H__

#include <stdlib.h>
#include <time.h>

#include "vector.h"
#include "cards.h"

#define MAGIC_NUMBER3 69948

typedef struct Deck Deck;

/*Description:
Creates a new Deck structure.

Input:
_NumOfdecks - The number of decks the game needs.

Output:
NULL - If one of the memory allocation fails.
round - Pointer to round structure.*/
Deck * DeckCreate (int _NumOfdecks);

/*Description:
Destroys the deck structure.

Input:
_deck - Pointer to deck structure.*/
void DeckDestroy (Deck * _deck);

/*Description:
Shuffle the deck randomly as many times as the number of cards.

Input:
_deck - Pointer to deck structure.

Output:
ERR_NOT_INITIALIZED - If _deck == NULL.
ERR_OK - If Shuffle done successfully.*/
ADTErr DeckShuffle (Deck * _deck);

/*Description:
Gives card at the request of the round and deletes it from the deck.

Input:
_deck - Pointer to deck structure.

Output:
ERR_NOT_INITIALIZED - If _deck == NULL.
card - The card it gives.*/
int DeckPopCard (Deck * _deck);


#endif //__DECK_H__

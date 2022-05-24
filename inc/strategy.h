
#include "players.h"

#define NO 0
#define YES 1

/*Description: 
	strategy for machine players.
Input:
	validCards - array of valid cards.
    validCardsSize 
    _isOpenHend
    _openCard 
    _openSuit 
Output:
	card - The optimal card according to the strategy.*/ 
int strategy(int* validCards, int validCardsSize, int _isOpenHend, int _openCard, int _openSuit);

/*Description: 
	strategy for initial swap for machine players.
Input:
	_player - Pointer to player.
    _numOfCards
Output:
    card - The optimal card according to the strategy.*/ 
int InitialSwapStrategy(Player* _player,  int _numOfCards);

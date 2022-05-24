#ifndef __PLAYERS_H__
#define __PLAYERS_H__

#include <stdlib.h>

#include "cards.h"
#include "enum.h"
#include "sorting_algorithms.h"


#define NO 0
#define YES 1
#define NOT_VALID -1
#define MAGIC_NUMBER4 14325

typedef struct Player Player; 

/*Description:
Creates a new player.

Input:
_name - player name.
_num - player number.
_IsHuman - 1 if human, 0 if machine.

Output:
NULL - If one of the memory allocation fails.
player - Pointer to player structure.*/
Player* PlayerCreate (int _playerNum, int _IsHuman);

/*Description:
Destroys the player structure.

Input:
_player - Pointer to player structure.*/
void PlayerDestroy ( Player * _player ) ;

/*Description:
Inserts new card to the cards vector of the player.

Input:
_player - Pointer to player structure.
_card - The new card.

Output:
ERR_NOT_INITIALIZED - if _player == NULL;
ERR_OK - If the card enters successfully.*/
ADTErr GetCard (Player * _player, int _card) ;

/*Description:
Handing card by demand according the rules and strategy received frome the round.

Input:
_player - Pointer to player structure.
_isOpenHend - 1 If its open hand, 0 otherwise
_isOpenTeick - 1 If its the first hand in the trick, 0 otherwise.
_isHeartBreke - 1 if heart brok, 0 if not.
_openSuit - the open Suit.
_openCard - the open card.
IsCardValid - Pointer to function that checks the validity of the card. received frome the round.
strategy - Pointer to function that selects card based on strategy. received frome the round.

Output:
card - The card the player handing.*/
int GiveCard (Player * _player, int _isOpenHend, int _isOpenTeick ,int _isHeartBreke, int _openSuit, int _openCard, int(*IsCardValid)(Vector*,int,int,int,int,int), int(*strategy)(int*,int,int,int,int));

/*Description:
Handing 3 cards to another player at the beginning of each round according the strategy received frome the round.

Input:
_player - Pointer to player structure.
strategy - Pointer to function that selects card based on strategy. received frome the round.

Output:
cards - The cards the player handing.*/
int GiveCardForInitialSwap (Player * _player, int(*strategyFor3)(Player*,int)) ;

/*Description:
Checks if a card exist or not.

Input:
_player - Pointer to player structure.
_card - the card we chack.

Output:
ERR_NOT_INITIALIZED - if _player == NULL.
ERR_ELEMENT_EXIST -if the card exsist.
ERR_ELEMENT_DONT_EXIST - uf the card dont exsist.*/
ADTErr IsCardExists(Player * _player, int _card);

/*Description:
Returns a card in the index place (does not delete it)

Input:
_player - Pointer to player structure.
_index - the card index we want.

Output:
item - the card in the index place.*/
int GivePlayrCards(Player* _player, int _index);

/*Description:
Returns the number of cards the player has.

Input:
_player - Pointer to player structure.

Output:
numOfCards - the number of cards.*/
int HowManyCards(Player* _player);


#endif //__PLAYERS_H__

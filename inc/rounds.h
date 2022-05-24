#ifndef __ROUNDS_H__
#define __ROUNDS_H__

#include "strategy.h"
#include "players.h"
#include "deck.h"
#include "enum.h"
#include "ui.h"

#define NO 0
#define YES 1
#define MAGIC_NUMBER2 548889

typedef struct Round Round;

/*Description:
Creates a new round structure.

Input:
_numOfplayers - Total number of players.
_howManyHuman - How many human players.
_players - array of pointers to players.

Output:
NULL - If one of the memory allocation fails or if _players == NULL.
round - Pointer to round structure.*/
Round* RoundCreate (int _numOfplayers, int _howManyHuman, Player ** _players);

/*Description:
Destroys the round structure.

Input:
_round - Pointer to round structure.*/
void RoundDestroy (Round * _round);

/*Description:
Executes a new round and manages it.

Input:
_round - Pointer to round structure.
_score - Pointer to scores array.
_numOfplayers - Total number of players.

Output:
ERR_NOT_INITIALIZED - if _round == NULL or if _score == NULL.
round - Pointer to round structure.*/
ADTErr RunRound (Round * _round, int *_score, int _numOfRound);


#endif //__ROUNDS_H__

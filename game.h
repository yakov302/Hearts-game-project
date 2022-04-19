#ifndef __GAME_H__
#define __GAME_H__
#include "rounds.h"
#include "players.h"
#include "enum.h"
#include "userInterface.h"

/*rename to struct Game*/
typedef struct Game Game; 

/*Description:
The function creates a new game.

Input:
_numOfplayers - Total number of players.
_howManyHuman - How many human players.

Output:
NULL - If one of the memory allocation fails.
game - Pointer to game structure.*/
Game * GameCreate ( int _numOfplayers, int _howManyHuman);

/*Description:
Runs the game.

Input:
 _game - Pointer to game structure.

Output:
ERR_NOT_INITIALIZED - If _game == NULL.
ERR_OK - If game is running.*/
ADTErr PlayGame(Game * _game);

/*Description:
Destroys the game.

Input:
 _game - Pointer to game structure.*/
void GameDestroy (Game * _game);


#endif /*#ifndef__GAME_H__*/

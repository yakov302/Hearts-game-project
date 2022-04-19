#include <stdio.h>
#include <stdlib.h>
#include "rounds.h"
#include "players.h"
#include "userInterface.h"
#include "enum.h"
#define MAGIC_NUMBER1 67358

/***********************struct Game*********************/

typedef struct Game 
{
	int m_numOfplayers;
	int* m_score;
	int m_numOfRound;
	Round * m_round ;
	Player ** m_players; 
	int m_magicNumber;
}Game;

/***********************FunctionSignatures*********************/

void GameDestroy (Game * _game);
static int FindWinner(Game * _game, int _numOfplayers);

/***********************GameCreate *********************/

Game* GameCreate (int _numOfplayers, int _howManyHuman)
{
Game* game;
int i;
int j;

	if((game = ((Game*)malloc(sizeof(Game)))) == NULL)
	{
		return NULL;
	}
	
	if (( game -> m_score = ((int*) calloc( _numOfplayers ,sizeof(int)))) == NULL)
	{
		free(game);
		return NULL;
	}
	
	if (( game ->  m_players = ((Player **) malloc( _numOfplayers*sizeof(Player*)))) == NULL)
	{
		free(game -> m_score);
		free(game);
		return NULL;
	}
		
	for (i = 0; i < _howManyHuman; i++)
	{
		if((game -> m_players[i] = PlayerCreate (i, 1)) == NULL)
		{
			for(j = 0; j < i; j++)
			{
				PlayerDestroy (game -> m_players[j]);
			}
			free(game ->  m_players);
			free(game -> m_score);
			free(game);
			return NULL;
		}
	}
	
	for (i = _howManyHuman; i < _numOfplayers; i++)
	{
		if((game -> m_players[i] = PlayerCreate (i ,0)) == NULL)
		{
			for(j = 0; j < i; j++)
			{
				PlayerDestroy (game -> m_players[j]);
			}
			free(game ->  m_players);
			free(game -> m_score);
			free(game);
			return NULL;	
		}
	}
	
	if((game -> m_round = RoundCreate(_numOfplayers, _howManyHuman, game -> m_players))== NULL)
	{
		for (i = 0; i < game -> m_numOfplayers; i++)
		{
			PlayerDestroy (game -> m_players[i]);
		}
		free(game ->  m_players);
		free(game -> m_score);
		free(game);
		return NULL;	
	}
	
	game -> m_numOfplayers = _numOfplayers;
	game -> m_numOfRound = 0;
	game -> m_magicNumber = MAGIC_NUMBER1;
	
return game;	
}

/***********************PlayGame *********************/

ADTErr PlayGame(Game * _game)
{
int status = 0;
int winNum;
int winScore;

	if(_game == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	while(status == 0)
	{
		_game -> m_numOfRound++; 
		RunRound (_game -> m_round, _game -> m_score,_game -> m_numOfRound);
		status = CheckEndConditions(_game -> m_score, _game -> m_numOfplayers);
		if(status == 1)
		{
			winNum = FindWinner(_game, _game -> m_numOfplayers);
			winScore = _game -> m_score[winNum];
			DeclareWinner(winNum, winScore);			
			GameDestroy (_game);	
		}	
	}
	
return ERR_OK;
}

static int FindWinner(Game * _game, int _numOfplayers)
{
int i;
int min;
int minPlayer;

	min = _game -> m_score[0];

	for(i = 0; i < _numOfplayers; i++)
	{
		if( _game -> m_score[i] <=  min)
		{
			min = _game -> m_score[i];
			minPlayer = i;	
		}	
	}
return minPlayer;
}

/***********************GameDestroy *********************/

void GameDestroy (Game * _game)
{
int i;
	if(_game == NULL || _game -> m_magicNumber != MAGIC_NUMBER1)
	{
		return;
	}
	
	_game -> m_magicNumber = 0;
	
	for (i = 0; i < _game -> m_numOfplayers; i++)
	{
		PlayerDestroy (_game -> m_players[i]);
	}
	
	RoundDestroy (_game -> m_round);
	free(_game ->  m_players);
	free(_game -> m_score);
	free(_game);
}






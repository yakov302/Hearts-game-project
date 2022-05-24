#include "game.h"

typedef struct Game 
{
	int m_numOfplayers;
	int* m_score;
	int m_numOfRound;
	Round * m_round ;
	Player ** m_players; 
	int m_magicNumber;
}Game;

void GameDestroy (Game * _game);
static int FindWinner(Game * _game, int _numOfplayers);
static int CheckEndConditions(int* _score, int _numOfplayers); // pass as parameter frome main
static void CreatePlayers(Game* _game, int _howManyHuman, int _numOfplayers);
static void DestroyPlayers(Game* _game, int _numOfplayers);

Game* GameCreate (int _numOfplayers, int _howManyHuman)
{
	Game* game;

	if((game = ((Game*)malloc(sizeof(Game)))) == NULL)
	{return NULL;}
	
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

	CreatePlayers(game, _howManyHuman, _numOfplayers);
			
	if((game -> m_round = RoundCreate(_numOfplayers, _howManyHuman, game -> m_players)) == NULL)
	{
		DestroyPlayers(game, _numOfplayers);
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

static void CreatePlayers(Game* _game, int _howManyHuman, int _numOfplayers)
{
	int i;
	int j;

	for (i = 0; i < _howManyHuman; ++i)
	{
		if((_game -> m_players[i] = PlayerCreate (i, 1)) == NULL)
		{
			for(j = 0; j < i; j++)
			{
				PlayerDestroy (_game -> m_players[j]);
			}
			free(_game ->  m_players);
			free(_game -> m_score);
			free(_game);
			return;
		}
	}
	
	for (i = _howManyHuman; i < _numOfplayers; ++i)
	{
		if((_game -> m_players[i] = PlayerCreate (i ,0)) == NULL)
		{
			for(j = _howManyHuman; j < i; ++j)
			{
				PlayerDestroy (_game -> m_players[j]);
			}
			free(_game ->  m_players);
			free(_game -> m_score);
			free(_game);
			return;	
		}
	}
}

static void DestroyPlayers(Game* _game, int _numOfplayers)
{
	int i;

	for (i = 0; i < _game -> m_numOfplayers; i++)
	{
		PlayerDestroy (_game -> m_players[i]);
	}
}

void PlayGame(Game * _game)
{
	int status = OFF;
	int winNum;
	int winScore;

	if(_game == NULL)
	{return;}
	
	while(status == OFF)
	{
		_game -> m_numOfRound++; 
		RunRound (_game -> m_round, _game -> m_score, _game -> m_numOfRound);
		status = CheckEndConditions(_game -> m_score, _game -> m_numOfplayers);
		if(status == ON)
		{
			winNum = FindWinner(_game, _game -> m_numOfplayers);
			winScore = _game -> m_score[winNum];
			DeclareWinner(winNum, winScore);
			return;			
		}	
	}
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

void GameDestroy (Game * _game)
{
	if(_game == NULL || _game -> m_magicNumber != MAGIC_NUMBER1)
	{return;}
	
	_game -> m_magicNumber = 0;
	
	DestroyPlayers(_game, _game->m_numOfplayers);
	RoundDestroy (_game -> m_round);
	free(_game ->  m_players);
	free(_game -> m_score);
	free(_game);
}

static int CheckEndConditions(int* _score, int _numOfplayers)
{
	int i;

	for(i = 0; i < _numOfplayers; i++)
	{
		if(_score[i] >= 100)
		{
			return ON;
		}
	}

	return OFF;
}

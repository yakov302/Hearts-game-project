#include "game.h"

int main()
{
	Game* game;
	game = GameCreate(4,1);
	if(game != NULL)
	{
		PlayGame(game);
		GameDestroy(game);
	}
	else
	{
		printf("Game initialization failedl!");
	}
}



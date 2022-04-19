#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int CheckEndConditions(int* _score, int _numOfplayers)
{
int i;
	for(i = 0; i < _numOfplayers; i++)
	{
		if(_score[i] >= 100)
		{
			return 1;
		}
	}

return 0;
}

int main()
{
Game* ptr;
ptr = GameCreate(4,1);
PlayGame(ptr);
GameDestroy(ptr);

}



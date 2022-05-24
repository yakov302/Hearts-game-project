#include "strategy.h"

static int StrategyCase1 (int* validCards, int validCardsSize);
static int StrategyCase2 (int* validCards, int validCardsSize,  int _openCard);
static int StrategyCase3 (int* validCards, int validCardsSize);
static int StrategyCase4 (int* validCards, int validCardsSize,  int _openCard);

int strategy(int* validCards, int validCardsSize, int _isOpenHend, int _openCard, int _openSuit)
{
	int maxHeart = 0;
	int i;

	if(_isOpenHend == YES)
	{return StrategyCase1 (validCards, validCardsSize);}
	
	if(_isOpenHend == NO)
	{		
		if(_openSuit == HEART)
		{StrategyCase2 (validCards, validCardsSize, _openCard);}
		
		if(_openSuit == SPADE)
		{StrategyCase4 (validCards, validCardsSize, _openCard);}
		
		if( _openSuit == CLUBS || _openSuit == DIAMOND)
		{StrategyCase3 (validCards, validCardsSize);}				
	}
}

static int StrategyCase1 (int* validCards, int validCardsSize)
{
	int maxHeart = 0;
	int i;

	for(i = 0; i < validCardsSize; ++i)
	{
		if(validCards[i] > maxHeart
		&& validCards[i] >= MIN_HEARTS
		&& validCards[i] <= MAX_HEARTS)
		{
			maxHeart = validCards[i];
		}		
	}
	if(maxHeart != 0)
	{return maxHeart;}
		
	for(i = validCardsSize-1; i > 0; --i)
	{
		if((validCards[i] < MIN_HEARTS
		|| validCards[i] > MAX_HEARTS)
		&& validCards[i] != SPADES_QUEEN)
		{return validCards[i];}		
	}	

	return validCards[0];	
}

static int StrategyCase2 (int* validCards, int validCardsSize,  int _openCard)
{
	int maxHeart = 0;
	int i;

	for(i = 0; i < validCardsSize; ++i)
	{
		if(validCards[i] > maxHeart && validCards[i] < _openCard)
		{
			maxHeart = validCards[i];
		}		
	}
	if(maxHeart != 0)
	{return maxHeart;}
			
	for(i = validCardsSize-1; i > 0; --i)
	{
		if(validCards[i] < MIN_HEARTS
		|| validCards[i] > MAX_HEARTS)
		{
			return validCards[i];
		}		
	}

	return validCards[0];				
}

static int StrategyCase3 (int* validCards, int validCardsSize)
{
	int maxHeart = 0;
	int max = 0;
	int i;
		
	for(i = 0; i < validCardsSize; i++)
	{
		if(validCards[i] == SPADES_QUEEN)
		{return validCards[i];}		
	}
	
	for(i = 0; i < validCardsSize; ++i)
	{
		if(validCards[i] > maxHeart
		&& validCards[i] >= MIN_HEARTS
		&& validCards[i] <= MAX_HEARTS)
		{
			maxHeart = validCards[i];
		}		
	}
	if(maxHeart != 0)
	{return maxHeart;}
	
	for(i = 0; i < validCardsSize; ++i)
	{
		if(validCards[i] > max)
		{
			max = validCards[i];
		}		
	}
	if(max!=0)
	{return max;}
	
	return validCards[0];
}

static int StrategyCase4 (int* validCards, int validCardsSize,  int _openCard)
{
	int i;

	for(i = 0; i < validCardsSize; ++i)
	{
		if(_openCard > SPADES_QUEEN && validCards[i] == SPADES_QUEEN)
		{
			return validCards[i];
		}		
	}
		
	for(i = 0; i < validCardsSize; ++i)
	{
		if(_openCard < SPADES_QUEEN && validCards[i] != SPADES_QUEEN)
		{
			return validCards[i];
		}		
	}

	return validCards[0];				
}

int InitialSwapStrategy(Player* _player, int _numOfCards)
{
	int* optimalCardsIndex;
	int maxHeartIndex;
	int maxHeart = 0;
	int k = 0;
	int card;
	int i;

	if ((optimalCardsIndex = ((int*) calloc(_numOfCards,sizeof(int)))) == NULL)
	{return ERR_NOT_INITIALIZED;}

	for(i = 0; i < _numOfCards; ++i)
	{
		card = GivePlayrCards(_player, i);
		if(card == SPADES_QUEEN)
		{
			optimalCardsIndex[k] = i;
			++k;
		}
	}
		
	for(i = 0; i < _numOfCards; ++i)
	{
		card = GivePlayrCards(_player, i);
		if(card >= MIN_HEARTS
		&& card<= MAX_HEARTS
		&& card >= maxHeart)
		{
			maxHeart = card;
			maxHeartIndex = i;	
		}
	}
	if( maxHeart != 0)
	{
		optimalCardsIndex[k] = maxHeartIndex;
		k++;
	}
	
	for(i = 0; i < _numOfCards; i++)
	{
		card = GivePlayrCards(_player, i);
		if(card > SPADES_QUEEN)
		{
			optimalCardsIndex[k] = i;
			k++;	
		}
	}

	card = optimalCardsIndex[0];
	free(optimalCardsIndex);
	return card;
}

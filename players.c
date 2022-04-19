#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "players.h"
#include "cards.h"
#include "enum.h"
#include "SortingAlgorithms.h"
#define MAGIC_NUMBER4 14325

/***********************struct Player*********************/

struct Player 
{
	Vector* m_handCards;
	int m_playerNum;
	int m_IsHuman;
	int m_magicNumber;
};

/***********************FunctionSignatures*********************/

static ADTErr sortCards(Player* _player, int _maxValu);
static int HumanTrick(int _isOpenHend, int _isOpenTeick, int _isHeartBreke, int _openSuit,  int isOpenSuitExists);
static int CheckIfOpenSuitExists(Player * _player, int _numOfCards, int _openSuit);
static int FindCardIndex(int* validCards, int len, int card);
static void DeleteCardYouGive (Player * _player, int _LatestIndex, int RemoveIndex);

/***********************PlayerCreate*********************/

Player* PlayerCreate (int _playerNum, int _IsHuman)
{
Player* player;

	if((player = ((Player*)malloc(sizeof(Player)))) == NULL)
	{
		return NULL;
	}
	

	if((player -> m_handCards = VectorCreate (NUM_OF_CARDS_IN_DECK, 5)) == NULL)
	{
		free(player);
		return NULL;
	}
	
	player -> m_playerNum = _playerNum;
	player -> m_IsHuman = _IsHuman;
	player -> m_magicNumber = MAGIC_NUMBER4;

return player;
}

/***********************PlayerDestroy*********************/

void PlayerDestroy (Player * _player)
{

	if(_player == NULL || _player -> m_magicNumber != MAGIC_NUMBER4)
	{
		return;
	}

	_player -> m_magicNumber = 0;
	VectorDestroy (_player -> m_handCards);
	free(_player);	
}

/***********************GiveCard*********************/

int GiveCard (Player * _player, int _isOpenHend, int _isOpenTeick ,int _isHeartBreke, int _openSuit, int _openCard, int(*IsCardValid)(Vector*,int,int,int,int,int), int(*strategy)(int*,int,int,int,int)) 
{
int* validCardsIndex; 
int IsCardValidCheck;
size_t numOfCards;
int* validCards;
int cardIndex;
int k = 0;
int temp;
int card;
int i;

	if(_player == NULL)
	{
		return;
	}
	
	VectorItemsNum (_player -> m_handCards, &numOfCards);
	
	if ((validCards = ((int*) calloc(numOfCards,sizeof(int)))) == NULL)
	{
		return;
	}
	if ((validCardsIndex = ((int*) calloc(numOfCards,sizeof(int)))) == NULL)
	{
		free(validCards);
		return;
	}
		
	for(i = 0; i < numOfCards; i++)
	{
		VectorGet(_player -> m_handCards, i, &card);
		IsCardValidCheck = IsCardValid(_player -> m_handCards, _isOpenHend, _isOpenTeick, _isHeartBreke, card, _openSuit);
		if(IsCardValidCheck == VALID_CARD)
		{
			validCards[k] = card;
			validCardsIndex[k] = i;
			k++;
		}
	}
	
if(_player -> m_IsHuman == 0)
{	
	card = strategy(validCards, k , _isOpenHend,  _openCard, _openSuit);
	cardIndex = FindCardIndex(validCards,k , card);
	
	DeleteCardYouGive (_player, numOfCards -1, validCardsIndex[cardIndex]);	
		
	sortCards(_player, NUM_OF_CARDS_IN_DECK);
	
	free(validCards);
	free(validCardsIndex);
	
return card;
}

if(_player -> m_IsHuman == 1)
{
	card = AskCardFromPlayer(_player);
	for(i = 0; i < k; i++)
	{
		if(card == validCards[i])
		{	
			DeleteCardYouGive (_player, numOfCards -1, validCardsIndex[i]);							
			sortCards(_player, NUM_OF_CARDS_IN_DECK);
			return card;	
		}
	}

	printNotValid();
	GiveCard (_player,  _isOpenHend, _isOpenTeick ,_isHeartBreke, _openSuit,  _openCard, IsCardValid, strategy);
}
}

/***********************FindCardIndex*********************/

static int FindCardIndex(int* validCards, int len, int card)
{
int i;
	for(i = 0; i < len ; i++)
	{
		if(card == validCards[i])
		{
			return i;	
		}
	}
}

/***********************DeleteCardYouGive*********************/

static void DeleteCardYouGive (Player * _player, int _LatestIndex, int RemoveIndex)
{
int temp;

	VectorGet(_player -> m_handCards, _LatestIndex , &temp);
	VectorSet(_player -> m_handCards,RemoveIndex, temp);
	VectorDelete(_player -> m_handCards, &temp);
}


/***********************GiveCardFor3*********************/

int GiveCardFor3 (Player * _player, int(*strategyFor3)(Player*,int)) 
{
size_t numOfCards;
int optimalIndex;
int temp;
int card;
int i;

	if(_player == NULL)
	{
		return;
	}
	
	
VectorItemsNum (_player -> m_handCards, &numOfCards);

if(_player -> m_IsHuman == 0)
{		
	optimalIndex = strategyFor3(_player,  numOfCards);

	VectorGet(_player -> m_handCards, optimalIndex , &card);
	DeleteCardYouGive (_player, numOfCards -1, optimalIndex);	
	sortCards(_player, NUM_OF_CARDS_IN_DECK);
	
return card;
}

if(_player -> m_IsHuman == 1)
{
	card = AskCardFromPlayer(_player);
	for(i = 0; i < numOfCards ; i++)
	{
		VectorGet(_player -> m_handCards, i , &temp);
		if(card == temp)
		{
			DeleteCardYouGive (_player, numOfCards -1, i);
			sortCards(_player, NUM_OF_CARDS_IN_DECK);
			printPlayersHand(_player , _player -> m_playerNum);
			return card;
		}
	}
	
	printNotValid();
	GiveCardFor3 (_player, strategyFor3);
}
}

/***********************GetCard*********************/

ADTErr GetCard (Player * _player,int _card) 
{
	if(_player == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorAdd (_player -> m_handCards, _card);
	sortCards(_player, NUM_OF_CARDS_IN_DECK);
	
return ERR_OK;
}

/***********************sortCards*********************/

static ADTErr sortCards(Player* _player, int _maxValu)
{
	CountingSort(_player -> m_handCards, _maxValu);
	
return ERR_OK;
}

/***********************IsCardExists*********************/

ADTErr IsCardExists(Player * _player, int _card)
{
size_t numOfCards;
int tempCars;
int i;

	if(_player == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}

	VectorItemsNum (_player -> m_handCards, &numOfCards);
	
	for(i = 0; i < numOfCards; i++)
	{
		VectorGet(_player -> m_handCards, i, &tempCars);
		if(tempCars ==  _card)
		{
			return ERR_ELEMENT_EXIST;
		}
	}
return ERR_ELEMENT_DONT_EXIST;
}

/***********************GivePlayrCards*********************/

int GivePlayrCards(Player* _player, int _index)
{
int item;

	if(_player == NULL)
	{
		return;
	}

	VectorGet(_player -> m_handCards,  _index, &item);
	
return  item;
}


/***********************HowManyCards*********************/

int HowManyCards(Player* _player)
{
size_t numOfCards;

	if(_player == NULL)
	{
		return;
	}

	VectorItemsNum (_player -> m_handCards , &numOfCards);
	
return numOfCards;
}







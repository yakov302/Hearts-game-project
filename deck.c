#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "deck.h"
#include "cards.h"
#include "enum.h"
#define MAGIC_NUMBER3 69948

/***********************struct Deck*********************/

struct Deck 
{
	Vector* m_deck;
	int m_magicNumber;
};

/***********************DeckCreate*********************/

Deck* DeckCreate (int _NumOfdecks)
{
Deck* deck;
int i;

	if ((deck = ((Deck*) malloc(sizeof(Deck)))) == NULL)
	{
		return NULL;
	}
	
	if((deck -> m_deck = VectorCreate (NUM_OF_CARDS_IN_DECK*_NumOfdecks, 0)) == NULL)
	{
		free(deck);
		return NULL;
	}
	
	for(i = 0; i < NUM_OF_CARDS_IN_DECK*_NumOfdecks; i++)
	{
		VectorAdd (deck -> m_deck, i);
	}
		
	deck -> m_magicNumber = MAGIC_NUMBER3;
	
return deck;
}

/***********************DeckDestroy*********************/

void DeckDestroy (Deck * _deck)
{
	if(_deck == NULL  || _deck -> m_magicNumber != MAGIC_NUMBER3)
	{
		return ;
	}
	
	_deck -> m_magicNumber = 0;
	VectorDestroy (_deck -> m_deck);
	free(_deck);
}

/***********************DeckShuffle*********************/

ADTErr DeckShuffle (Deck * _deck)
{
int i;
int item1;
int item2;
size_t index1;
size_t index2;
size_t len;

	if(_deck == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum (_deck -> m_deck, &len);

	srand(time(0));
	for(i = 0; i < len; i++)
	{
		index1 = rand()%len;
		index2 = rand()%len;
		VectorGet(_deck -> m_deck, index1, &item1);
		VectorGet(_deck-> m_deck, index2 , &item2);
		VectorSet(_deck-> m_deck, index1,item2);
		VectorSet(_deck -> m_deck,index2,item1);				
	}
return ERR_OK;	
}

/***********************DeckPopCard*********************/

int DeckPopCard (Deck * _deck)
{
int card;

	if(_deck == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorDelete(_deck -> m_deck, &card);
	
return card;	
}












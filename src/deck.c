#include "deck.h"

struct Deck 
{
	Vector* m_deck;
	int m_magicNumber;
};

static void CreateCards(Deck* _deck, int _NumOfdecks);
static void swapCards(Vector* _vrctor, int _index1, int _index2);

Deck* DeckCreate (int _NumOfdecks)
{
	Deck* deck;
	int i;

	if ((deck = ((Deck*) malloc(sizeof(Deck)))) == NULL)
	{return NULL;}
	
	if((deck -> m_deck = VectorCreate (NUM_OF_CARDS_IN_DECK*_NumOfdecks, 0)) == NULL)
	{
		free(deck);
		return NULL;
	}

	CreateCards(deck, _NumOfdecks);
	deck -> m_magicNumber = MAGIC_NUMBER3;

	return deck;
}

static void CreateCards(Deck* _deck, int _NumOfdecks)
{
	int i;

	for(i = 0; i < NUM_OF_CARDS_IN_DECK*_NumOfdecks; ++i)
	{
		VectorAdd (_deck -> m_deck, i);
	}
}

void DeckDestroy (Deck * _deck)
{
	if(_deck == NULL  || _deck -> m_magicNumber != MAGIC_NUMBER3)
	{return ;}
	
	_deck -> m_magicNumber = 0;
	VectorDestroy (_deck -> m_deck);
	free(_deck);
}

ADTErr DeckShuffle (Deck* _deck)
{
	int i;
	size_t index1;
	size_t index2;
	size_t len;

	if(_deck == NULL)
	{return ERR_NOT_INITIALIZED;}
	
	VectorItemsNum (_deck -> m_deck, &len);

	srand(time(0));
	for(i = 0; i < len; i++)
	{
		index1 = rand()%len;
		index2 = rand()%len;
		swapCards(_deck -> m_deck, index1, index2);			
	}

	return ERR_OK;	
}

static void swapCards(Vector* _vrctor, int _index1, int _index2)
{
	int item1;
	int item2;

	VectorGet(_vrctor, _index1, &item1);
	VectorGet(_vrctor, _index2 , &item2);
	VectorSet(_vrctor, _index1,item2);
	VectorSet(_vrctor, _index2,item1);
}

int DeckPopCard (Deck * _deck)
{
	int card;

	if(_deck == NULL)
	{return ERR_NOT_INITIALIZED;}	
	VectorDelete(_deck -> m_deck, &card);
	
	return card;	
}


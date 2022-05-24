#include "players.h"
#include "ui.h"

struct Player 
{
	Vector* m_handCards;
	int m_playerNum;
	int m_IsHuman;
	int m_magicNumber;
};

static ADTErr sortCards(Player* _player, int _maxValu);
static int HumanTrick(int _isOpenHend, int _isOpenTeick, int _isHeartBreke, int _openSuit,  int isOpenSuitExists);
static int CheckIfOpenSuitExists(Player * _player, int _numOfCards, int _openSuit);
static int FindCardIndex(Vector* _vector, int len, int card);
static void DeleteCardYouGive (Player * _player, int _LatestIndex, int RemoveIndex);
static int fillValidCardArray(Player* _player, int(*IsCardValid)(Vector*,int,int,int,int,int), int* _validCards, size_t _numOfCards, int _isOpenHend, int _isOpenTeick, int _isHeartBreke, int _openSuit);
static int GiveCardMachinePlayer(Player* _player, int(*strategy)(int*,int,int,int,int), int* _validCards, int _validCardsIndex, int _isOpenHend,  int _openCard, int _openSuit, int _numOfCards);
static int GiveCardHumanPlayer(Player* _player, int* _validCards, int _validCardsIndex, int _numOfCards);
static int GiveCardForInitialSwapMachinePlayer(Player* _player, int(*InitialSwapStrategy)(Player*,int), int _numOfCards);
static int GiveCardForInitialSwapHumanPlayer(Player* _player, int _numOfCards);

Player* PlayerCreate (int _playerNum, int _IsHuman)
{
	Player* player;

	if((player = ((Player*)malloc(sizeof(Player)))) == NULL)
	{return NULL;}
	
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

void PlayerDestroy (Player * _player)
{

	if(_player == NULL || _player -> m_magicNumber != MAGIC_NUMBER4)
	{return;}

	_player -> m_magicNumber = 0;
	VectorDestroy (_player -> m_handCards);
	free(_player);	
}

int GiveCard (Player* _player, int _isOpenHend, int _isOpenTeick ,int _isHeartBreke, int _openSuit, int _openCard, int(*IsCardValid)(Vector*,int,int,int,int,int), int(*strategy)(int*,int,int,int,int)) 
{
	size_t numOfCards;
	int validCardsIndex;
	int* validCards;
	int card;

	if(_player == NULL)
	{return ERR_NOT_INITIALIZED;}
	
	VectorItemsNum (_player->m_handCards, &numOfCards);
	
	if ((validCards = ((int*) calloc(numOfCards,sizeof(int)))) == NULL)
	{return ERR_NOT_INITIALIZED;}
	validCardsIndex = fillValidCardArray(_player, IsCardValid, validCards, numOfCards, _isOpenHend, _isOpenTeick, _isHeartBreke, _openSuit);

	if(_player -> m_IsHuman == NO)
	{	
		return GiveCardMachinePlayer(_player, strategy, validCards, validCardsIndex, _isOpenHend,  _openCard, _openSuit, numOfCards);
	}

	if(_player -> m_IsHuman == YES)
	{
		card = GiveCardHumanPlayer(_player, validCards, validCardsIndex, numOfCards);
		if(card != NOT_VALID)
		{return card;}
		GiveCard (_player, _isOpenHend, _isOpenTeick ,_isHeartBreke, _openSuit,  _openCard, IsCardValid, strategy);
	}
}

static int GiveCardHumanPlayer(Player* _player, int* _validCards, int _validCardsIndex, int _numOfCards)
{
	int cardIndex;
	int card;
	int i;

	card = AskCardFromPlayer(_player);
	for(i = 0; i < _validCardsIndex; ++i)
	{
		if(card == _validCards[i])
		{	
			cardIndex = FindCardIndex(_player->m_handCards, _numOfCards, card);
			DeleteCardYouGive (_player, _numOfCards -1, cardIndex);							
			sortCards(_player, NUM_OF_CARDS_IN_DECK);
			free(_validCards);
			return card;	
		}
	}

	printNotValid();
	return NOT_VALID;
}

static int GiveCardMachinePlayer(Player* _player, int(*strategy)(int*,int,int,int,int), int* _validCards, int _validCardsIndex, int _isOpenHend,  int _openCard, int _openSuit, int _numOfCards)
{
	int card;
	int cardIndex;

	card = strategy(_validCards, _validCardsIndex , _isOpenHend,  _openCard, _openSuit);
	cardIndex = FindCardIndex(_player->m_handCards, _numOfCards, card);
	DeleteCardYouGive (_player, _numOfCards -1, cardIndex);		
	sortCards(_player, NUM_OF_CARDS_IN_DECK);
	
	free(_validCards);
	return card;
}

static int fillValidCardArray(Player* _player, int(*IsCardValid)(Vector*,int,int,int,int,int), int* _validCards, size_t _numOfCards, int _isOpenHend, int _isOpenTeick, int _isHeartBreke, int _openSuit)
{
	int i;
	int card;
	int IsCardValidCheck;
	int validCardsIndex = 0;

	for(i = 0; i < _numOfCards; ++i)
	{
		VectorGet(_player -> m_handCards, i, &card);
		IsCardValidCheck = IsCardValid(_player -> m_handCards, _isOpenHend, _isOpenTeick, _isHeartBreke, card, _openSuit);
		if(IsCardValidCheck == VALID_CARD)
		{
			_validCards[validCardsIndex] = card;
			++validCardsIndex;
		}
	}
	return validCardsIndex;
}

static int FindCardIndex(Vector* _vector, int len, int card)
{
	int temp;
	int i;

	for(i = 0; i < len ; ++i)
	{
		VectorGet(_vector, i ,&temp);
		if(card == temp)
		{
			return i;	
		}
	}
}

static void DeleteCardYouGive (Player* _player, int _LatestIndex, int RemoveIndex)
{
	int temp;

	VectorGet(_player -> m_handCards, _LatestIndex , &temp);
	VectorSet(_player -> m_handCards, RemoveIndex, temp);
	VectorDelete(_player -> m_handCards, &temp);
}

int GiveCardForInitialSwap (Player * _player, int(*InitialSwapStrategy)(Player*,int)) 
{
	size_t numOfCards;
	int card;

	if(_player == NULL)
	{return ERR_NOT_INITIALIZED;}
	
	VectorItemsNum (_player -> m_handCards, &numOfCards);

	if(_player -> m_IsHuman == NO)
	{	
		return GiveCardForInitialSwapMachinePlayer(_player,InitialSwapStrategy, numOfCards);	
	}

	if(_player -> m_IsHuman == YES)
	{
		card = GiveCardForInitialSwapHumanPlayer(_player, numOfCards);
		if(card != NOT_VALID)
		{return card;}
		GiveCardForInitialSwap (_player, InitialSwapStrategy);
	}
}

static int GiveCardForInitialSwapHumanPlayer(Player* _player, int _numOfCards)
{
	int i;
	int temp;
	int card = AskCardFromPlayer(_player);
	for(i = 0; i < _numOfCards; ++i)
	{
		VectorGet(_player -> m_handCards, i , &temp);
		if(card == temp)
		{
			DeleteCardYouGive (_player, _numOfCards -1, i);
			sortCards(_player, NUM_OF_CARDS_IN_DECK);
			printPlayersHand(_player , _player -> m_playerNum);
			return card;
		}
	}	
	printNotValid();
	return NOT_VALID;
}

static int GiveCardForInitialSwapMachinePlayer(Player* _player, int(*InitialSwapStrategy)(Player*,int), int _numOfCards)
{
	int card;
	int optimalIndex = InitialSwapStrategy(_player,  _numOfCards);
	VectorGet(_player -> m_handCards, optimalIndex , &card);
	DeleteCardYouGive (_player, _numOfCards -1, optimalIndex);	
	sortCards(_player, NUM_OF_CARDS_IN_DECK);
	return card;
}

ADTErr GetCard (Player * _player, int _card) 
{
	if(_player == NULL)
	{return ERR_NOT_INITIALIZED;}
	
	VectorAdd (_player -> m_handCards, _card);
	sortCards(_player, NUM_OF_CARDS_IN_DECK);	
	return ERR_OK;
}

static ADTErr sortCards(Player* _player, int _maxValu)
{
	CountingSort(_player -> m_handCards, _maxValu);	
	return ERR_OK;
}

ADTErr IsCardExists(Player * _player, int _card)
{
	size_t numOfCards;
	int tempCards;
	int i;

	if(_player == NULL)
	{return ERR_NOT_INITIALIZED;}

	VectorItemsNum (_player -> m_handCards, &numOfCards);
	
	for(i = 0; i < numOfCards; ++i)
	{
		VectorGet(_player -> m_handCards, i, &tempCards);
		if(tempCards == _card)
		{return ERR_ELEMENT_EXIST;}
	}
	return ERR_ELEMENT_DONT_EXIST;
}

int GivePlayrCards(Player* _player, int _index)
{
	int item;
	if(_player == NULL)
	{return ERR_NOT_INITIALIZED;}
	VectorGet(_player -> m_handCards,  _index, &item);	
	return  item;
}

int HowManyCards(Player* _player)
{
	size_t numOfCards;
	if(_player == NULL)
	{return ERR_NOT_INITIALIZED;}
	VectorItemsNum (_player -> m_handCards , &numOfCards);	
	return numOfCards;
}

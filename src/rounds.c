#include "rounds.h"

struct Round 
{
	int m_numOfplayers;
	int m_howManyHuman;
	int* m_score;
	int* m_table;
	Deck* m_deck;
	Player ** m_players; 	
	int m_magicNumber;		
};

static ADTErr HandingCards(Round * _round);
static ADTErr InitialCardsSwap(Round * _round, int _numOfRound);
static void Case1(Round * _round);
static void Case2(Round * _round);
static void Case3(Round * _round);
static int Trick(Round * _round, int player, int* isHeartBreke, int _isOpenTeick);
static void printPlayersHands( Round * _round );
static int CheckIfHeartBreke(int _card, int* isHeartBreke );
static int WhoIsOpens(Round * _round);
static int CheckLoser(Round * _round, int _openSuit);
static int CalculateScore(Round * _round);
static int IsCardValid(Vector* _handCards, int _isOpenHend, int _isOpenTeick ,int _isHeartBreke, int _card, int _openSuit);
static int CheckIfOpenSuitExists(Vector* _handCards, int _numOfCards, int _openSuit);
static void Give3CardsForInitialSwap(Round * _round, int _playerIndex, int _cards[]);
static void Take3CardsForInitialSwap(Round * _round, int _playerIndex, int _cards[]);
static void TemporaryCardsSwap(int _cardsFirst[], int _cardsSecond[]);
static int PlayHand(Round* _round, int _isOpenHend, int _player, int* _isHeartBreke, int _isOpenTeick, int  _openSuit, int _openCard);

Round* RoundCreate (int _numOfplayers, int _howManyHuman, Player ** _players)
{
	Round* round;

	if(_players == NULL)
	{return NULL;}

	if ((round = ((Round*) malloc(sizeof(Round)))) == NULL)
	{return NULL;}

	if (( round -> m_table = ((int*) calloc( _numOfplayers ,sizeof(int)))) == NULL)
	{
		free(round);
		return NULL;
	}
	
	round -> m_numOfplayers = _numOfplayers;
	round -> m_howManyHuman = _howManyHuman;
	round -> m_players = _players;
	round ->  m_magicNumber = MAGIC_NUMBER2;
		
	return round;
}

void RoundDestroy (Round * _round)
{
	if(_round == NULL || _round -> m_magicNumber != MAGIC_NUMBER2)
	{return;}

	_round -> m_magicNumber = 0;
	
	free(_round -> m_table);
	free(_round);	
}

ADTErr RunRound (Round * _round, int *_score, int _numOfRound)
{
	int isHeartBreke = NO;
	int player;
	int i;
	
	if(_round == NULL || _score == NULL)
	{return ERR_NOT_INITIALIZED;}
	
	_round->m_score = _score;
	printRound(_numOfRound);

	_round->m_deck = DeckCreate(1);
	if(_round->m_deck == NULL)
	{return ERR_NOT_INITIALIZED;}
	
	DeckShuffle (_round->m_deck);
	HandingCards(_round);	
	printPlayersHands(_round);
	InitialCardsSwap(_round, _numOfRound);	
	printPlayersHands(_round);
	
	player = WhoIsOpens(_round);	
	player = Trick(_round, player, &isHeartBreke, YES);
	printPlayersHands(_round);
			
	for(i = 0; i < 12; ++i)
	{		
		player = Trick(_round, player, &isHeartBreke, NO);
		printPlayersHands(_round );	
	}
					
	DeckDestroy (_round -> m_deck);
	return ERR_OK;
}

static ADTErr HandingCards(Round * _round)
{
	int j = 0;
	int card;
	int i;

	for (i = 0; i < NUM_OF_CARDS_IN_DECK; ++i)
	{
		card = DeckPopCard (_round -> m_deck);
		GetCard(_round -> m_players[j] , card);
		j = (j+1)%(_round -> m_numOfplayers);
	}
	return ERR_OK;		
}

static void printPlayersHands( Round * _round )
{
	int i;

	if(_round -> m_howManyHuman == 0)
	{
		for(i = 0; i < _round->m_numOfplayers; ++i)
		{
			printPlayersHand(_round -> m_players[i] , i);
		}
	}
	else
	{
		for(i = 0; i < _round->m_howManyHuman; ++i)
		{
			printPlayersHand(_round -> m_players[i] , i);
		}	
	}
}

static ADTErr InitialCardsSwap(Round * _round, int _numOfRound)
{
	if(_numOfRound%4 == 0)
	{return ERR_OK;}
	
	if(_numOfRound%4 == 1)
	{
		Case1(_round);
		return ERR_OK;		
	}
	
	if(_numOfRound%4 == 2)
	{
		Case2(_round);	
		return ERR_OK;		
	}
	
	if(_numOfRound%4 == 3)
	{		
		Case3(_round);
		return ERR_OK;		
	}			
}

static void Give3CardsForInitialSwap(Round * _round, int _playerIndex, int _cards[])
{
	int i;
	for(i = 0; i < 3; ++i)
	{
 		_cards[i] = GiveCardForInitialSwap(_round ->  m_players[_playerIndex], InitialSwapStrategy);
	}
}

static void Take3CardsForInitialSwap(Round * _round, int _playerIndex, int _cards[])
{
	int i;
	for(i = 0; i < 3; ++i)
	{
 		GetCard (_round ->  m_players[_playerIndex], _cards[i]);
	}
}

static void TemporaryCardsSwap(int _cardsFirst[], int _cardsSecond[])
{
	int i;
	for(i = 0; i < 3; ++i)
	{
 		_cardsFirst[i] = _cardsSecond[i];
	}
}

static void Case1(Round * _round)
{
	int cardsFirst[3];
	int cardsSecond[3];
	int i = 0;
	
	Give3CardsForInitialSwap(_round, 0, cardsFirst);
	
	for(i = 0; i < _round->m_numOfplayers - 1; ++i) 
	{
		Give3CardsForInitialSwap(_round, i+1, cardsSecond);				
		Take3CardsForInitialSwap(_round, i+1, cardsFirst);
		TemporaryCardsSwap(cardsFirst, cardsSecond);
	}
	
	Take3CardsForInitialSwap(_round, 0, cardsFirst);		
}

static void Case2(Round * _round)
{
	int cardsFirst[3];
	int cardsSecond[3];
	int i = _round -> m_numOfplayers - 1;
	
	Give3CardsForInitialSwap(_round, i, cardsFirst);
	
	for(i = _round -> m_numOfplayers - 1; i > 0; --i)
	{
		Give3CardsForInitialSwap(_round, i-1, cardsSecond);
		Take3CardsForInitialSwap(_round, i-1, cardsFirst);
		TemporaryCardsSwap(cardsFirst, cardsSecond);
	}
		
	Take3CardsForInitialSwap(_round, _round -> m_numOfplayers - 1, cardsFirst);						
}

static void Case3(Round * _round)
{
	int cardsFirst[3];
	int cardsSecond[3];
	int i = 0;
	
	for(i = 0; i < (_round -> m_numOfplayers)/2; ++i)
	{
		Give3CardsForInitialSwap(_round, i, cardsFirst);
		Give3CardsForInitialSwap(_round, i+2, cardsSecond);				
		Take3CardsForInitialSwap(_round, i+2, cardsFirst);							
		Take3CardsForInitialSwap(_round, i, cardsSecond);						
	}	
}

static int WhoIsOpens(Round* _round)
{
	int i;

	for(i = 0; i < _round->m_numOfplayers; ++i)
	{
		if((IsCardExists(_round -> m_players[i] , 0)) == ERR_ELEMENT_EXIST)
		{
			return i;
		}
	}
}

static int Trick(Round * _round, int _player, int* _isHeartBreke, int _isOpenTeick)
{
	int openCard;
	int openSuit;
	int player = _player;
	int loser;
	int i;

	player = PlayHand(_round, YES , player, _isHeartBreke, _isOpenTeick, openSuit, openCard);
 	openCard = _round ->  m_table[_player];	
 	openSuit = ConvertFromNumberToSuit (openCard);

	for(i = 0; i < _round -> m_numOfplayers -1; i++)
	{
		player = PlayHand(_round, NO , player, _isHeartBreke, _isOpenTeick,openSuit, openCard);	
	}

	loser = CheckLoser(_round, openSuit);
	_round-> m_score[loser] = _round-> m_score[loser] + CalculateScore(_round);	
	printScore(_round -> m_score, _round -> m_numOfplayers);

	player = loser;		
	return player;
}

static int PlayHand(Round* _round, int _isOpenHend, int _player, int* _isHeartBreke, int _isOpenTeick, int  _openSuit, int _openCard)
{
	_round->m_table[_player] = GiveCard (_round->m_players[_player], _isOpenHend, _isOpenTeick, *_isHeartBreke, _openSuit, _openCard, IsCardValid, strategy);		
	CheckIfHeartBreke(_round ->  m_table[_player], _isHeartBreke );
	printTrick(_player, _round ->  m_table[_player]);	
	_player = (_player+1)%(_round -> m_numOfplayers);
	return _player;
}

static int CheckIfHeartBreke(int _card, int* isHeartBreke )
{
	if(_card >= MIN_HEARTS
	&&_card <= MAX_HEARTS)
	{
		*isHeartBreke = YES;
	}
}

static int CheckLoser(Round* _round, int _openSuit)
{
	int maxCard = 0;
	int maxIndex;
	int cardSuit;
	int i;
		
	for(i = 0; i < _round->m_numOfplayers; ++i)
	{
		cardSuit = ConvertFromNumberToSuit(_round-> m_table[i]);
				
		if(_round -> m_table[i] >= maxCard
		&& cardSuit == _openSuit)
		{
			maxCard = _round -> m_table[i];
			maxIndex = i;
		}	
	}

	return maxIndex;
}

static int CalculateScore(Round* _round)
{
	int score = 0;
	int i;

	for(i = 0; i < _round -> m_numOfplayers; ++i)
	{
		if(_round -> m_table[i] >= MIN_HEARTS
		&& _round -> m_table[i] <= MAX_HEARTS)
		{
			++score;
		}
		if(_round -> m_table[i] == SPADES_QUEEN)
		{
			score += 13;
		}	
	}

	return score;
}

static int IsCardValid(Vector* _handCards, int _isOpenHend, int _isOpenTeick ,int _isHeartBreke, int _card, int _openSuit)
{
	int ifOpenSuitExists;
	size_t numOfCards;
	int cardSuit;
	
	VectorItemsNum (_handCards, &numOfCards);
	ifOpenSuitExists = CheckIfOpenSuitExists(_handCards, numOfCards, _openSuit);

	if(_isOpenTeick == YES && _isOpenHend == YES)
	{
		if(_card == 0)
		{return VALID_CARD;}
		return NOT_VALID_CARD;
	}
	
	if(_isOpenHend == NO && ifOpenSuitExists == YES)
	{
		cardSuit = ConvertFromNumberToSuit(_card);
		if(cardSuit == _openSuit)
		{return VALID_CARD;}
		else
		{return NOT_VALID_CARD;}
	}
	
	if(_isOpenHend == YES
	&& _isHeartBreke == NO
	&& _card >= MIN_HEARTS
	&& _card <= MAX_HEARTS)
	{return NOT_VALID_CARD;}

	return VALID_CARD;							
}

static int CheckIfOpenSuitExists(Vector* _handCards, int _numOfCards, int _openSuit)
{
	int cardSuit;
	int card;
	int j;

	for(j = 0; j < _numOfCards; ++j)
	{
		VectorGet(_handCards, j, &card);
		cardSuit = ConvertFromNumberToSuit(card);
		
		if(cardSuit == _openSuit)
		{return YES;}
	}
	return NO;	
}


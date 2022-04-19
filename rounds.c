#include <stdio.h>
#include <stdlib.h>
#include "rounds.h"
#include "vector.h"
#include "players.h"
#include "deck.h"
#include "cards.h"
#include "enum.h"
#include "userInterface.h"
#define MAGIC_NUMBER2 548889

/***********************struct Round*********************/

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

/***********************StaticFunctionSignatures*********************/

static ADTErr HandingCards(Round * _round);
static ADTErr pass3Cards(Round * _round, int _numOfRound);
static void pass3CardsCase1(Round * _round, int _numOfRound);
static void pass3CardsCase2(Round * _round, int _numOfRound);
static void pass3CardsCase3(Round * _round, int _numOfRound);
static int Trick(Round * _round, int player, int* isHeartBreke, int _isOpenTeick);
void static printPlayersHands( Round * _round );
static int CheckIfHeartBreke(int _card, int* isHeartBreke );
static int WhoIsOpens(Round * _round);
static int CheckLoser(Round * _round, int _openSuit);
static int CalculateScore(Round * _round);
int IsCardValid(Vector* _handCards, int _isOpenHend, int _isOpenTeick ,int _isHeartBreke, int _card, int _openSuit);
static int CheckIfOpenSuitExists(Vector* _handCards, int _numOfCards, int _openSuit);
int strategy(int* validCards, int validCardsSize, int _isOpenHend, int _openCard, int _openSuit);
static int StrategyCase1 (int* validCards, int validCardsSize);
static int StrategyCase2 (int* validCards, int validCardsSize,  int _openCard);
static int StrategyCase3 (int* validCards, int validCardsSize);
static int StrategyCase4 (int* validCards, int validCardsSize,  int _openCard);
int strategyFor3(Player * _player,  int _numOfCards);

/***********************RoundCreate*********************/

Round* RoundCreate (int _numOfplayers, int _howManyHuman, Player ** _players)
{
Round* round;

	if(_players == NULL)
	{
		return NULL;
	}

	if ((round = ((Round*) malloc(sizeof(Round)))) == NULL)
	{
		return NULL;
	}

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

/***********************RoundDestroy*********************/

void RoundDestroy (Round * _round)
{
	if(_round == NULL || _round -> m_magicNumber != MAGIC_NUMBER2)
	{
		return;
	}

	_round -> m_magicNumber = 0;
	
	free(_round -> m_table);
	free(_round);	
}

/***********************RunRound*********************/

ADTErr RunRound (Round * _round, int *_score, int _numOfRound)
{
int isHeartBreke = 0;
int player;
int i;
	
	if(_round == NULL || _score == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	_round ->  m_score = _score;
	
	printRound(_numOfRound);

	_round -> m_deck = DeckCreate(1);
	
	DeckShuffle (_round -> m_deck);
	
	HandingCards( _round);
	
	 printPlayersHands(_round );
	
	pass3Cards(_round, _numOfRound);
	
	printPlayersHands(_round );
	
	player = WhoIsOpens(_round);
	
	player = Trick(_round, player, &isHeartBreke, 1);
	printPlayersHands(_round );
			
	for(i = 0; i < 12; i++)
	{		
		player = Trick(_round, player, &isHeartBreke, 0);
		printPlayersHands(_round );	
	}
					
DeckDestroy (_round -> m_deck);
return ERR_OK;
}

/***********************HandingCards*********************/

static ADTErr HandingCards(Round * _round)
{
int j = 0;
int card;
int i;

	for (i = 0; i < NUM_OF_CARDS_IN_DECK; i++)
	{
		card = DeckPopCard (_round -> m_deck);
		GetCard (_round -> m_players[j] , card);
		j = (j+1)%(_round -> m_numOfplayers);
	}
return ERR_OK;		
}

/***********************printPlayersHands*********************/

void static printPlayersHands( Round * _round )
{
int i;

	if(_round -> m_howManyHuman == 0)
	{
		for(i = 0; i < _round -> m_numOfplayers; i++)
		{
			printPlayersHand(_round -> m_players[i] , i);
		}
	}
	else
	{
		for(i = 0; i < _round -> m_howManyHuman; i++)
		{
			printPlayersHand(_round -> m_players[i] , i);
		}	
	}
}

/***********************pass3Cards*********************/

static ADTErr pass3Cards(Round * _round, int _numOfRound)
{
	if(_numOfRound%4 == 0)
	{
		return ERR_OK;
	}
	
	if(_numOfRound%4 == 1)
	{
		pass3CardsCase1(_round, _numOfRound);

	return ERR_OK;		
	}
	
	
	if(_numOfRound%4 == 2)
	{
		pass3CardsCase2(_round, _numOfRound);
		
	return ERR_OK;		
	}
	
	if(_numOfRound%4 == 3)
	{		
		pass3CardsCase3(_round, _numOfRound);

	return ERR_OK;		
	}			
}

/***********************pass3CardsCase1*********************/

static void pass3CardsCase1(Round * _round, int _numOfRound)
{
int card1NextI, card2NextI, card3NextI;
int card1I, card2I, card3I;
int i = 0;
	
		card1I = GiveCardFor3 (_round ->  m_players[0], strategyFor3);
		card2I = GiveCardFor3 (_round ->  m_players[0], strategyFor3);
		card3I = GiveCardFor3 (_round ->  m_players[0], strategyFor3);
		
		for(i = 0; i < _round -> m_numOfplayers - 1; i++)
		{
			card1NextI = GiveCardFor3 (_round->m_players[i+1], strategyFor3);
			card2NextI = GiveCardFor3 (_round->m_players[i+1], strategyFor3);			
			card3NextI = GiveCardFor3 (_round->m_players[i+1], strategyFor3);						
			
			GetCard (_round ->  m_players[i+1],card1I);
			GetCard (_round ->  m_players[i+1],card2I);
			GetCard (_round ->  m_players[i+1],card3I);
			 
			 card1I = card1NextI;
			 card2I = card2NextI;
			 card3I = card3NextI;
		}
		
		GetCard (_round ->  m_players[0],card1I);
		GetCard (_round ->  m_players[0],card2I);
		GetCard (_round ->  m_players[0],card3I);		
}

/***********************pass3CardsCase2*********************/

static void pass3CardsCase2(Round * _round, int _numOfRound)
{
int card1NextI, card2NextI, card3NextI;
int card1I, card2I, card3I;
int i = 0;
	
		i = _round -> m_numOfplayers - 1;
		
		card1I = GiveCardFor3 (_round->m_players[i], strategyFor3);
		card2I = GiveCardFor3 (_round->m_players[i], strategyFor3);
		card3I = GiveCardFor3 (_round->m_players[i], strategyFor3);
		
		for(i = _round -> m_numOfplayers - 1; i > 0; i--)
		{
			card1NextI = GiveCardFor3 (_round->m_players[i-1], strategyFor3);
			card2NextI = GiveCardFor3 (_round->m_players[i-1], strategyFor3);			
			card3NextI = GiveCardFor3 (_round->m_players[i-1], strategyFor3);						
		
			GetCard (_round ->  m_players[i-1],card1I);
			GetCard (_round ->  m_players[i-1],card2I);
			GetCard (_round ->  m_players[i-1],card3I);

			 card1I = card1NextI;
			 card2I = card2NextI;
			 card3I = card3NextI;
		}
		
		i = _round -> m_numOfplayers - 1;
		
		GetCard (_round ->  m_players[i],card1I);
		GetCard (_round ->  m_players[i],card2I);
		GetCard (_round ->  m_players[i],card3I);
				
}

/***********************pass3CardsCase3*********************/

static void pass3CardsCase3(Round * _round, int _numOfRound)
{
int card1NextI, card2NextI, card3NextI;
int card1I, card2I, card3I;
int i = 0;
	
	for(i = 0; i < (_round -> m_numOfplayers)/2; i++)
	{
		card1I = GiveCardFor3 (_round ->  m_players[i], strategyFor3);
		card2I = GiveCardFor3 (_round ->  m_players[i], strategyFor3);
		card3I = GiveCardFor3 (_round ->  m_players[i], strategyFor3);
			
		card1NextI = GiveCardFor3 (_round->m_players[i+2], strategyFor3);
		card2NextI = GiveCardFor3 (_round->m_players[i+2], strategyFor3);			
		card3NextI = GiveCardFor3 (_round->m_players[i+2], strategyFor3);
						
			
		GetCard (_round ->  m_players[i+2],card1I);
		GetCard (_round ->  m_players[i+2],card2I);
		GetCard (_round ->  m_players[i+2],card3I);
			
		GetCard (_round ->  m_players[i],card1NextI);
		GetCard (_round ->  m_players[i],card2NextI);
		GetCard (_round ->  m_players[i],card3NextI);

	}	
}
/***********************WhoIsOpens*********************/

static int WhoIsOpens(Round * _round)
{
int i;
	for(i = 0; i < _round -> m_numOfplayers; i++)
	{
		if((IsCardExists(_round -> m_players[i] , 0)) == ERR_ELEMENT_EXIST)
		{
			return i;
		}
	}
}

/***********************Trick*********************/

static int Trick(Round * _round, int player, int* isHeartBreke, int _isOpenTeick)
{
int openCard;
int openSuit;
int loser;
int i;

	_round ->  m_table[player] = GiveCard (_round ->  m_players[player], 1, _isOpenTeick, *isHeartBreke, openSuit, openCard, IsCardValid, strategy);	
	CheckIfHeartBreke(_round ->  m_table[player], isHeartBreke );	
	openCard = _round ->  m_table[player];	
	openSuit = ConvertFromNumberToSuit (openCard);	
	printTrick( player, _round ->  m_table[player]);	
	player = (player+1)%(_round -> m_numOfplayers);
	
	for(i = 0; i < _round -> m_numOfplayers -1; i++)
	{
		_round ->  m_table[player] = GiveCard (_round ->  m_players[player], 0, _isOpenTeick, *isHeartBreke, openSuit,openCard, IsCardValid, strategy);		
		CheckIfHeartBreke(_round ->  m_table[player], isHeartBreke );
		printTrick(player, _round ->  m_table[player]);	
		player = (player+1)%(_round -> m_numOfplayers);
	}
	
	loser = CheckLoser(_round, openSuit);

	_round ->  m_score[loser] = _round ->  m_score[loser] + CalculateScore(_round);
	
	printScore(_round -> m_score, _round -> m_numOfplayers);
	
	player = loser;
		
return player;
}

/***********************CheckIfHeartBreke*********************/

static int CheckIfHeartBreke(int _card, int* isHeartBreke )
{
	if(_card >= MIN_HEARTS
	&&_card <= MAX_HEARTS)
	{
		*isHeartBreke = 1;
	}
}

/***********************CheckLoser*********************/

static int CheckLoser(Round * _round, int _openSuit)
{
int maxCard = 0;
int maxIndex;
int cardSuit;
int i;
		
	for(i = 0; i < _round -> m_numOfplayers; i++)
	{
		cardSuit = ConvertFromNumberToSuit(_round ->  m_table[i]);
				
		if(_round -> m_table[i] >= maxCard
		 &&
		 cardSuit == _openSuit)
		{
			maxCard = _round -> m_table[i];
			maxIndex = i;
		}	
	}
return maxIndex;
}

/***********************CalculateScore*********************/

static int CalculateScore(Round * _round)
{
int score = 0;
int i;

	for(i = 0; i < _round -> m_numOfplayers; i++)
	{
		if(_round -> m_table[i] >= MIN_HEARTS
		 && _round -> m_table[i] <= MAX_HEARTS)
		{
			score++;
		}
		if(_round -> m_table[i] == SPADES_QUEEN
		)
		{
			score = score + 13;
		}	
	}
return score;
}

/***********************IsCardValid*********************/

int IsCardValid(Vector* _handCards, int _isOpenHend, int _isOpenTeick ,int _isHeartBreke, int _card, int _openSuit)
{
int ifOpenSuitExists;
size_t numOfCards;
int cardSuit;
	
	VectorItemsNum (_handCards, &numOfCards);

	ifOpenSuitExists = CheckIfOpenSuitExists(_handCards, numOfCards, _openSuit);

	if(_isOpenTeick == 1 && _isOpenHend == 1)
	{
		if(_card == 0)
		{
			return VALID_CARD;
		}
		return NOT_VALID_CARD;
	}
	
	if(_isOpenHend == 0 && ifOpenSuitExists == 1)
	{

		cardSuit = ConvertFromNumberToSuit(_card);
		if(cardSuit == _openSuit)
		{
			return VALID_CARD;		
		}
		else
		{
			return NOT_VALID_CARD;
		}
	}
	
	if(_isOpenHend == 1
	&& _isHeartBreke == 0
	&&  _card >= MIN_HEARTS
	&& _card <= MAX_HEARTS)
	{
		return NOT_VALID_CARD;	
	}

return VALID_CARD;
							
}

/***********************CheckIfOpenSuitExists*********************/

static int CheckIfOpenSuitExists(Vector* _handCards, int _numOfCards, int _openSuit)
{
int cardSuit;
int card;
int j;

	for(j = 0; j < _numOfCards; j++)
	{
		VectorGet(_handCards, j, &card);
		cardSuit = ConvertFromNumberToSuit(card);
		
		if(cardSuit == _openSuit)
		{
			return 1;	
		}
	}
return 0;	
}


/***********************strategy*********************/

int strategy(int* validCards, int validCardsSize, int _isOpenHend, int _openCard, int _openSuit)
{
int maxHeart = 0;
int i;

	if(_isOpenHend == 1)
	{
		return StrategyCase1 (validCards, validCardsSize);
			
	}
	
	if(_isOpenHend == 0)
	{		
		if(_openSuit == HEART)
		{
			StrategyCase2 (validCards, validCardsSize, _openCard);						
		}
		
		if( _openSuit == SPADE)
		{
			StrategyCase4 (validCards, validCardsSize, _openCard);
		}
		
		if( _openSuit == CLUBS || _openSuit == DIAMOND)
		{
			StrategyCase3 (validCards, validCardsSize);
				
		}				
	}
}

/***********************StrategyCase1*********************/

static int StrategyCase1 (int* validCards, int validCardsSize)
{
int maxHeart = 0;
int i;

	for(i = 0; i < validCardsSize; i++)
	{
		if(validCards[i] > maxHeart
		&& validCards[i] >= MIN_HEARTS
		&& validCards[i] <= MAX_HEARTS)
		{
			maxHeart = validCards[i];
		}		
	}
	if(maxHeart!=0)
	{
		return maxHeart;
	}
		
	for(i = validCardsSize-1; i > 0; i--)
	{
		if(validCards[i] < MIN_HEARTS
		&& validCards[i] > MAX_HEARTS
		&& validCards[i] != SPADES_QUEEN)
		{
			return validCards[i];
		}		
	}			
return validCards[0];	
}

/***********************StrategyCase2*********************/

static int StrategyCase2 (int* validCards, int validCardsSize,  int _openCard)
{
int maxHeart = 0;
int i;
	for(i = 0; i < validCardsSize; i++)
	{
		if(validCards[i] > maxHeart && validCards[i] < _openCard)
		{
			maxHeart = validCards[i];
		}		
	}
	if(maxHeart != 0)
	{
		return maxHeart;
	}
			
	for(i = validCardsSize-1; i > 0; i--)
	{
		if(validCards[i] < MIN_HEARTS
		|| validCards[i] > MAX_HEARTS)
		{
			return validCards[i];
		}		
	}
return validCards[0];				
}

/***********************StrategyCase3*********************/

static int StrategyCase3 (int* validCards, int validCardsSize)
{
int maxHeart = 0;
int max = 0;
int i;
	
	for(i = 0; i < validCardsSize; i++)
	{
		if(validCards[i] == SPADES_QUEEN)
		{
			return validCards[i];
		}		
	}
	
	for(i = 0; i < validCardsSize; i++)
	{
		if(validCards[i] > maxHeart
		&& validCards[i] >= MIN_HEARTS
		&& validCards[i] <= MAX_HEARTS)
		{
			maxHeart = validCards[i];
		}		
	}
	if(maxHeart!=0)
	{
		return maxHeart;
	}
	

	for(i = 0; i < validCardsSize; i++)
	{
		if(validCards[i] > max)
		{
			max = validCards[i];
		}		
	}
	if(max!=0)
	{
		return max;
	}
	
return validCards[0];
}

/***********************StrategyCase4*********************/

static int StrategyCase4 (int* validCards, int validCardsSize,  int _openCard)
{
int i;
	for(i = 0; i < validCardsSize; i++)
	{
		if(_openCard > SPADES_QUEEN && validCards[i] == SPADES_QUEEN)
		{
			return validCards[i];
		}		
	}

			
	for(i = 0; i < validCardsSize; i++)
	{
		if(_openCard < SPADES_QUEEN && validCards[i] != SPADES_QUEEN)
		{
			return validCards[i];
		}		
	}


return validCards[0];				
}
/***********************strategyFor3*********************/

int strategyFor3(Player * _player, int _numOfCards)
{
int* optimalCardsIndex;
int maxHeartIndex;
int maxHeart = 0;
int k = 0;
int card;
int i;

	if ((optimalCardsIndex = ((int*) calloc(_numOfCards,sizeof(int)))) == NULL)
	{
		return;
	}

	for(i = 0; i < _numOfCards; i++)
	{
		card = GivePlayrCards(_player, i);
		if(card == SPADES_QUEEN)
		{
			optimalCardsIndex[k] = i;
			k++;
		}
	}
		
	for(i = 0; i < _numOfCards; i++)
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
	
	if(k == 0)
	{
		free(optimalCardsIndex);
		return 0;	
	}

card = optimalCardsIndex[0];
free(optimalCardsIndex);
return card;

}















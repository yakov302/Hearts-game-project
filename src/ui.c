#include "ui.h"

#define HEART "\xE2\x99\xA5"
#define SPADE "\xE2\x99\xA0"
#define DIAMOND "\xE2\x99\xA6"
#define CLUB "\xE2\x99\xA3"
#define BLACK "\x1B[90m"
#define RED "\x1B[91m"
#define NORMAL "\x1B[0m"
#define INDEX "\x1B[2m" 
#define WITHE "\x1B[55m" 


char* name1[15] = { "Your", "Hila", "Orel", "Dana"};
char* name2[15] = { "You ", "Hila", "Orel", "Dana"};

static void ChooseShapeToPrint(int _suit)
{
	if(_suit == 0)
	{printf(BLACK CLUB);}

	if(_suit == 1)
	{printf(RED DIAMOND );}

	if(_suit == 2)
	{printf(RED HEART);}

	if(_suit == 3)
	{printf(BLACK SPADE);}
}

static void ChooseNumberToPrint(int cardNumber)
{
	printf(NORMAL);

	if(cardNumber == 14)
	{printf(" A  ");}

	if(cardNumber == 13)
	{printf(" K  ");}

	if(cardNumber == 12)
	{printf(" Q  ");}

	if(cardNumber == 11)
	{printf(" J  ");}

	if(cardNumber < 11)
	{printf(" %d  ", cardNumber);}	
}

void DeclareWinner(int _winNum, int _winScore)
{
	printf(NORMAL);
	printf("\ngame over!\n");
	printf("%s is the winner with only %d points.\n", name2[_winNum], _winScore);	
}

void printRound(int _numOfRound)
{
	printf(NORMAL);
	printf("\n                          Round no. %d\n", _numOfRound);
}

void printPlayersHand(Player* _player, int _playerNum)
{
	int cardNumber ;
	int Suit;
	int len;
	int i;

	if( _player == NULL)
	{return;}

	len = HowManyCards(_player);

	usleep(300000);
	printf(NORMAL);
	printf("\n%s hand\n", name1[_playerNum]);
	usleep(300000);

	for(i = 0; i < len; ++i)
	{
		Suit = ConvertFromNumberToSuit (GivePlayrCards(_player, i)) ;
		cardNumber = ConvertFromNumberToCardNumber (GivePlayrCards(_player, i), Suit);
		ChooseShapeToPrint(Suit);
		ChooseNumberToPrint(cardNumber);
	}

	printf("\n");
	printf(INDEX);
	for(i = 0; i < len && i < 11; ++i)
	{
		printf(" %d   ", i);
	}
	for(i = 11; i < len; ++i)
	{
		printf(" %d  ", i);
	}
	printf("<- index\n\n");
}

void printTrick(int _playerNum, int _card)
{
	int cardNumber;	
	int Suit;

	usleep(300000);
	Suit = ConvertFromNumberToSuit (_card) ;
	cardNumber = ConvertFromNumberToCardNumber (_card, Suit);
	printf(NORMAL);	
	printf("%3s put card: ", name2[_playerNum]);	
	ChooseShapeToPrint(Suit);
	ChooseNumberToPrint(cardNumber);
	printf("\n");
}

void printScore(int* _score, int _numOfPlayers)
{
	int i;
	
	if( _score == NULL)
	{return;}

	printf("\n");
	for(i = 0; i < _numOfPlayers; ++i)
	{
		usleep(300000);
		printf(NORMAL);
		printf("%s score: %d\n",name1[i], _score[i]);			
	}
}

int AskCardFromPlayer(Player* _player)
{
	int index;
	int card;

	if(_player == NULL)
	{return ERR_NOT_INITIALIZED;}

	printf(NORMAL);
	printf(INDEX);
	printf("Pick index: ");
	scanf("%d", &index);
	card = GivePlayrCards(_player, index);
	
	return card;
}

void printNotValid(void)
{
	printf(NORMAL);
	printf(RED);
	printf("                        -> Not valid <- \n");
}


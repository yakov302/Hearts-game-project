#include "cards.h"

Suit ConvertFromNumberToSuit (int _num) 
{
	Suit suit;
	suit = _num/13;
	return suit;	
}

CardNumber ConvertFromNumberToCardNumber (int _num, int _suit) 
{
	CardNumber cardNumber;
	cardNumber = (_num - 13*(_suit)) + 2;
	return cardNumber;
}

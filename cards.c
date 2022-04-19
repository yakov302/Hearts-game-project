#include <stdio.h>
#include <stdlib.h>
#include "cards.h"

/***********************ConvertFromNumberToSuit*********************/

Suit ConvertFromNumberToSuit (int _num) 
{
Suit suit;
	suit = _num/13;
	return suit;	
}

/***********************ConvertFromNumberToCardNumber*********************/

CardNumber ConvertFromNumberToCardNumber (int _num, int _suit) 
{
CardNumber n;
	n = (_num - 13*(_suit)) + 2;
	return n;
}






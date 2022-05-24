#ifndef __CARDS_H__
#define __CARDS_H__

typedef enum Suit {CLUBS, DIAMOND, HEART, SPADE, NUM_OF_SUITS}Suit;
typedef enum CardNumber {TWO, THREE, FOUR ,FIVE ,SIX ,SEVEN ,EIGHT ,NINE ,TEN ,PRINCE ,QUEEN ,KING ,ACE, NUM_OF_RANK}CardNumber; 

#define NUM_OF_CARDS_IN_DECK NUM_OF_SUITS*NUM_OF_RANK
#define MIN_HEARTS NUM_OF_RANK*HEART
#define MAX_HEARTS NUM_OF_RANK*(HEART+1) -1
#define SPADES_QUEEN NUM_OF_RANK*SPADE + QUEEN

/*Description:
Convert From Number To Suit.

Input:
 _num - Card number (according to the numbering of the software).

Output:
suit - suit number.*/
Suit ConvertFromNumberToSuit (int _num);

/*Description:
Convert From Number To CardNumber

Input:
 _num - Card number (according to the numbering of the software).
 suit - suit number.

Output:
n - Card number (according to the numbering of the cards deck. A equals 14)*/
CardNumber ConvertFromNumberToCardNumber (int _num, int _suit);


#endif // __CARDS_H__

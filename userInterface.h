#ifndef __USERINTERFACE_H__
#define __USERINTERFACE_H__

/*Description:
Prints that the game is over, the name of the winner and his number of points.

Input:
_winNum - Number (index) of the winning player.
_winScore - Number of points of the winning player.*/
void DeclareWinner(int _winNum, int _winScore);

/*Description:
Prints the round number.

Input:
_numOfRound - the round number.*/
void printRound(int _numOfRound);

/*Description:
Prints all the cards the player has.

Input:
player - Pointer to player structure.
_playerNum - player number (index). */
void printPlayersHand(Player* _player, int _playerNum);

/*Description:
Prints the card the player puts on the table.

Input:
_playerNum - player number (index). 
_card - the card the player puts on the table.*/
void printTrick(int _playerNum, int _card);

/*Description:
Prints the scores of all players.

Input:
_score - Pointer to the score array.
_numOfPlayers - Number of players.*/
void printScore(int* _score, int _numOfPlayers);

/*Description:
Asks a human player to index the card he chooses and gives it to GiveCard function.

Input:
player - Pointer to player structure.

Output:
card - the card he chooses.*/
int AskCardFromPlayer(Player* _player);

/*Description:
Prints "Not valid!" when the player makes an invalid chooses.*/
void printNotValid(void);

#endif /*#ifndef__USERINTERFACE_H__*/

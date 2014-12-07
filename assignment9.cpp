// ___  __ 
//|__ \/_ |
//   ) || |
//  / / | |
// / /_ | |
//|____||_|

/*=================================
Program name: 21
Developer name: Aaron Schraner
Date: 11/26/2014
Purpose: A C++ implementation of 21
===================================*/

//requires C++11 support
#include <iostream>
#include "libcards2.h"
using namespace std;

/*
 * Name: resetGame
 * Purpose: reset the game deck of cards
 * Arguments: gameDeck (Deck) - the deck to reset
 *
 * 1. erases the deck
 * 2. populates it with an ordered set of 52 cards
 * 3. shuffles that deck.
 */
const char resetScr[]= { 0x1B , 0x5B , 0x48 , 0x1B , 0x5B , 0x32 , 0x4A };
void clearScreen()
{
#ifndef WINDOWS
	cout << resetScr;
#else
	system("cls");
#endif
}
void resetGame(Deck &gameDeck)
{
	clearScreen();
	gameDeck.clear();
	gameDeck.populate52();
	gameDeck.shuffle();
}

/*
 * Name: yesOrNo
 * Purpose: get a "yes" or "no" from the user in a convenient way
 * Arguments:
 * 	- prompt (string) : What the program should ask the user. 
 * 			(e.g. "would you like to continue")
 * Returns: if user entered yes (bool)
 *
 * --Persists until a valid input is entered. (y or n) --
 */
bool yesOrNo(string prompt)
{

	cout << endl << prompt << "\n> ";

	char response;
	bool goodres=false, result;
	while(!goodres)
	{
		cin >> response;
		switch(response)
		{
			case 'y':
			case 'Y':
				result=true;
				goodres=true;
				break;
			case 'n':
			case 'N':
				result=false;
				goodres=true;
				break;
			default:
				cout << "Invalid input.\n> ";
				break;
		}
	}
	return result;
}

/*
 * Name: winnerLogic
 * Purpose: Print a message indicating who won the game.
 * Arguments:
 *  - dealerHand : the dealer's hand
 *  - playerHand : the player's hand
 * Returns: void
 */
void winnerLogic(Deck &dealerHand, Deck &playerHand)
{
	if(playerHand.getScore() <= WINLIMIT && dealerHand.getScore() <= WINLIMIT)
	{
		if(playerHand.getScore() == WINLIMIT || playerHand.getScore() > dealerHand.getScore())
		{
			cout << "Player has won!\n";
			if(playerHand.getScore() == WINLIMIT)
				cout << "FLAWLESS VICTORY.\n";
		}
		else if(playerHand.getScore() < dealerHand.getScore() || dealerHand.getScore() == WINLIMIT)
		{
			cout << "Dealer has won!\n";
		}
	}
	else if(playerHand.getScore() > WINLIMIT)
	{
		cout << "You went too high! Dealer wins by default.\n";
	}
	else
	{
		cout << "Dealer went too high! You win!\n";
	}
}

/* Name: deal4cards(gameDeck, dealerHand, playerHand)
 * Purpose: deal 4 cards and ensure that the game is not immediately over
 * Parameters: gameDeck, dealerHand, playerHand
 */
void deal4cards(Deck &gameDeck, Deck &dealerHand, Deck &playerHand)
{

	do
	{
		playerHand.clear();
		dealerHand.clear();
		//clear decks

		gameDeck.deal(dealerHand);
		gameDeck.deal(playerHand);
		gameDeck.deal(dealerHand);
		gameDeck.deal(playerHand);
		//deal 4 cards, 2 to each player

	} while ( haswinner(playerHand,dealerHand) );
}

//main loop
int main()
{
	Deck gameDeck, playerHand, dealerHand;
	//declare the decks for the game
	
	do
	{
		resetGame(gameDeck);
		//reset the game deck (reset and reshuffle)

		cout << "Playing with score limit " << WINLIMIT << ".\n";
		//tell user what the compiled maximum score is

		cout << "Dealing cards...\n";
		deal4cards(gameDeck, dealerHand, playerHand);
		//deal 4 cards: 2 to the dealer and 2 to the player.

		dealerHand.setHidden(0,true);
		//hide the dealer's first card



		//show the dealer's hand (with first card hidden)
		cout << "Dealer's hand:\n";
		dealerHand.printAA();
		
		//show the player's hand
		cout << "Your hand:\n";
		playerHand.printAA();
		cout << "[Your score: " << playerHand.getScore() << "]\n\n";
		//
		bool playerDone=false;

		//Actual game loop//
		while(!haswinner(playerHand, dealerHand) && !playerDone)
		{

			//find if player wants another card
			if(yesOrNo("Do you want another card?"))
			{
				clearScreen();
				cout << "\n\n";

				cout << "Dealer's hand: \n";
				dealerHand.printAA();
				gameDeck.deal(playerHand);
				cout << "Your hand:\n";
				playerHand.printAA();
				cout << "[Your score: " << playerHand.getScore() << "]\n";
			}
			else
			{
				playerDone=true;
			}
		}
		dealerHand.setHidden(0,false);
		//end game loop//
		if(playerHand.getScore() <= WINLIMIT)
		{

			cout << "Dealer's turn.\nDealing cards....\n";
			while(dealerHand.getScore() <= WINLIMIT-4)
			{
				gameDeck.deal(dealerHand);
			}
			//Let the dealer get some cards	

			cout << "Dealer's hand: \n";
			dealerHand.printAA();
			cout << "Dealer score: " << dealerHand.getScore() << endl;
			cout << "Your score: " << playerHand.getScore() << endl;
		}
		winnerLogic(dealerHand, playerHand);
		//winning logic

		cout << "Game over.";

	}while(yesOrNo("Would you like to play again?"));
	//keep running the game until user wants to stop
	return 0;
}

/*=============================
Program name: libcards V2
Developer name: Aaron Schraner
Date: 11/24/2014
Purpose: Powerful card game API
===============================*/

// this file handles the bulk of card operations. //

//includes
#include <iostream>
#include <time.h>
#include <string>
#include <vector>

//suit definitions
#define SUIT_CLUBS 0x00
#define SUIT_DIAMONDS 0x20
#define SUIT_HEARTS 0x40
#define SUIT_SPADES 0x60

//rank definitions
#define RANK_ACE 0x01
#define RANK_JACK 0x0B
#define RANK_QUEEN 0x0C
#define RANK_KING 0x0D

//bit access holders
#define RANKBITS 0x0F // b00001111
#define SUITBITS 0x60 // b00110000
//all rank and suit definitions are libcards V1 compliant

//other constants
#ifndef SHUFFLE_THOROUGHNESS
#define SHUFFLE_THOROUGHNESS 10000
#endif
#ifndef WINLIMIT
#define WINLIMIT 21
#endif

/*
 * All classes and functions defined here are designed
 * to be used with any and all types of card games. No
 * function is exclusive to the 21 card game except 
 * getScore() and hasWinner(deck1, deck2).
 * This library is intended to be used for any type of
 * game that uses digital cards.
 */

using namespace std;
//Card class
//for cards
class Card
{
	public:
		char suitAA[4][3][6] = {
			{
				" ( ) ",
				"(   )",
				" /_\\ "},
			{
				" /\\  ",
				"<  > ",
				" \\/  "},
			{
				" _ _ ",
				"( v )",
				" \\ / "},
			{
				" /\\  ",
				"(  ) ",
				" /\\  "}
		};
		char suit; //card suit 
		char rank; //card rank
		bool hidden=false;

		/*
		 * Name: init(suit,rank)
		 * Purpose: populate the card's suit and rank with the specified arguments
		 */
		void init(char suit,char rank)
		{
			this->suit=suit;
			this->rank=rank;
		}

		/*
		 * Name: fromChar(oldchar)
		 * Purpose: populate the card from an 8-bit format card
		 * Provided for compatibility with older version, deprecated
		 */
		void fromChar(char oldchar)
		{
			suit=oldchar&SUITBITS;
			rank=oldchar&RANKBITS;
		}

		/*
		 * Name: getrank()
		 * Purpose: Get character to represent rank of card
		 * A: Ace
		 * X: 10
		 * J: Jack
		 * Q: Queen
		 * K: King
		 */
		char getrank()
		{
			switch(rank)
			{
				case RANK_ACE:
					return 'A';
					break;
				case 10:
					return 'X';
					break;
				case RANK_JACK:
					return 'J';
					break;
				case RANK_QUEEN:
					return 'Q';
					break;
				case RANK_KING:
					return 'K';
					break;
				default:
					return rank + '0';
					break;
			}
		}

		/*
		 * Name: printWin()
		 * Purpose: print using windows card characters
		 * Not used by default due to lack of Linux support
		 */
		string toWinString()
		{
			string result="[";
			result += (char) (suit/SUIT_DIAMONDS + 3);
			if(rank==10)
				result+="10";
			else
				result += getrank();
			result += "] ";
			return result;
		}
		/*
		 * Name: toString()
		 * Purpose: return a string format version of the card
		 * Used for simple printing
		 */
		string toString()
		{
			string result="[";
			switch(suit)
			{
				case SUIT_CLUBS:
					result+="C";
					break;
				case SUIT_DIAMONDS:
					result+="D";
					break;
				case SUIT_HEARTS:
					result+="H";
					break;
				case SUIT_SPADES:
					result+="S";
					break;
			}
			result += getrank();
			result += "]";
			if(hidden)
				result="[--]";

			return result;
		}

		/*
		 * Name: toChar()
		 * Purpose: return an 8-bit format copy of the card
		 * Provided for compatibility with older versions, deprecated
		 */
		char toChar()
		{
			return suit|rank;
		}

		/*
		 * Name: addAAto(display[])
		 * Purpose: append the card's ASCII art to a virtual display (string array)
		 */
		void addAAto(string display[])
		{
			if(!hidden)
			{
				display[0] += " -------  ";
				if(getrank()=='X')
				{
					display[1] += "|10";
					display[1] += suitAA[(int)(suit/SUIT_DIAMONDS)][0];
					display[1] += "| ";
				}
				else
				{
					display[1] += "|";
					display[1] += getrank();
					display[1] += " ";
					display[1] += suitAA[(int)(suit/SUIT_DIAMONDS)][0];
					display[1] += "| ";
				}
				display[2] += "|  "; 
				display[2] += suitAA[(int)(suit/SUIT_DIAMONDS)][1];
				display[2] += "| ";

				display[3] += "|  "; 
				display[3] += suitAA[(int)(suit/SUIT_DIAMONDS)][2];
				display[3] += "| ";
				display[4] += " -------  ";
			}
			else
			{
				display[0] += " -------  ";
				display[1] += "|--/////| ";
				display[2] += "|///////| ";
				display[3] += "|///////| ";
				display[4] += " -------  ";
			}
		}
};

/*
 * Name: Deck
 * Purpose: is a sort of wrapper for a vector of Cards.
 * Has built-in functions for appending, dealing, filling with 52-card standard deck, printing, shuffling, etc.
 */
class Deck
{
	public:
		
		//vector of cards to manipulate
		vector<Card> cards;

		/*
		 * Name: addCard(card)
		 * Purpose: append the specified card to the deck
		 */
		void addCard(Card card)
		{
			cards.push_back(card);
		}

		/*
		 * Name: printWin()
		 * Purpose: print the card deck
		 * (windows compatible version)
		 */
		void printWin()
		{
			int i=0;
			for (Card card : cards)
			{
				if(i%13==0)
					cout << endl;
				cout << card.toWinString() << " ";
				i++;
			}
			cout << endl;
		}

		/*
		 * Name: init()
		 * Purpose: fill cards with empty data
		 * Not really used but it's there.
		 */
		void init()
		{
			for ( Card card : cards)
			{
				card.init(0,0);
			}
		}

		/*
		 * Name: populate52()
		 * Purpose: Add a 52-card standard deck to this deck
		 */
		void populate52()
		{
			for(int i=0;i<52;i++)
			{
				Card newCard;
				newCard.init(i/13*SUIT_DIAMONDS,i%13+1);
				addCard(newCard);
			}
		}
		
		/*
		 * Name: print()
		 * Purpose: display the deck in a plain format
		 * (no ascii art)
		 */
		void print()
		{
			int i=0;
			for (Card card : cards)
			{
				if(i%13==0)
					cout << endl;
				cout << card.toString() << " ";
				i++;
			}
			cout << endl;
		}

		/*
		 * Name: shuffle()
		 * Purpose: shuffle the cards
		 * Uses SHUFFLE_THOROUGHNESS to determine how many times the algorithm should run
		 * 10,000 seems to work well.
		 */
		void shuffle()
		{
			static int seedoffset;
			for(int x=0;x<SHUFFLE_THOROUGHNESS;x++)
			{
				Card tempcard;
				int i1;
				int i2;

				srand(time(NULL)+seedoffset);
				i1=rand()%52;
				srand(x+seedoffset);
				i2=rand()%52;
				//generate two random numbers

				tempcard=cards[i2];
				cards[i2]=cards[i1];
				cards[i1]=tempcard;
				seedoffset++;
			}
		}

		/*
		 * Name: deal(toDeck)
		 * Purpose: move a card from this deck to another deck (toDeck) 
		 * Removes the top card in this deck and puts it on top of toDeck.
		 */
		void deal(Deck &toDeck)
		{
			Card sharecard;
			sharecard=cards.back();
			toDeck.addCard(sharecard);
			cards.pop_back();
		}

		/*
		 * Name: printAA()
		 * Purpose: print the deck in Ascii art
		 * card characters don't work on my Linux setup
		 */
		void printAA()
		{
			string display[6];

			for (unsigned int i=0;i<cards.size();i++)
			{
				cards[i].addAAto(display);
				if(i%8==7 || i==cards.size()-1)
				{
					for(int x=0;x<6;x++)
					{
						cout << display[x] << endl;
						display[x]="";
					}
				}
			}
		}

		/*
		 * Name: setHidden(index,hidden)
		 * Purpose: sets whether or not a card should be hidden
		 */
		void setHidden(int index, bool hidden)
		{
			cards[index].hidden=hidden;
		}
		int getScore()
		{
			int score=0,aces=0;
			for( Card card : cards)
			{
				score += (int)card.rank;
				if(card.rank==RANK_ACE)
				{
					aces++;
					score+=10;
				}
			}
			while ( score > WINLIMIT && aces>0)
			{
				aces--;
				score-=10;
			}
			return score;
		}
		void clear()
		{
			cards.clear();
		}
};
//Many of these methods will not be useful until we make an actual game.
bool haswinner(Deck deck1, Deck deck2)
{
	return (deck1.getScore() >= WINLIMIT || deck2.getScore() >= WINLIMIT);
}

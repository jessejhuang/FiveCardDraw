// Author : Danny Weiner
// Purpose: define that which is declared in fiveCardDraw.h, to be used in lab3

//#include "stdafx.h"
#include "poker.h"
#include "deck.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

int usage(char * program_name, char * error_message, int message) {
	std::cout << "Usage: " << program_name << " experienced error: " << error_message << endl;
	return message;
}

/*helper functions for parseHands*/

//find a particular int in a vector of ints
bool found(const std::vector<int> & ints, const int x) {
	return std::find(ints.begin(), ints.end(), x) != ints.end();
}
//check whether a sorted hand is a straight
bool straightBool(const std::vector<Card> &hand) {
	return (hand[4].r == (hand[3].r + 1)) && (hand[3].r == (hand[2].r + 1)) && (hand[2].r == (hand[1].r + 1)) && (hand[1].r == (hand[0].r + 1));
}

//take in a vector of cards (any length) and determine the hands it holds
void parseHand(Hand & hand) {
	string printout;
	std::sort(hand.handv.begin(), hand.handv.end()); //sort this hand, based on the operator< we defined
	printout = "no rank"; //only overwrite this if a valid hand is later found

	bool flushBool = (hand.handv[0].s == hand.handv[1].s && hand.handv[0].s == hand.handv[2].s && hand.handv[0].s == hand.handv[3].s && hand.handv[0].s == hand.handv[4].s);
	if (flushBool) { //same suit
		if (straightBool(hand.handv)) {
			printout = "straight flush";
			hand.h = straightFlush;
		}
		else { //same suit but not straight
			printout = "flush";
			hand.h = HANDRANKINGS::flush;
		}
	}
	Hand handcopy = hand; //make a copy of the vector, convert all suits to the same one (Clubs, arbitrarily)
	std::vector<int> handRanks(5, 0);
	for (size_t i = 0; i < 5; ++i) {
		handcopy.handv[i].s = Clubs;
		handRanks[i] = hand.handv[i].r;
	}
	std::sort(handcopy.handv.begin(), handcopy.handv.end()); //sort again, now removing suit from the equation, so we can compare more easily for the sake of detecting full houses

															 //fullHouseBool
	bool a3 = (handcopy.handv[0].r == handcopy.handv[1].r && handcopy.handv[0].r == handcopy.handv[2].r); //[XXX]YY
	bool a2 = (handcopy.handv[3].r == handcopy.handv[4].r); //XXX[YY]
	bool b3 = (handcopy.handv[2].r == handcopy.handv[3].r && handcopy.handv[2].r == handcopy.handv[4].r); //XX[YYY]
	bool b2 = (handcopy.handv[0].r == handcopy.handv[1].r); //[XX]YYY
	if (a3 && a2) {
		hand.sigCard = handcopy.handv[0];
		hand.sigCard2 = handcopy.handv[3];
	}
	else if (b3 && b2) {
		hand.sigCard = handcopy.handv[3];
		hand.sigCard2 = handcopy.handv[0];
	}
	bool fullHouseBool = ((a3 && a2) || (b3 && b2)); //XXXYY or XXYYY


	if (straightBool(handcopy.handv) && !flushBool) { //check for a straight, in the context of a false flush, but accounting for a real flush, to circumvent the less operator's suit ordering
		printout = "straight";
		hand.h = straight;
		hand.sigCard = hand.handv[0];
		hand.sigCard2 = hand.handv[1];
		hand.sigIndex = 0;
	}
	else if (fullHouseBool) {
		printout = "full house";
		hand.h = fullHouse;
	}

	bool paired = false; //have we seen a pair yet?
	int pairedRank; //track the rank of the first pair found
	bool found3or4 = false; //no need to look at other cards if we've already found a "three of a kind" or "four of a kind"
	if (printout == "no rank") { //meaning we have not yet overwritten with a valid hand - this should be a redundant check and exists as a precaution	
		for (size_t i = 0; i < 5; ++i) { //go through each card in the hand
			if (!found3or4) { //no need to look at other cards if we've already found a "three of a kind" or "four of a kind"
				switch (std::count(handRanks.begin(), handRanks.end(), hand.handv[i].r)) { //count the number of times the rank of each card in the hand appears
				case 4:
					printout = "four of a kind";
					hand.h = fourOfAKind;
					hand.sigCard = hand.handv[i];
					hand.sigCard2 = hand.handv[1];
					hand.sigIndex = 0;
					found3or4 = true;
					break;
				case 3:
					if (!fullHouseBool) { //redundant check
						printout = "three of a kind";
						hand.h = threeOfAKind;
						hand.sigCard = hand.handv[i];
						hand.sigCard2 = hand.handv[1];
						hand.sigIndex = 0;
						found3or4 = true;
					}
					break;
				case 2:
					if (!paired) {
						pairedRank = hand.handv[i].r;
						printout = "one pair";
						hand.sigCard = hand.handv[i];
						hand.sigCard2 = hand.handv[1];
						hand.sigIndex = 0;
						paired = true;
					}
					else if (hand.handv[i].r != pairedRank) {
						printout = "two pairs";
						hand.sigCard2 = hand.handv[i];
					}
					break;
				case 1:
					hand.sigIndex = i;
				default:
					break;
				}
			}
		}
	}
	if (printout == "one pair") { //account for the last few hand rank groups
		hand.h = onePair;
	}
	else if (printout == "two pairs") { //confirm final result of case 2
		hand.h = twoPairs;
	}
	else if (printout == "no rank") { //IFF printout STILL equals "no rank"
		hand.h = noRank;
		hand.sigCard = hand.handv[0];
		hand.sigCard2 = hand.handv[1];
		hand.sigIndex = 0;
	}
	//std::cout << printout << endl; //print this hand's rank without helper function
	//std::cout << hand.h << std::endl;
	//return hand;
}

//return TRUE if the first hand (hand2) ranks higher than the second hand (hand1): hand2 > hand1
//extra credit from previous lab
bool poker_rank(const Hand & unrankedHand2, const Hand & unrankedHand1) {
	Hand hand1 = unrankedHand1;
	parseHand(hand1); //assign sigCard, sigIndex as needed
	Hand hand2 = unrankedHand2;
	parseHand(hand2); //^ditto

	if (hand1.h == hand2.h) {
		switch (hand1.h) {
		case 0: //no rank
			for (size_t i = hand1.size() - 1; i >= 0; --i) {
				if (hand1.handv[i] != hand2.handv[i]) {
					return (hand1.handv[i] < hand2.handv[i]);
				}
			}
			return false;
			break;
		case 1: //one pair
			if (hand1.sigCard != hand2.sigCard) {
				return (hand1.sigCard < hand2.sigCard);
			}
			else {
				for (size_t i = hand1.size() - 1; i >= 0; --i) {
					if (hand1.handv[i] != hand2.handv[i] && hand1.handv[i].r != hand1.sigCard.r && hand2.handv[i].r != hand2.sigCard.r) {
						return (hand1.handv[i] < hand2.handv[i]);
					}
				}
			}
			return false;
			break;
		case 2: //two pairs
			Card highPair = hand1.sigCard2;
			Card lowPair = hand1.sigCard;
			if (hand1.sigCard2 < hand1.sigCard) {
				highPair = hand1.sigCard;
				lowPair = hand1.sigCard2;
			}

			Card highPair2 = hand2.sigCard2;
			Card lowPair2 = hand2.sigCard;
			if (hand2.sigCard2 < hand2.sigCard) {
				highPair2 = hand2.sigCard;
				lowPair2 = hand2.sigCard2;
			}

			if (highPair != highPair2) {
				return (highPair < highPair2);
			}
			else if (lowPair != lowPair2) {
				return (lowPair < lowPair2);
			}
			else {
				return (hand1.handv[hand1.sigIndex] < hand2.handv[hand2.sigIndex]);
			}
			break;
		case 3: //three of a kind
			return (hand1.sigCard < hand2.sigCard);
			break;
		case 4: //straight
			for (size_t i = hand1.size() - 1; i >= 0; --i) {
				if (hand1.handv[i] != hand2.handv[i]) {
					return (hand1.handv[i] < hand2.handv[i]);
				}
			}
			return false;
			break;
		case 5: //flush
			for (size_t i = hand1.size() - 1; i >= 0; --i) {
				if (hand1.handv[i] != hand2.handv[i]) {
					return (hand1.handv[i] < hand2.handv[i]);
				}
			}
			return false;
			break;
		case 6: //full house
			if (hand1.sigCard != hand2.sigCard) {
				return (hand1.sigCard < hand2.sigCard);
			}
			else {
				return (hand1.sigCard2 < hand2.sigCard2);
			}
			break;
		case 7: //four of a kind
			return (hand1.sigCard < hand2.sigCard);
			break;
		case 8: //straight flush
			return hand1.handv[4] < hand2.handv[4];
			break;
		default:
			return false;
			break;
		}
	}
	else {
		return (hand1.h < hand2.h);
	}
}

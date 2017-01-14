#pragma once

// Author : Danny Weiner
// Purpose: lab3 Hand class declarations


#ifndef HAND_H
#define HAND_H
#include "card.h"
#include "deck.h"
#include <vector>
#include <string>

enum HANDRANKINGS {
	noRank = 0,
	onePair = 1,
	twoPairs = 2,
	threeOfAKind = 3,
	straight = 4,
	flush = 5,
	fullHouse = 6,
	fourOfAKind = 7,
	straightFlush = 8
};

class Hand {
	friend std::ostream & operator<< (std::ostream &, const Hand &);
	friend void operator<< (Hand &h, Deck &d);
	friend void operator<< (Deck &d, Hand &h);
	friend bool poker_rank(const Hand & hand2, const Hand & hand1);
	friend void parseHand(Hand & hand);
public:
	//constructors
	Hand();
	Hand(const Hand & otherH);
	//destructors
	~Hand();

	int size() const;
	std::string toString() const;
	void remove_card(size_t &i);

	void operator= (const Hand &);
	bool operator< (const Hand &) const;
	bool operator== (const Hand &) const;
	Card operator[] (size_t & i) const;

	Card sigCard; //store one particular card of significance
	Card sigCard2; //store another card of significance
	int sigIndex; //store one particular index of significance
	HANDRANKINGS h;
private:
	std::vector<Card> handv = std::vector<Card>(5);
};


#endif /* HAND_H */
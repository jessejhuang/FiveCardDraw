#pragma once

// Author : Danny Weiner
// Purpose: lab3 Deck class declarations


#ifndef DECK_H
#define DECK_H
#include "card.h"
#include <vector>

//forward declaration
class Hand;

class Deck {
	friend std::ostream & operator<< (std::ostream &, const Deck &);
	friend void operator<< (Hand &h, Deck &d);
	friend void operator<< (Deck &d, Hand &h);
	friend void operator<< (Deck &d1, Deck &d2);
public:
	//constructors
	Deck();
	Deck(const char * filename);

	//destructors
	~Deck();

	//functions
	int size() const;
	void shuffle();
	void add_card(Card & c);
private:
	std::vector<Card> deckv;
	int load(const char * filename);
	int loadHelper(std::string word, int index);

};

#endif /* DECK_H */
#pragma once

// Author : Danny Weiner
// Purpose: Card declarations


#ifndef CARD_H
#define CARD_H
#include <iostream>

enum SUITS {
	Clubs = 0,
	Diamonds = 1,
	Hearts = 2,
	Spades = 3
};

enum RANKS {
	two = 2,
	three = 3,
	four = 4,
	five = 5,
	six = 6,
	seven = 7,
	eight = 8,
	nine = 9,
	ten = 10,
	jack = 11,
	queen = 12,
	king = 13,
	ace = 14
};

struct Card {
	SUITS s;
	RANKS r;
	bool operator< (const Card &) const;
	bool operator== (const Card &) const;
	bool operator!= (const Card &) const;
};


std::ostream & operator<< (std::ostream &, const Card &);

#endif /* CARD_H */
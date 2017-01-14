#pragma once

// Author : Jesse Huang, Kate Hao Danny Weiner
// Purpose: declarations for derived class from Game


#ifndef FIVECARDDRAW_H
#define FIVECARDDRAW_H

#include "Game.h"

class FiveCardDraw : public Game {
protected:
	size_t dealer;
	Deck discard_deck;
public:
	FiveCardDraw();
	virtual ~FiveCardDraw();
	virtual int before_turn(Player& p);
	virtual int turn(Player& p);
	virtual int after_turn(Player& p);
	virtual int before_round();
	virtual int round();
	virtual int after_round();
};

bool poker_rank(std::shared_ptr<Player> & p1, std::shared_ptr<Player> & p2);

#endif /* FIVECARDDRAW_H */

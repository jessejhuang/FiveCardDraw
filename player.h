#pragma once

// Author : Jesse Huang, Danny Weiner
// Purpose: Player declarations


#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>

struct Player {
	std::string name;
	Hand playerCards;
	unsigned int won;
	unsigned int lost;
	Player(std::string filename);
	friend bool operator==(const Player& a, const Player& b);
};

std::ostream & operator<< (std::ostream &, const Player &);
bool operator==(const Player& a, const Player& b);
bool isInt(std::string s);
#endif /* PLAYER_H */

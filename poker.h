#pragma once

// Author : Danny Weiner
// Purpose: lab3 general declarations


#ifndef POKER_H
#define POKER_H
#include "hand.h"

int usage(char * program_name, char * error_message, int message);

void parseHand(Hand & hand);

bool found(const std::vector<int> & ints, const int x);

bool straightBool(const std::vector<Card> &hand);

bool poker_rank(const Hand & hand2, const Hand & hand1);

enum RESULT_CODES {
	success = 0,
	could_not_read = 1,
	no_filename = 2,
	two_args_no_shuffle = 3,
	no_args = 4,
	too_many_args = 5,
	invalid_position = 6,
	not_enough_args = 7,
	no_cards_to_deal = 8,
	caught_exception = 9,
	unknown_error = 10
};

#endif /* POKER_H */
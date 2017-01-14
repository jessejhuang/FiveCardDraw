// Author : Danny Weiner
// Purpose: define that which is declared in card.h, to be used in lab3

//#include "stdafx.h"
#include "card.h"
#include <string>


bool Card::operator<(const Card & otherC) const {
	if (s == otherC.s) {
		return (r < otherC.r);
	}
	else {
		return (s < otherC.s);
	}
}

bool Card::operator==(const Card & otherC) const { //equality comparator
	return (r == otherC.r && s == otherC.s);
}

bool Card::operator!=(const Card & otherC) const { //inequality comparator
	return (r != otherC.r && s != otherC.s);
}

std::ostream & operator<< (std::ostream &o, const Card &c) { //make individual cards printable without a helper function
	std::string printout = "";
	switch (c.r) {
	case jack:
		printout += 'J';
		break;
	case queen:
		printout += 'Q';
		break;
	case king:
		printout += 'K';
		break;
	case ace:
		printout += 'A';
		break;
	case two:
		printout += '2';
		break;
	case three:
		printout += '3';
		break;
	case four:
		printout += '4';
		break;
	case five:
		printout += '5';
		break;
	case six:
		printout += '6';
		break;
	case seven:
		printout += '7';
		break;
	case eight:
		printout += '8';
		break;
	case nine:
		printout += '9';
		break;
	case ten:
		printout += "10";
		break;
	default:
		break;
	}
	switch (c.s) {
	case Clubs:
		printout += 'C';
		break;
	case Diamonds:
		printout += 'D';
		break;
	case Hearts:
		printout += 'H';
		break;
	case Spades:
		printout += 'S';
		break;
	default:
		break;
	}

	o << printout;
	return o;
}

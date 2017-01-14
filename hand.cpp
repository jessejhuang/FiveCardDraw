// Author : Danny Weiner
// Purpose: define that which is declared in hand.h, to be used in lab3

//#include "stdafx.h"
#include "poker.h"
#include <algorithm>
#include <iterator>
#include <sstream>

using namespace std;

Hand::Hand() : handv(NULL) {}
Hand::Hand(const Hand & otherH) : handv(otherH.handv) {}
Hand::~Hand() {
	//compiler-supplied is destructor is sufficient, because I am not dynamically allocating anything additional. The absence of the "new" keyword and/or related pointer usage means there is no excess material on a heap that needs to be separately addressed.
}
int Hand::size() const {
	return handv.size();
}

string Hand::toString() const {
	string printout = "";
	string VCDS = "";
	ostringstream oss(printout);
	for (size_t i = 0; i < handv.size(); ++i) {
		oss << "P" << i << ": " << handv[i] << " ";
	}
	istringstream iss(oss.str());
	while (getline(iss, VCDS)) {
		iss >> VCDS;
		printout += VCDS;
	}
	return string(printout);
}

void Hand::remove_card(size_t &i) {
	if (i >= 0 && i < handv.size()) {
		handv.erase(handv.begin() + i);
	}
	else {
		throw invalid_position;
	}
}

bool Hand::operator<(const Hand & otherH) const {
	for (size_t i = 0; i < 5; ++i) {
		if (handv[i] != otherH.handv[i]) {
			return (handv[i] < otherH.handv[i]);
		}
	}
	return false;
}

bool Hand::operator== (const Hand & otherH) const {
	return (handv == otherH.handv);
}

void Hand::operator=(const Hand & otherH) {
	if (!(*this == otherH)) {
		handv.clear();
		handv = otherH.handv;
	}
}

Card Hand::operator[](size_t & i) const {
	if (i >= 0 && i < handv.size()) {
		return handv[i];
	}
	else {
		throw invalid_position;
	}
}

std::ostream & operator<<(std::ostream &o, const Hand &hand) {
	std::copy(hand.handv.begin(), hand.handv.end(), std::ostream_iterator<Card>(o, " "));
	o << std::endl;
	return o;
}

void operator<<(Hand &h, Deck &d) {
	h.handv.push_back(d.deckv.back()); //grab last card from deck and add it to the back of the hand
	d.deckv.pop_back(); //remove the last card from the deck
	std::sort(h.handv.begin(), h.handv.end()); //maintain order									   
}

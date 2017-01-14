// Author : Danny Weiner
// Purpose: define that which is declared in deck.h, to be used in lab2

//#include "stdafx.h"
#include "poker.h"
#include "deck.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>

using namespace std;

Card c;
Deck d;

std::string ICDS = "INVALID CARD DEFINITION STRING";

Deck::Deck() : deckv(NULL) {}

Deck::~Deck() {
	//compiler-supplied is destructor is sufficient, because I am not dynamically allocating anything additional. The absence of the "new" keyword and/or related pointer usage means there is no excess material on a heap that needs to be separately addressed.
}

Deck::Deck(const char * filename) {
	int loaded = Deck::load(filename);
	if (loaded != 0) {
		Deck::Deck();
	}

}

int Deck::load(const char * filename) {
	ifstream ifs;
	std::string VCDS; //"VCDS" is my shorthand for "valid card definition string"
	std::string line;
	std::string subline;
	size_t slashes;
	size_t cCount = 0;
	size_t dCount = 0;
	size_t hCount = 0;
	size_t sCount = 0;
	size_t suitCount = 0;
	ifs.open(filename);
	if (!ifs.is_open()) {
		cerr << filename << " could not be opened for reading." << endl;
		return could_not_read;
	}
	else {
		while (getline(ifs, line)) {
			slashes = line.find("//");
			subline = line.substr(0, (slashes - 1));

			istringstream iss(subline);
			while (iss >> VCDS) {
				if (VCDS.length() == 2) { //all valid card definitions are 2-3 characters
					Deck::loadHelper(VCDS, 1);
					switch (VCDS[0]) {
					case 'J':
						c.r = jack;
						deckv.push_back(c);
						//std::cout << "PUSHING BACK" << c << std::endl;
						break;
					case 'j':
						c.r = jack;
						deckv.push_back(c);
						//std::cout << "PUSHING BACK" << c << std::endl;
						break;
					case 'Q':
						c.r = queen;
						deckv.push_back(c);
						//std::cout << "PUSHING BACK" << c << std::endl;
						break;
					case 'q':
						c.r = queen;
						deckv.push_back(c);
						//std::cout << "PUSHING BACK" << c << std::endl;
						break;
					case 'K':
						c.r = king;
						deckv.push_back(c);
						//std::cout << "PUSHING BACK" << c << std::endl;
						break;
					case 'k':
						c.r = king;
						deckv.push_back(c);
						//std::cout << "PUSHING BACK" << c << std::endl;
						break;
					case 'A':
						c.r = ace;
						deckv.push_back(c);
						//std::cout << "PUSHING BACK" << c << std::endl;
						break;
					case 'a':
						c.r = ace;
						deckv.push_back(c);
						//std::cout << "PUSHING BACK" << c << std::endl;
						break;
					case '2':
						c.r = two;
						deckv.push_back(c);
						//std::cout << "PUSHING BACK" << c << std::endl;
						break;
					case '3':
						c.r = three;
						deckv.push_back(c);
						//std::cout << "PUSHING BACK" << c << std::endl;
						break;
					case '4':
						c.r = four;
						deckv.push_back(c);
						//std::cout << "PUSHING BACK" << c << std::endl;
						break;
					case '5':
						c.r = five;
						deckv.push_back(c);
						//std::cout << "PUSHING BACK" << c << std::endl;
						break;
					case '6':
						c.r = six;
						deckv.push_back(c);
						//std::cout << "PUSHING BACK" << c << std::endl;
						break;
					case '7':
						c.r = seven;
						deckv.push_back(c);
						//std::cout << "PUSHING BACK" << c << std::endl;
						break;
					case '8':
						c.r = eight;
						deckv.push_back(c);
						//std::cout << "PUSHING BACK" << c << std::endl;
						break;
					case '9':
						c.r = nine;
						deckv.push_back(c);
						//std::cout << "PUSHING BACK" << c << std::endl;
						break;
					default: //don't push_back here or it'll add a duplicate of the last valid card definition string to the hand vector
						cerr << ICDS << endl;
						break;
					}
				}
				else if (VCDS.length() == 3) { //the only valid card definition string that is three characters long is a 10X
					Deck::loadHelper(VCDS, 2);
					if (VCDS[0] == '1' && VCDS[1] == '0') { //doublecheck that this is a 10
						c.r = ten;
						deckv.push_back(c);
						//std::cout << "PUSHING BACK" << c << std::endl;
					}
					else {
						cerr << ICDS << endl;
					}

				}
				else { //if the word is not 2 or 3 characters, it cannot be a card definition string
					cerr << ICDS << endl;
				}
			}
		}
	}

	ifs.close();
	return success; //success
}

int Deck::loadHelper(std::string word, int index) {
	switch (word[index]) {
	case 'C':
		c.s = Clubs;
		break;
	case 'c':
		c.s = Clubs;
		break;
	case 'D':
		c.s = Diamonds;
		break;
	case 'd':
		c.s = Diamonds;
		break;
	case 'H':
		c.s = Hearts;
		break;
	case 'h':
		c.s = Hearts;
		break;
	case 'S':
		c.s = Spades;
		break;
	case 's':
		c.s = Spades;
		break;
	default:
		cout << ICDS << endl;
		break;
	}
	return 0; //success
}

int Deck::size() const {
	return deckv.size();
}

void Deck::shuffle() {
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(deckv.begin(), deckv.end(), g);
}

void Deck::add_card(Card & c) {
	deckv.push_back(c);
}

std::ostream & operator<<(std::ostream &o, const Deck &deck) {
	std::copy(deck.deckv.begin(), deck.deckv.end(), std::ostream_iterator<Card>(o, " "));
	o << std::endl;
	return o;

}

void operator<<(Deck &d, Hand &h) {
	d.deckv.push_back(h.handv.back());
	h.handv.pop_back();
}

void operator<<(Deck &d1, Deck &d2) {
	d1.deckv.push_back(d2.deckv.back());
	d2.deckv.pop_back();
}

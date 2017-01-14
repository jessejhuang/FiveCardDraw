// Author : Danny Weiner, Jesse Huang
// Purpose: define that which is declared in player.h, to be used in lab3

//#include "stdafx.h"
#include "poker.h"
#include "player.h"

using namespace std;

Player::Player(std::string filename) : name(filename), playerCards(), won(0), lost(0) {
	ifstream ifs;
	unsigned int slashes;
	std::string line;
	std::string subline;
	std::string word;
	ifs.open(filename+".txt");
	if (!ifs.is_open()) {
		std::cout << "(" << filename << ".txt could not be opened for reading, so a default player was created.)" << std::endl;
		//throw could_not_read; I think last part of step 6 wants us to do nothing
	}
	else {
		if (getline(ifs, line)) {
			slashes = line.find("//");
			subline = line.substr(0, (slashes - 1));

			istringstream iss(subline);
			std::string str_won;
			std::string str_lost;
			iss >> filename;
			iss >> str_won;
			iss >> str_lost;
			if (filename == "" || !isInt(str_won) || !isInt(str_lost)) {
				//Do nothing, isInt should prevent stoi from throwing illegal argument
			}
			else {
				//Converts strings from files to integers 
				won = stoi(str_won, nullptr, 10);
				lost = stoi(str_lost, nullptr, 10);
				name = filename;
			}
		}
	}
	ifs.close();
}


bool operator==(const Player & a, const Player & b)
{
	return (a.name == b.name);
}

std::ostream & operator<< (std::ostream &o, const Player &p) {
	o << p.name << " " << p.won << " " << p.lost << std::endl;
	return o;
}

//From http://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int
bool isInt(std::string s) {
	return s.find_first_not_of("0123456789") == string::npos;
}

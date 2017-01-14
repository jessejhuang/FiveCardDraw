// Author : Jesse Huang, Kate Hao, Danny Weiner
// Purpose: define that which is declared in fiveCardDraw.h, to be used in lab3

//#include "stdafx.h"
#include "fiveCardDraw.h"
#include "poker.h"
#include "Exceptions.h"
#include <algorithm>

FiveCardDraw::FiveCardDraw() :
	dealer(0), discard_deck()
{
	for (unsigned int i = 0; i < 4; ++i) {
		for (unsigned int j = 2; j < 15; ++j) {
			Card c;
			c.r = RANKS(j);
			c.s = SUITS(i);
			main_deck.add_card(c);
		}
	}
}

FiveCardDraw::~FiveCardDraw()
{
}

int FiveCardDraw::before_turn(Player & p)
{
	std::string ans;
	std::cout << "Player: " << p.name << std::endl << "Hand: " << p.playerCards << std::endl;
	bool validAnswer = false;
	do {
		std::cout << "Indicate by position number which cards you'd like to discard and press enter when done. (E.g to discard your first and third cards type \"1 3\" or \"3 1\")" << std::endl;
		std::cout << "To discard none, type \"0\"." << std::endl;
		std::getline(std::cin, ans);
		std::cout << std::endl;
		std::istringstream iss(ans);

		//extract indices of discarded cards
		std::vector<Card> discards;
		int elementCount = 0;
		size_t i;
		while (iss >> i) {
			++elementCount;
			if (i == 0 && (!iss.eof() || discards.size() != 0)) {		//test if 0 (i.e. discard none) isn't the only input (i.e. invalid)
				std::cout << "0 should indicate discarding none." << std::endl;
				break;
			}
			else if (i == 0) {										//if 0 is the only input (i.e. discard none); end the loop and do nothing
				validAnswer = true;
				break;
			}
			else {
				if (i > 0 && i <= 5) {
					size_t k = i - 1;
					discards.push_back(p.playerCards[k]);
					validAnswer = true;
				}
				else {												//user entered invalid card position
					std::cout << "Invalid card position to discard." << std::endl;
					validAnswer = false;
					break;
				}
			}
			if (elementCount > 5) {
				std::cout << "Too many elements, invalid response." << std::endl;
				validAnswer = false;
				break;
			}
		}
		if (validAnswer) {
			//must add & remove separately so that playerCard's indices remain consistent
			for (size_t i = 0; i < discards.size(); ++i) {
				discard_deck.add_card(discards[i]);

			}
			for (size_t i = 0; i < discards.size(); ++i) {
				for (size_t j = 0; j < p.playerCards.size(); ++j) {
					if (p.playerCards[j] == discards[i]) {
						p.playerCards.remove_card(j);

					}
				}
			}
		}
	} while (!validAnswer);
	return success;
}

int FiveCardDraw::turn(Player & p)
{
	int cardsToDeal = 5 - p.playerCards.size();
	if (cardsToDeal > main_deck.size()) {
		int cardsFromDiscard = cardsToDeal - main_deck.size();
		for (int i = 0; i < main_deck.size(); ++i) {
			p.playerCards << main_deck;
		}
		for (int j = 0; j < cardsFromDiscard; ++j) {
			if (discard_deck.size() != 0) {
				p.playerCards << discard_deck;
			}
			else {
				return no_cards_to_deal;
			}
		}
	}
	else {
		for (int i = 0; i < cardsToDeal; ++i) {
			p.playerCards << main_deck;
		}
	}
	return success;
}

int FiveCardDraw::after_turn(Player & p)
{
	std::cout << "Player: " << p.name << std::endl << "New hand: " << p.playerCards << std::endl;
	return success;
}

int FiveCardDraw::before_round()
{
	main_deck.shuffle();
	size_t start = dealer + 1;
	if (start == players.size()) start = 0;
	size_t currPlayer = start;
	for (size_t i = 0; i < (players.size()-1)* 5; ++i) {		//iterate enough times to give each (non-dealer) player 5 cards
		if (currPlayer == dealer) {
			currPlayer++;
			if (currPlayer == players.size()) currPlayer = 0;
		}
		Player & curr = *players[currPlayer];
		curr.playerCards << main_deck;
		currPlayer++;
		if (currPlayer == players.size()) currPlayer = 0;
	}

	currPlayer = start;
	for (size_t i = 0; i < players.size() - 1; ++i) {			//call before_turn for each non-dealer player
		Player & curr = *players[currPlayer];
		before_turn(curr);
		currPlayer++;
		if (currPlayer == players.size()) currPlayer = 0;
	}
	return success;
}

int FiveCardDraw::round()
{
	size_t currPlayer = dealer + 1;
	if (currPlayer == players.size()) currPlayer = 0;
	for (size_t i = 0; i < players.size() - 1; ++i) {
		Player & curr = *players[currPlayer];
		int result = turn(curr);
		if (result == success) {
			after_turn(curr);
		}
		else return result;
		currPlayer++;
		if (currPlayer == players.size()) currPlayer = 0;
	}
	return success;
}

int FiveCardDraw::after_round()
{ 
	std::vector<std::shared_ptr<Player>> temp;
	//copy all the players from players to temp EXCEPT the dealer
	for (size_t i = 0; i < players.size(); ++i) {
		if (i == dealer) {
			continue;
		}
		else temp.push_back(players[i]);
	}
	bool(*func)(std::shared_ptr<Player> &, std::shared_ptr<Player> &) = &poker_rank;
	std::
		
		(temp.begin(), temp.end(), func);
	
	//increment wins & losses:
	//first, count number of winners
	std::vector<Player> winners;
	Player firstWinner = *temp[0];
	winners.push_back(firstWinner);
	for (size_t i = 1; i < temp.size(); ++i) {
		if (temp[i]->playerCards.h == firstWinner.playerCards.h) winners.push_back(*temp[i]);
		else break;
	}
	//then, iterate through original vector of players to find winners
	for (size_t i = 0; i < players.size(); ++i) {
		if (find(winners.begin(), winners.end(), *players[i]) != winners.end()) {	//is a winner
			players[i]->won++;
		}
		else if(i != dealer) players[i]->lost++;
	}

	//print out each player's name, # of wins and losses, and current hand
	for (size_t i = 0; i < temp.size(); ++i) {
		std::cout << "Player: " << temp[i]->name << ", Wins: " << temp[i]->won << ", Losses: " << temp[i]->lost
			<< ", Current hand: " << temp[i]->playerCards << std::endl;
	}

	//move all cards from player hands and discard deck back to main deck
	//first, move cards from discard deck to main deck
	while (discard_deck.size() > 0) {
		main_deck << discard_deck;
	}
	//second, move cards from players' hands to main deck
	for (size_t i = 0; i < players.size(); ++i) {
		while (players[i]->playerCards.size() > 0) {
			main_deck << players[i]->playerCards;
		}
	}

	//until user says no, repeatedly ask if any players want to leave the game
	std::string leave;
	do {
		std::cout << "Do any players want to leave the game? If so, enter the player name." << std::endl
			<< "If not, type 'no'." << std::endl;;
		getline(std::cin, leave);

		if (leave != "no") {
			for (size_t i = 0; i < players.size(); ++i) {
				if (players[i]->name == leave) {
					std::ofstream ofs;
					ofs.open(leave + ".txt");
					ofs << *players[i];
					ofs.close();
					players.erase(players.begin() + i);
					break;
				}
			}
		}
	} while (leave != "no");

	//until user says no, repeatedly ask if any players want to join the game
	std::string join;
	do {
		std::cout << "Do any players want to join the game? If so, enter the player name." << std::endl
			<< "If not, type 'no'." << std::endl;
		getline(std::cin, join);
		
		if (join != "no") {
			try {
				add_player(join);
			}
			catch (already_playing e) {
				std::cout << e.what() << std::endl;
				continue;
			}
		}
	} while (join != "no");

	//increment the dealer
	dealer++;
	if (dealer >= players.size()) dealer = 0;

	return success;
}

bool poker_rank(std::shared_ptr<Player> & p1, std::shared_ptr<Player> & p2) {
	if (p1 == nullptr && p2 != nullptr) {
		return false;
	}
	else if (p1 != nullptr && p2 == nullptr) {
		return true;
	}
	else {
		Player player1 = *p1;
		Hand h1 = player1.playerCards;
		Player player2 = *p2;
		Hand h2 = player2.playerCards;
		return poker_rank(h1, h2);
	}
}

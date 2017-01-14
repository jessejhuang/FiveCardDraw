#pragma once
#ifndef  Game_h
#define Game_h

#include <memory>
#include <vector>
#include "player.h"
#include "deck.h"

//class FiveCardDraw;

class Game {

public:
	virtual ~Game();
	static std::shared_ptr<Game> instance();
	static void start_game(const std::string& s);
	static void stop_game();
	bool add_player(const std::string& s); //Returns true if successful add
	std::shared_ptr<Player> find_player(const std::string& s);
	int numPlayers() const;

	virtual int before_turn(Player& p) = 0;
	virtual int turn(Player& p) = 0;
	virtual int after_turn(Player& p) = 0;
	virtual int before_round() = 0;
	virtual int round() = 0;
	virtual int after_round() = 0;
protected:
	Deck main_deck = Deck::Deck();
	std::vector<std::shared_ptr<Player> > players;
	static std::shared_ptr<Game> game_ptr; //initially null	
};

#endif // ! Game_h
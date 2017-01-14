//#include "stdafx.h"
#include "Exceptions.h"
#include "Game.h"
#include "fiveCardDraw.h"
#include <algorithm>

std::shared_ptr<Game> Game::game_ptr = nullptr;
Game::~Game()
{
}

void Game::start_game(const std::string & s)
{
	if (Game::game_ptr != nullptr) {
		throw game_already_started();
	}
	else if (s.find("FiveCardDraw") == std::string::npos) {
		throw unknown_game();
	}
	else {
		
		std::shared_ptr<FiveCardDraw> fcd_ptr;
		game_ptr = std::make_shared<FiveCardDraw>(); 
	}
}
void Game::stop_game() {
	if (game_ptr == nullptr) {
		throw no_game_in_progress();
	}
	else {
		game_ptr.reset();
	}
}

bool Game::add_player(const std::string & s)
{
	if (Game::find_player(s) == nullptr) {
		std::shared_ptr<Player> p = std::make_shared<Player>(s);//Dynamically allocate memory for new player
		Game::players.push_back(p);
		return true;
	}
	else {
		throw already_playing();
	}
	return false;
}
std::shared_ptr<Player> Game::find_player(const std::string& s) {
	for (std::shared_ptr<Player> p : Game::players) {
		if (p->name == s) {
			return p;
		}
	}
	return nullptr;
}

std::shared_ptr<Game> Game::instance()
{
	if (game_ptr == nullptr) {
		throw instance_not_available();
		return nullptr;
	}
	else {
		std::shared_ptr<Game> gp_copy(game_ptr);
		return gp_copy;
	}
}

int Game::numPlayers() const {
	return players.size();
}

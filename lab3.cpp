// lab3.cpp : Defines the entry point for the console application.
//
//Authors : Danny Weiner, Jesse Huang, Kate Hao
//Purpose : (paraphrased from class webpage)
//extend your C++ programs from previous the labs to:
//(1) maintain and display the status of a multiplayer game of 5 card draw poker;
//(2) parse commandline arguments to identify the initial players in the game;
//(3) within each round of play allow players to discard cards from and add cards to their hands, and print out a ranking of the resulting hands; and
//(4) between rounds allow current players to leave the game and new players to enter the game, saving information for players who leave in files so
//		that if they rejoin the game later the files can be used to restore their statistics from previous rounds of play.

//#include "stdafx.h"
#include "poker.h"
#include "deck.h"
#include "Game.h"
#include "fiveCardDraw.h"
#include "Exceptions.h"
#include <algorithm>
#include <string>
#include <fstream>//t
#include <sstream>

using namespace std;

int main(int argc, char * argv[]) {
	try {
		char * program_name = argv[0];
		if (argc >= 4) {
			Game::start_game(argv[1]);
			shared_ptr<Game> pointer = Game::instance();
			for (int i = 2; i < argc; ++i) {
				pointer->add_player(argv[i]);
			}
			while ((pointer->numPlayers()) >= 2) {
				cout << endl << "---------------------------" << endl;
				pointer->before_round();
				pointer->round();
				pointer->after_round();
			}
			pointer->stop_game();
			return success;
		}
		else {
			return usage(program_name, "program should be run with the name of the game followed by two or more player names", not_enough_args);
		}
	}
	catch (unknown_game e) {
		cout << e.what() << endl;
		return caught_exception;
	}
	catch (no_game_in_progress e) {
		cout << e.what() << endl;
		return caught_exception;
	}
	catch (instance_not_available e) {
		cout << e.what() << endl;
		return caught_exception;
	}
	catch (game_already_started e) {
		cout << e.what() << endl;
		return caught_exception;
	}
	catch (already_playing e) {
		cout << e.what() << endl;
		return caught_exception;
	}
	catch (...) {
		Game::stop_game();
		cout << "An unknown error occurred" << endl;
		return unknown_error;
	}
}

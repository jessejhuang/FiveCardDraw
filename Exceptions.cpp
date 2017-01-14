//#include "stdafx.h"
#include "Exceptions.h"

const char * instance_not_available::what() const throw()
{
	return "This instance is not available";
}
const char * game_already_started::what() const throw()
{
	return "The game has already been started";
}

const char * unknown_game::what() const throw()
{
	return "The game specified is not recognized";
}

const char * no_game_in_progress::what() const throw()
{
	return "A game is not in progress";
}

const char * already_playing::what() const throw()
{
	return "This player is already in the game.";
}


***************Grading***************
Grader: Christopher McKiernan

Grade: 83/105

Deductions:

-3 You have a warning in your build that you don't mention in your errors and warning section (it should be fixed).

-5 Broke your program  (Error message included at end)

-3 Dealer should be allowed to play as well.

-3 Hardcoding throughout program.

-3 Lacking thoughtful comments throughout code

"Player: Todd
Hand: 3C 10C 3D 3H JS

Indicate by position number which cards you'd like to discard and press enter wh
en done. (E.g to discard your first and third cards type "1 3" or "3 1")
To discard none, type "0".
2 5

Player: Vanessa
Hand: 5D 2H 8H 9H 3S

Indicate by position number which cards you'd like to discard and press enter wh
en done. (E.g to discard your first and third cards type "1 3" or "3 1")
To discard none, type "0".
1,2,3,4,5

Player: Antonio
Hand: AC 10D AD AH 9S

Indicate by position number which cards you'd like to discard and press enter wh
en done. (E.g to discard your first and third cards type "1 3" or "3 1")
To discard none, type "0".
1xx2

Player: Doyle
Hand: 4C JD KD 10S KS

Indicate by position number which cards you'd like to discard and press enter wh
en done. (E.g to discard your first and third cards type "1 3" or "3 1")
To discard none, type "0".
aaa

Indicate by position number which cards you'd like to discard and press enter wh
en done. (E.g to discard your first and third cards type "1 3" or "3 1")
To discard none, type "0".
  xq1

Indicate by position number which cards you'd like to discard and press enter wh
en done. (E.g to discard your first and third cards type "1 3" or "3 1")
To discard none, type "0".
1x2x3

Player: Todd
New hand: 3C JC 3D 3H 10H

Player: Vanessa
New hand: 6D 2H 8H 9H 3S

Player: Antonio
New hand: 10D AD AH 7S 9S

Player: Doyle
New hand: 8D JD KD 10S KS

\n "lab3_grading.exe FiveCardDraw Doyle Jennifer Todd Vanessa Antonio returned "
 3
Press any key to continue . . .
"
*************************************





========================================================================
    lab3 Project Overview
	Jesse Huang		jessehuang@wustl.edu
	Danny Weiner		dnweiner@wustl.edu
	Kate Hao		kate.hao@gmail.com
========================================================================


Program Description
===================
This program will simulate a game of Five-Card Draw between at least two players, where the role of the dealer cycles through the players (the dealer begins as position 0, i.e. the first player inputted). Each round begins with giving the players the option to discard as few or as many cards they want from their randomly drawn hand. After discarding, their hand is refilled to 5 cards from the shuffled main deck; then, whoever as the winning hand wins the round. At the end of the round, players have the option to leave (in which case their wins and losses will be outputted to a text file). Additionally, players can join -- whenever players are added, either at the very beginning of the game or between rounds, the program will check for a text file whose title matches their name from which to read in wins and losses. If such a text file is not found, then a default player is created with 0 wins and losses. The game will continue to execute until there are fewer than 2 players, at which point it automatically terminates.


In addition to the functions in the lab instructions, we wrote several additional functions. In Deck, we wrote two new << operators in order to make it easier to transfer cards from the discard deck and player hands to the main deck. In Game, we added a numPlayers() method that returns the number of players that are currently in the game. 
In player.cpp, the isInt method checks if a string can be converted into an integer.


Errors and Warnings
===================
One major error we struggled with was how to deal with the shared_ptr, game_ptr, in the Game.cpp class. In start_game, we initially struggled to figure out how to instantiate it with make_shared, since just forward declaring wouldn't allow that. The solution just turned out to be including FiveCardDraw.h in the Game.cpp class.
Beyond that, before_turn was the most difficult to debug.


Test Cases and Command Line Arguments
=====================================
Not enough arguments:
Command: Lab3.exe FiveCardDraw Kate
Output: “Usage: Lab3.exe experienced error: program should be run with the name of the game followed by two or more player names”
	This is the correct behavior!
When a player without a text file is entered as part of a command,
upon exiting, a text file with their name is created in the directory of the exe file.
 
The game terminates when there are less than two players 
(i.e. if there are currently 2 players and one of them leaves at the end of the round)
If there are only two players, the player who is not dealing will automatically win 
because the dealer does not have a hand to compare to. 

If a player is already in the game, the already_playing exception is thrown. 

If a command such as “Lab3.exe FaveCadDra Danny “ is entered, the unknown game exception is thrown.

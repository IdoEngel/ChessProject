#pragma once

#include "Board.h"
#include "Player.h"

#define PLAYERS_IN_GAME 2
#define ROW_COLUMN 8
#define EMPTY '#'

class Game /* : std::exception*/ {
public:
	/*Constractor - creates an instance of the class with the board peices in the defualt position
	input: bool - forException (if instace created for excption no need to create all the peices, just the function 'what'.
		Default value if 'false' - creating all the instance)
	output: none*/
	Game(const bool forException = false);

	//Distractor
	~Game();

	//Getter - Hard Copy
	Board getBoard() const;

	/*Return the current player color - white always starts*/
	char getCurrPlayerColor() const;

	/*Return how won - bool type
		RAISE error if no of them won (typed Game)
	input: none
	output: how won? (0 - white, 1 - black)*/
	//bool HowIsWinning() const;

	/*Plat one move in the game - each player in his turn (White starts)
	input: string - coordinates (the coordintas to move to)
	output: none*/
	void play(const std::string& coordinates);

	/*prints the board by lines to the console
	OPERATOR << FUNCTION*/
	friend std::ostream& operator<<(std::ostream& os, const Game& g);

	/*RAISE if the no one won the game in the givan moment
	input: none
	output: msg error - "No one won yet"*/
	//const char* what() const noexcept override;
private:
	unsigned int _numOfMoves;
	bool _ifForException;
	Board* _board;
	Player _playes[PLAYERS_IN_GAME];
};
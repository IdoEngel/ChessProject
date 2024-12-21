#pragma once

#include <vector>
#include "Board.h"
#include "Player.h"
#include "Pipe.h"

#define PLAYERS_IN_GAME 2
#define ROW_COLUMN 8
#define EMPTY '#'

#define WHITE_STR "W"
#define BLACK_STR "B"

#define CODE_2 "2"

class Game  : std::exception {
public:
	/*Constractor - creates an instance of the class with the board peices in the defualt position
	input: bool - forException (if instace created for excption no need to create all the peices, just the function 'what'.
		Default value if 'false' - creating all the instance)
	output: none*/
	Game(const bool forException = false);

	//Distractor
	~Game();

	//Getter - Hard Copy
	Board getBoard() const noexcept;

	/*Return the current player color - white always starts*/
	char getCurrPlayerColor() const noexcept;


	/*Plat one move in the game - each player in his turn (White starts)
	input: string - coordinates (the coordintas to move to)
	output: none*/
	std::string play(const std::string& coordinates);

	/*prints the board by lines to the console
	OPERATOR << FUNCTION*/
	friend std::ostream& operator<<(std::ostream& os, const Game& g);

	/*Call the all the funcs that check the code errors and return the code
	input: none
	output: the code for graphics*/
	std::string codeForGraphics(const std::string& coordinats) const noexcept;

	/*RAISE if the someone won the game
	input: none
	output: msg error - "B" - if black won; "W" - if white won*/
	const char* what() const noexcept override;
private:
	unsigned int _numOfMoves;
	bool _ifForException;
	Board* _board;
	Player _playes[PLAYERS_IN_GAME];

	/*Check if the current turn is the same color as the selected piece
	* input: Piece - piece (the piece to check)
	* output: is the piece match?
	*/
	bool isCurrTurnMatchColorSelected(const Piece* piece) const noexcept;

	/*is the king of the current player is thretend?
	input: string - kingCoordinate (the king of the curr to check)
	output: is the king thretend?*/
	bool isSelfCheck(const std::string kingCoordinate) const noexcept;

	bool isWayClear(const std::vector<std::string>);

	/*Get the current king to and return it
	input: none
	output: the King piece*/
	Piece* getKing() const noexcept;

	/*get the coordinate of the piece
	input: Piece - piece (the piece to get the coords)
	output: string of the coord*/
	std::string getCoordinates(const Piece* piece) const noexcept;
};
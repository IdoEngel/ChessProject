//game.h
#pragma once

#include <vector>
#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Pipe.h"

#define PLAYERS_IN_GAME 2
#define ROW_COLUMN 8
#define EMPTY '#'

#define WHITE_STR "W"
#define BLACK_STR "B"

#define CODE_0 "0"
#define CODE_4 "4"
#define CODE_6 "6"

class Game : std::exception {
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
	std::string play(const std::string& coordinates) noexcept;

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
	bool isSelfChecked(const std::string kingCoordinate) const noexcept;

	/*Checks all the coordinates in the vector are nullptr (no pieces on the way)
	input: vector<string> - moves (the moves to check if nullptr)
	output: is all the moves are null (the way is clear)*/
	bool isWayClear(const std::vector<std::string> moves) const noexcept;

	/*Get the current king to and return it
	input: none
	output: the King piece*/
	Piece* getKing() const noexcept;

	/*get the coordinate of the piece
	input: Piece - piece (the piece to get the coords)
	output: string of the coord*/
	std::string getCoordinatesOfPiece(const Piece* piece) const noexcept;

	/*Get the len of the passible moves (to check if the path is valid)
	input: string - coord (the coord of the piece to create the passible
	output: the len of the vector of passible moves*/
	int lenOfPassibleMoves(const std::string& coord) const noexcept;
};
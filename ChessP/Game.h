//game.h
#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Pipe.h"

#define PLAYERS_IN_GAME 2
#define NO_ENOUGH_PIECES_TO_PROTECT_KING 2
#define TAKE_TWO_CHARS 2
#define NOT_THE_LAST_TWO_CHARS 2
#define ROW_COLUMN 8
#define EMPTY '#'

#define WHITE_STR "W"
#define BLACK_STR "B"

#define CODE_0 "0"
#define CODE_1 "1"
#define CODE_4 "4"
#define CODE_6 "6"
#define CODE_8 "8"

#define MY_KING true
#define OPPO_KING false //opponant king
#define KING_MOVING true
#define KING_NOT_MOVING false
#define ONLY_SELF_ON_THE_WAY true
#define NOT_ONLY_SELF_ON_THE_WAY false

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

	/*Return the opponent player color - white always starts*/
	char getOpponentPlayerColor() const noexcept;


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
	input: string - kingCoordinate (the king of the curr to check), pieceCoord (the piece want to move in the turn)
		bool - isKingPlaying (true - the king is moving, false - other piece)
	output: is the king thretend?*/
	bool isSelfChecked(const std::string& kingCoordinate, const std::string& pieceCoord, const bool isKingPlaying = false) const noexcept;

	/*is the king of opponent thretened?
	input: string - kingCoordinate (the king to check)
	output: is the king of opponent thretened? (bool)*/
	bool isCheckedOnOpponent(const std::string& kingCoordinate, const std::string& pieceCoords) const noexcept;

	/*Checks all the coordinates in the vector are nullptr (no pieces on the way)
	input: vector<string> - moves (the moves to check if nullptr)
	output: is all the moves are null (the way is clear)*/
	bool isWayClear(const std::vector<std::string> moves) const noexcept;

	/*Get the king to and return it
	input: bool - isMyKing (get the current king?) - if false - return opponant king
	output: the King piece*/
	Piece* getKing(const bool isMyKing) const noexcept;

	/*get the coordinate of the piece
	input: Piece - piece (the piece to get the coords)
	output: string of the coord*/
	std::string getCoordinatesOfPiece(const Piece* piece) const noexcept;

	/*Get the len of the passible moves (to check if the path is valid)
	input: string - coord (the coord of the piece to create the passible
	output: the len of the vector of passible moves*/
	int lenOfPassibleMoves(const std::string& coord) const noexcept;

	/*Check and return how many pieces on the way
	input: vector<string> - way (the way to check and count)
		bool - onlySelfPieces (true - count only pieces of curr player, false - count all)
	output: the number of pieces on the way*/
	unsigned int howManyOnTheWay(const std::vector<std::string> way, const bool onlySelfPieces) const noexcept;
};

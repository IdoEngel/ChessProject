#pragma once

#include <string>
#include <exception>

#include "Piece.h"
#include "Bishop.h"
#include "King.h"
#include "Knigth.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

enum class columnDictBlack
{
	ROOK, KNIGTH, BISHOP, QUEEN, KING, BISHOP2, KNIGTH2, ROOK2
};

enum class columnDictWhite
{
	ROOK, KNIGTH, BISHOP, KING, QUEEN, BISHOP2, KNIGTH2, ROOK2
};

#define NUM_OF_PIECES 64
#define ROW_COLUMN 8
#define FIRST_ROW_OF_SOLDIERS 2
#define SECOND_ROW_OF_SOLDIERS 7
#define FIRST_ROW 1
#define LAST_ROW 8
#define TO_CHAR 97

#define W_PAWN_CHAR 'P'
#define B_PAWN_CHAR 'p'

#define W_ROOK_CHAR 'R'
#define B_ROOK_CHAR 'r'

#define W_KNIGHT_CHAR 'K'
#define B_KNIGHT_CHAR 'k'

#define W_BISHOP_CHAR 'B'
#define B_BISHOP_CHAR 'b'

#define W_QUEEN_CHAR 'Q'
#define B_QUEEN_CHAR 'q'

#define W_KING_CHAR 'K'
#define B_KING_CHAR 'k'

class Board : std::exception {
public:

	/*Constractor - creates an instance of the class with the board peices in the defualt position
	input: bool - forException (if instace created for excption no need to create all the peices, just the function 'what'.
		Default value if 'false' - creating the peaces)
	output: none*/
	Board(const bool forException = false);

	/*Copy constractor for return types in functions*/
	Board(const Board& other);

	//Distractor
	~Board();

	/*Movrs the peice to the coordinate loction and return true, if its valid - if not - do noting and return false
	input: string - coordinate (coordinate with src and dst)
	output: is the move occured?*/
	bool movePeice(const std::string& coordinate) noexcept;

	/*Check if the src position the and dst position of the 'coordinate' is valid 
		if not valid retrun the error - if valid RAISE an excpion (typed Board)
	input: string - coordinate (coordinate with src and dst)
	output: the error code if occured*/
	std::string isPositionValid(const std::string& coordinate);

	/*RAISE if the 'isPositionValid' not found an error
	input: none
	output: msg error - "No error codes found"*/
	const char* what() const noexcept override;

protected:

	/*Create default board (all pieces in the loction of starting game)
	No input or output*/
	void createDefault();

private:
	Piece*** _pieces;
	const bool _isForException;

	/*Get the coordinate base om row and column
	input: int - row (the row), column (the column)
	output: coordinate of the row and column (string)*/
	std::string getCoordinate(const int row, const int column);

};

//board.h
#pragma once

#include <string>
#include <exception>
#include <memory>

#include "Exceptions.h"
#include "Piece.h"
#include "Bishop.h"
#include "King.h"
#include "Pawn.h"
#include "Knight.h"
#include "Queen.h"
#include "Rook.h"

typedef std::unique_ptr<std::vector<int>> intArr;

enum class PieceType
{
	ROOK, KNIGTH, BISHOP, QUEEN, KING, BISHOP2, KNIGTH2, ROOK2
};

#define NUM_OF_PIECES 64
#define ROW_COLUMN 8
#define FIRST_ROW_OF_SOLDIERS 2
#define SECOND_ROW_OF_SOLDIERS 7
#define FIRST_ROW 1
#define LAST_ROW 8
#define TO_CHAR 97
#define NUM_STR_TO_INT (int)'0'

#define SRC_START_INDEX 0
#define DST_START_INDEX 2
#define LEN_OF_TWO_COORDS 4

#define IS_WHITE_PIECE(piece) (piece >= 'A' && piece <= 'Z')
#define IS_BLACK_PIECE(piece) (piece >= 'a' && piece <= 'z')

#define W_PAWN_CHAR 'P'
#define B_PAWN_CHAR 'p'

#define W_ROOK_CHAR 'R'
#define B_ROOK_CHAR 'r'

#define W_KNIGHT_CHAR 'N'
#define B_KNIGHT_CHAR 'n'

#define W_BISHOP_CHAR 'B'
#define B_BISHOP_CHAR 'b'

#define W_QUEEN_CHAR 'Q'
#define B_QUEEN_CHAR 'q'

#define W_KING_CHAR 'K'
#define B_KING_CHAR 'k'

#define BLACK_CHAR 'b'
#define WHITE_CHAR 'W'

#define CODE_5 "5"
#define CODE_7 "7"
#define CODE_2 "2"
#define CODE_3 "3"

class Board {
public:

	/*Constractor - creates an instance of the class with the board peices in the defualt position
	input: bool - forException (if instace created for excption no need to create all the peices, just the function 'what'.
		Default value if 'false' - creating the peaces)
	output: none*/
	Board();

	/*Copy constractor for return types in functions*/
	//Board(const Board& other);

	//Distractor
	~Board();

	/*Movrs the peice to the coordinate loction and return true, if its valid - if not - do noting and return false
	input: string - coordinate (coordinate with src and dst)
	output: is the move ended the game? (code 8 happend?)*/
	bool movePeice(const std::string& coordinate) noexcept;

	/*Check if the src position the and dst position of the 'coordinate' is valid
		if not valid retrun the error - if valid RAISE an excpion (typed Board)
	input: string - coordinate (coordinate with src and dst)
	output: the error code if occured*/
	std::string isPositionValid(const std::string& coordinate);

	/*Get the peice in the loction mention
	*/
	Piece* getPiece(const int row, const int column) const;

	static intArr strToCoords(const std::string& coords);

	static std::string coordsToStr(const int row, const int column);

	static std::string coordsToStr(const int srcRow, const int srcColumn, const int dstRow, const int dstColumn);

protected:

	/*Create default board (all pieces in the loction of starting game)
	No input or output*/
	void createDefault();

private:
	Piece*** _pieces;
};


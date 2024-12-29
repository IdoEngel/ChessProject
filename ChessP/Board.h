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

typedef std::shared_ptr<std::vector<int>> intArr;

enum class PieceType
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
#define NUM_STR_TO_INT (int)'0'

#define SRC_START_INDEX 0
#define DST_START_INDEX 2
#define LEN_OF_TWO_COORDS 4

constexpr bool IS_WHITE_PIECE(char piece) {
	return piece >= 'A' && piece <= 'Z';
}

constexpr bool IS_BLACK_PIECE(char piece) {
	return piece >= 'a' && piece <= 'z';
}

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

	//Distractor
	~Board();

	/*Movrs the peice to the coordinate loction and return true, if its valid - if not - do noting and return false
	input: string - coordinate (coordinate with src and dst)
	output: is the move ended the game? (code 8 happend?)*/
	bool movePeice(const std::string& coordinate) noexcept;

	/*operator to get elememnt form the _pieces.
	can return a nullptr*/
	Piece* operator() (const size_t row, const size_t column) noexcept;

	/*Check if the src position the and dst position of the 'coordinate' is valid
		if not valid retrun the error - if valid RAISE an excpion (typed Board)
	input: string - coordinate (coordinate with src and dst)
	output: the error code if occured*/
	std::string isPositionValid(const std::string& coordinate);

	/*get coords in str and return int arr of them
	input: string - coords (the coords to convert)
	output the intArr */
	static intArr strToCoords(const std::string& coords);

	/*get the string value of the coords
	input: int {row, column}
	output: string of the coord*/
	static std::string coordsToStr(const int row, const int column);

	/*get the string value of the coords
	input: int {row, column, row, column}
	output: string of the coord*/
	static std::string coordsToStr(const int srcRow, const int srcColumn, const int dstRow, const int dstColumn);

	/*is the coords entered valid?
	input: int {row, column, row = 0, column = 0}
	output: is the coords valid?*/
	static bool isCoordsValid(const int srcRow, const int srcColumn, const int dstRow = 0, const int dstColumn = 0) noexcept;

	void didRookOrKingMoved(const int srcRow, const int srcCol);
	bool _bKingMoved;
	bool _wKingMoved;
	bool _bRookLeftMoved;
	bool _bRookRigthMoved;
	bool _wRookLeftMoved;
	bool _wRookRigthMoved;
protected:

	/*Create default board (all pieces in the loction of starting game)
	No input or output*/
	void createDefault();
private:
	Piece*** _pieces;
};


#include "Board.h"

//Constractors/Distractors
Board::Board(const bool forException) : _isForException(forException){

	if (!forException) { // if not for exception

		this->_pieces = new Piece**[ROW_COLUMN];

		int row = 0; // crreate a 2d arr
		for (row = 0; row < ROW_COLUMN; row++) {
			this->_pieces[row] = new Piece*[ROW_COLUMN];
		}
		createDefault();
	}
	else {
		this->_pieces = nullptr;
	}
}

Board::Board(const Board& other) : _isForException(other._isForException) {
	if (!this->_isForException) {

		// create the 2d arr
		this->_pieces = new Piece**[ROW_COLUMN];
		int row = 0; // crreate a 2d arr
		for (row = 0; row < ROW_COLUMN; row++) {
			this->_pieces[row] = new Piece*[ROW_COLUMN];
		}

		// copy the pieces
		int column = 0; // like 2d arr
		for (row = 0; row < ROW_COLUMN; row++) {
			for (column = 0; column < ROW_COLUMN; column++) {
				this->_pieces[row][column] = other._pieces[row][column];
			}
		}
	}
	else {
		this->_pieces = nullptr;
	}
}

Board::~Board() {
	int row = 0;
	int column = 0;

	if (!this->_isForException) { // if for excption - nothing to free
		// free individual pieces
		for (row = 0; row < ROW_COLUMN; row++) {
			for (column = 0; column < ROW_COLUMN; column++) {
				delete this->_pieces[row][column]; // can 'free' nullptr
			}
		}

		// free the 2d part of the _pieces var
		for (row = 0; row < ROW_COLUMN; row++) {
			delete[] this->_pieces[row];
		}

		delete[] this->_pieces; // free the placeholder of the 2d part
	}
}


//Helping funcs

void Board::createDefault() {
	PieceType dict;

	int row = 0;
	int column = 0; // like 2d arr
	for (row = 0; row < ROW_COLUMN; row++) {
		for (column = 0; column < ROW_COLUMN; column++) {

			// if the place of pown
			if (FIRST_ROW_OF_SOLDIERS == row + 1) { // black
				this->_pieces[row][column] = new Pown(getCoordinate(row, column), B_PAWN_CHAR);
			}
			else if (SECOND_ROW_OF_SOLDIERS == row + 1) { //white
				this->_pieces[row][column] = new Pown(getCoordinate(row, column), B_PAWN_CHAR);
			}
			else if (FIRST_ROW == row+1 || LAST_ROW == row+1) { // all other pieces, black or white

				dict = (PieceType)column;
				switch (dict)
				{
				case PieceType::ROOK:
					this->_pieces[row][column] = new Rook(getCoordinate(row, column),(FIRST_ROW == row+1 ? B_ROOK_CHAR : W_ROOK_CHAR));
					break;
				case PieceType::KNIGTH:
					this->_pieces[row][column] = new Knigth(getCoordinate(row, column), (FIRST_ROW == row+1 ? B_KNIGHT_CHAR : W_KNIGHT_CHAR));
					break;
				case PieceType::BISHOP:
					this->_pieces[row][column] = new Bishop(getCoordinate(row, column), (FIRST_ROW == row+1 ? B_BISHOP_CHAR : W_BISHOP_CHAR));
					break;
				case PieceType::QUEEN:
					this->_pieces[row][column] = new Queen(getCoordinate(row, column), (FIRST_ROW == row+1 ? B_QUEEN_CHAR : W_QUEEN_CHAR));
					break;
				case PieceType::KING:
					this->_pieces[row][column] = new King(getCoordinate(row, column), (FIRST_ROW == row+1 ? B_KING_CHAR : W_KING_CHAR));
					break;
				case PieceType::BISHOP2:
					this->_pieces[row][column] = new Bishop(getCoordinate(row, column), (FIRST_ROW == row+1 ? B_BISHOP_CHAR : W_BISHOP_CHAR));
					break;
				case PieceType::KNIGTH2:
					this->_pieces[row][column] = new Knigth(getCoordinate(row, column), (FIRST_ROW == row+1 ? B_KNIGHT_CHAR : W_KNIGHT_CHAR));
					break;
				case PieceType::ROOK2:
					this->_pieces[row][column] = new Rook(getCoordinate(row, column), (FIRST_ROW == row+1 ? B_ROOK_CHAR : W_ROOK_CHAR));
					break;
				}
			}
			else { // none of the options - put nullptr (no piece in this place)
				this->_pieces[row][column] = nullptr;
			}
		}
	}
}

std::string Board::getCoordinate(const int row, const int column) {
	std::string ret = "";

	ret += std::to_string(TO_CHAR + row);
	ret += std::to_string(column);

	return ret;
}



//Logic funcs

const char* Board::what() const noexcept {
	return "No error codes in the possition check are found";
}

bool Board::movePeice(const std::string& coordinate) noexcept {
	bool happend = false;

	int srcRow = coordinate[0] - TO_CHAR;
	int srcColumn = coordinate[1] - NUM_STR_TO_INT;
	int dstRow = coordinate[3] - TO_CHAR;
	int dstColumn = coordinate[4] - NUM_STR_TO_INT;

	// check if the move is valid
	try {
		isPositionValid(coordinate);
	}
	catch (const Board& e) { // error - move is valid
		happend = true;
		this->_pieces[dstRow][dstColumn] = this->_pieces[srcRow][srcColumn];
		this->_pieces[srcRow][srcColumn] = nullptr;
	}

	return happend;
}

std::string Board::isPositionValid(const std::string& coordinate) {
	std::string errCode = "";
	bool isValid = true;

	int srcRow = coordinate[0] - TO_CHAR;
	int srcColumn = coordinate[1] - NUM_STR_TO_INT;
	int dstRow = coordinate[3] - TO_CHAR;
	int dstColumn = coordinate[4] - NUM_STR_TO_INT;

	// check options for making the move invalid
	if (srcRow == srcColumn && dstRow == dstColumn) { // error code 7 - same coordinate
		isValid = false;
		errCode = "7";
	}
	// error code 5 - index out of range
	else if (ROW_COLUMN > srcRow || ROW_COLUMN > srcColumn || ROW_COLUMN > dstRow || ROW_COLUMN > dstColumn || // more then passible
		srcRow < 1 || srcColumn < 1 || dstRow < 1 || dstColumn < 1) { // less then passible

		isValid = false;
		errCode = "5";
	}
	// error code 3 - dst coord with piece of the same color
	else if (this->_pieces[dstRow][dstColumn] != nullptr && this->_pieces[srcRow][srcColumn] != nullptr &&
		// check if the dst piece is the same color as the src piece
		(IS_BLACK_PIECE(this->_pieces[dstRow][dstColumn]->getType()) && IS_BLACK_PIECE(this->_pieces[srcRow][srcColumn]->getType()) || 
		(IS_WHITE_PIECE(this->_pieces[dstRow][dstColumn]->getType()) && IS_WHITE_PIECE(this->_pieces[srcRow][srcColumn]->getType())) )) {

		isValid = false;
		errCode = "3";
	}
	else { // not error board-related found (RAISE error)
		throw Board(true);
	}

	return errCode;
}


Piece* Board::getPiece(const int row, const int column) const {
	return this->_pieces[row][column];
}
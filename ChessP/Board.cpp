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
	columnDictBlack blackDict;
	columnDictWhite whiteDict;

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
			else if (FIRST_ROW == row + 1) { // all other pieces, black

				blackDict = (columnDictBlack)column;
				switch (blackDict)
				{
				case columnDictBlack::ROOK:
					this->_pieces[row][column] = new Rook(getCoordinate(row, column), B_ROOK_CHAR);
					break;
				case columnDictBlack::KNIGTH:
					this->_pieces[row][column] = new Knigth(getCoordinate(row, column), B_KNIGHT_CHAR);
					break;
				case columnDictBlack::BISHOP:
					this->_pieces[row][column] = new Bishop(getCoordinate(row, column), B_BISHOP_CHAR);
					break;
				case columnDictBlack::QUEEN:
					this->_pieces[row][column] = new Queen(getCoordinate(row, column), B_QUEEN_CHAR);
					break;
				case columnDictBlack::KING:
					this->_pieces[row][column] = new King(getCoordinate(row, column), B_KING_CHAR);
					break;
				case columnDictBlack::BISHOP2:
					this->_pieces[row][column] = new Bishop(getCoordinate(row, column), B_BISHOP_CHAR);
					break;
				case columnDictBlack::KNIGTH2:
					this->_pieces[row][column] = new Knigth(getCoordinate(row, column), B_KNIGHT_CHAR);
					break;
				case columnDictBlack::ROOK2:
					this->_pieces[row][column] = new Rook(getCoordinate(row, column), B_ROOK_CHAR);
					break;
				}
			}
			else if (LAST_ROW == row + 1) {

				whiteDict = (columnDictWhite)column;
				switch (whiteDict)
				{
				case columnDictWhite::ROOK:
					this->_pieces[row][column] = new Rook(getCoordinate(row, column), W_ROOK_CHAR);
					break;
				case columnDictWhite::KNIGTH:
					this->_pieces[row][column] = new Knigth(getCoordinate(row, column), W_KNIGHT_CHAR);
					break;
				case columnDictWhite::BISHOP:
					this->_pieces[row][column] = new Bishop(getCoordinate(row, column), W_BISHOP_CHAR);
					break;
				case columnDictWhite::KING:
					this->_pieces[row][column] = new King(getCoordinate(row, column), W_KING_CHAR);
					break;
				case columnDictWhite::QUEEN:
					this->_pieces[row][column] = new Queen(getCoordinate(row, column), W_QUEEN_CHAR);
					break;
				case columnDictWhite::BISHOP2:
					this->_pieces[row][column] = new Bishop(getCoordinate(row, column), W_BISHOP_CHAR);
					break;
				case columnDictWhite::KNIGTH2:
					this->_pieces[row][column] = new Knigth(getCoordinate(row, column), W_KNIGHT_CHAR);
					break;
				case columnDictWhite::ROOK2:
					this->_pieces[row][column] = new Rook(getCoordinate(row, column), W_ROOK_CHAR);
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


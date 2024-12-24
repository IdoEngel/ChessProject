#include "Board.h"

//Constractors/Distractors
Board::Board(const bool forException) : _isForException(forException) {

	if (!forException) { // if not for exception

		this->_pieces = new Piece * *[ROW_COLUMN];

		int row = 0; // crreate a 2d arr
		int col = 0;
		for (row = 0; row < ROW_COLUMN; row++) {
			this->_pieces[row] = new Piece * [ROW_COLUMN];
			for (col = 0; col < ROW_COLUMN; col++) {
				this->_pieces[row][col] = nullptr;
			}
		}
		createDefault();
	}
	else {
		this->_pieces = nullptr;
	}
}
//Board::Board(const Board& other) : _isForException(other._isForException) {
//	if (!this->_isForException) {
//
//		// create the 2d arr
//		this->_pieces = new Piece**[ROW_COLUMN];
//		int row = 0; // crreate a 2d arr
//		for (row = 0; row < ROW_COLUMN; row++) {
//			this->_pieces[row] = new Piece*[ROW_COLUMN];
//		}
//
//		// copy the pieces
//		int column = 0; // like 2d arr
//		for (row = 0; row < ROW_COLUMN; row++) {
//			for (column = 0; column < ROW_COLUMN; column++) {
//				this->_pieces[row][column] = other._pieces[row][column];
//			}
//		}
//	}
//	else {
//		this->_pieces = nullptr;
//	}
//}

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
				//this->_pieces[row][column] = new Pown(Board::coordsToStr(row, column), B_PAWN_CHAR);
				this->_pieces[row][column] = nullptr;
			}
			else if (SECOND_ROW_OF_SOLDIERS == row + 1) { //white
				//this->_pieces[row][column] = new Pown(Board::coordsToStr(row, column), B_PAWN_CHAR);
				this->_pieces[row][column] = nullptr;
			}
			else if (FIRST_ROW == row + 1 || LAST_ROW == row + 1) { // all other pieces, black or white

				dict = (PieceType)column;
				switch (dict)
				{
				case PieceType::ROOK:
					this->_pieces[row][column] = new Rook(Board::coordsToStr(row, column), (FIRST_ROW == row + 1 ? B_ROOK_CHAR : W_ROOK_CHAR));
					//this->_pieces[row][column] = nullptr;
					break;
				case PieceType::KNIGTH:
					//this->_pieces[row][column] = new Knigth(Board::coordsToStr(row, column), (FIRST_ROW == row+1 ? B_KNIGHT_CHAR : W_KNIGHT_CHAR));
					this->_pieces[row][column] = nullptr;
					break;
				case PieceType::BISHOP:
					this->_pieces[row][column] = new Bishop(Board::coordsToStr(row, column), (FIRST_ROW == row+1 ? B_BISHOP_CHAR : W_BISHOP_CHAR));
					//this->_pieces[row][column] = nullptr;
					break;
				case PieceType::QUEEN:
					this->_pieces[row][column] = new Queen(Board::coordsToStr(row, column), (FIRST_ROW == row+1 ? B_QUEEN_CHAR : W_QUEEN_CHAR));
					//this->_pieces[row][column] = nullptr;
					break;
				case PieceType::KING:
					this->_pieces[row][column] = new King(Board::coordsToStr(row, column), (FIRST_ROW == row + 1 ? B_KING_CHAR : W_KING_CHAR));
					//this->_pieces[row][column] = nullptr;
					break;
				case PieceType::BISHOP2:
					this->_pieces[row][column] = new Bishop(Board::coordsToStr(row, column), (FIRST_ROW == row+1 ? B_BISHOP_CHAR : W_BISHOP_CHAR));
					//this->_pieces[row][column] = nullptr;
					break;
				case PieceType::KNIGTH2:
					//this->_pieces[row][column] = new Knigth(Board::coordsToStr(row, column), (FIRST_ROW == row+1 ? B_KNIGHT_CHAR : W_KNIGHT_CHAR));
					this->_pieces[row][column] = nullptr;
					break;
				case PieceType::ROOK2:
					this->_pieces[row][column] = new Rook(Board::coordsToStr(row, column), (FIRST_ROW == row + 1 ? B_ROOK_CHAR : W_ROOK_CHAR));
					//this->_pieces[row][column] = nullptr;
					break;
				}
			}
			else { // none of the options - put nullptr (no piece in this place)
				this->_pieces[row][column] = nullptr;
			}
		}
	}
}


//Logic funcs

const char* Board::what() const noexcept {
	return "No error codes in the possition check are found";
}

bool Board::movePeice(const std::string& coordinate) noexcept {
	bool isCode8 = false;

	intArr points = Board::strToCoords(coordinate);
	int srcRow = points.get()->at(SRC_START_INDEX);
	int srcColumn = points.get()->at(SRC_START_INDEX + 1);
	int dstRow = points.get()->at(DST_START_INDEX);
	int dstColumn = points.get()->at(DST_START_INDEX + 1);
	Piece* p;

	// check if the move is valid
	try {
		isPositionValid(coordinate);
	}
	catch (const Board& e) { // error - move is valid

		// the dst coord is white or black king
		if (this->_pieces[dstRow][dstColumn] != nullptr &&
			(this->_pieces[dstRow][dstColumn]->getType() == B_KING_CHAR ||
			this->_pieces[dstRow][dstColumn]->getType() == W_KING_CHAR)) {
			isCode8 = true;
		}
		delete this->_pieces[dstRow][dstColumn]; //delete if needed
		this->_pieces[dstRow][dstColumn] = this->_pieces[srcRow][srcColumn];
		this->_pieces[srcRow][srcColumn] = nullptr;
		p = this->_pieces[srcRow][srcColumn];
	}

	return isCode8;
}

std::string Board::isPositionValid(const std::string& coordinate) {
	std::string errCode = "";

	intArr points = Board::strToCoords(coordinate);
	int srcRow = points.get()->at(SRC_START_INDEX);
	int srcColumn = points.get()->at(SRC_START_INDEX + 1);
	int dstRow = points.get()->at(DST_START_INDEX);
	int dstColumn = points.get()->at(DST_START_INDEX + 1);

	// check options for making the move invalid
	if (srcRow == srcColumn && dstRow == dstColumn) { // error code 7 - same coordinate
		errCode = CODE_7;
	}
	// error code 5 - index out of range
	else if (!(srcRow >= 0 && srcRow < ROW_COLUMN &&
		srcColumn >= 0 && srcColumn < ROW_COLUMN &&
		dstRow >= 0 && dstRow < ROW_COLUMN &&
		dstColumn >= 0 && dstColumn < ROW_COLUMN)) { // less then passible

		errCode = CODE_5;
	}
	//code 2 - src coord is empty (part one of code 2)
	else if (this->_pieces[srcRow][srcColumn] == nullptr) {
		errCode = CODE_2;
	}
	// error code 3 - dst coord with piece of the same color
	else if (this->_pieces[dstRow][dstColumn] != nullptr && this->_pieces[srcRow][srcColumn] != nullptr &&
		// check if the dst piece is the same color as the src piece
		(IS_BLACK_PIECE(this->_pieces[dstRow][dstColumn]->getType()) && IS_BLACK_PIECE(this->_pieces[srcRow][srcColumn]->getType()) ||
			(IS_WHITE_PIECE(this->_pieces[dstRow][dstColumn]->getType()) && IS_WHITE_PIECE(this->_pieces[srcRow][srcColumn]->getType())))) {

		errCode = CODE_3;
	}
	else { // not error board-related found (RAISE error)
		throw Board(true);
	}

	return errCode;
}


Piece* Board::getPiece(const int row, const int column) const {
	return this->_pieces[row][column];
}

std::string Board::coordsToStr(const int row, const int column) {
	std::string coord = "";

	coord += (char)(row + TO_CHAR);
	coord += std::to_string(column + 1);

	return coord;
}

std::string Board::coordsToStr(const int srcRow, const int srcColumn, const int dstRow, const int dstColumn) {
	return (Board::coordsToStr(srcRow, srcColumn) + Board::coordsToStr(dstRow, dstColumn)); // use the function for one coord twice
}

intArr Board::strToCoords(const std::string& coords) {
	intArr points = std::make_unique<std::vector<int>>(coords.length());
	int arr[LEN_OF_TWO_COORDS] = { 0 };
	int point = 0;

	points.get()->resize(0); // no elements before
	int i = 0;
	for (i = 0; i < coords.length(); i++) {

		if (!(i % 2 == 0)) { // a number
			point = (int)((coords[i] - NUM_STR_TO_INT) - 1); // get pure index
			point = (ROW_COLUMN - 1) - point; //fix index to the board 
			arr[i] = point;
		}
		else { // a latter
			arr[i] = (int)(coords[i] - TO_CHAR);
		}
	}

	points.get()->push_back(arr[SRC_START_INDEX + 1]);
	points.get()->push_back(arr[SRC_START_INDEX]);

	if (coords.length() == LEN_OF_TWO_COORDS) { // there are 2 coords
		points.get()->push_back(arr[DST_START_INDEX + 1]);
		points.get()->push_back(arr[DST_START_INDEX]);
	}




	return points;
}


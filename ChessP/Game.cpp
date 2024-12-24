#include "Game.h"

//Constractor/Destractor

Game::Game(const bool forException) :
	_board(new Board()), _numOfMoves(0), _ifForException(forException) {
	if (!forException) {
		this->_playes[0] = Player(WHITE);
		this->_playes[1] = Player(BLACK);
	}
	else {
		this->_ifForException = true;
	}

}

Game::~Game() {
	delete this->_board;
}
//Helping/getters functions

Board Game::getBoard() const noexcept {
	return Board(this->_board);
}

char Game::getCurrPlayerColor() const noexcept {
	return (this->_numOfMoves % 2 == 0 ? this->_playes[0].getColor() : this->_playes[1].getColor());
}

char Game::getOpponentPlayerColor() const noexcept {
	return (this->_numOfMoves % 2 == 0 ? this->_playes[1].getColor() : this->_playes[0].getColor());
}

Piece* Game::getKing(const bool isMyKing) const noexcept {
	char kingColor = (isMyKing ? this->getCurrPlayerColor() : this->getOpponentPlayerColor());
	Piece* king = nullptr;

	intArr coords;
	int rowPiece = 0;
	int columnPiece = 0;

	int row = 0;
	int column = 0;
	for (row = 0; row < ROW_COLUMN; row++) {
		for (column = 0; column < ROW_COLUMN; column++) {

			//transfer to the right coords
			coords = Board::strToCoords(Board::coordsToStr(row, column));
			rowPiece = coords.get()->at(SRC_START_INDEX);
			columnPiece = coords.get()->at(SRC_START_INDEX + 1);

			//make sure the piece is not nullptr
			if (this->_board->getPiece(rowPiece, columnPiece) != nullptr) {

				// if both are black
				if (IS_BLACK_PIECE(this->_board->getPiece(rowPiece, columnPiece)->getType()) &&
					IS_BLACK_PIECE(kingColor) &&
					this->_board->getPiece(rowPiece, columnPiece)->getType() == B_KING_CHAR) { // take only the king 
					king = this->_board->getPiece(rowPiece, columnPiece);
				}
				// if both are white
				else if (IS_WHITE_PIECE(this->_board->getPiece(rowPiece, columnPiece)->getType()) &&
					IS_WHITE_PIECE(kingColor) &&
					this->_board->getPiece(rowPiece, columnPiece)->getType() == W_KING_CHAR) { // take only the king 
					king = this->_board->getPiece(rowPiece, columnPiece);
				}
			}
		}
	}

	return king;
}


std::string Game::getCoordinatesOfPiece(const Piece* piece) const noexcept { //MAYBE transfer to Board (?)
	char type = piece->getType();
	std::string coordinates = "";
	Piece* p = nullptr;

	intArr coords;
	int rowPiece = 0;
	int columnPiece = 0;

	int row = 0;
	int column = 0;
	for (row = 0; row < ROW_COLUMN; row++) {
		for (column = 0; column < ROW_COLUMN; column++) {

			//transfer to the right coords
			coords = Board::strToCoords(Board::coordsToStr(row, column));
			rowPiece = coords.get()->at(SRC_START_INDEX);
			columnPiece = coords.get()->at(SRC_START_INDEX + 1);

			p = this->_board->getPiece(static_cast<const int>(rowPiece), static_cast<const int>(columnPiece));
			if (p != nullptr) { // make sure the piece is not nullptr
				if (p->getType() == type) { // if the type is the same
					coordinates = Board::coordsToStr(row, column);
				}
			}
		}
	}
	return coordinates;
}

bool Game::isCurrTurnMatchColorSelected(const Piece* piece) const noexcept {
	bool isVal = false;

	if (piece != nullptr) {
		if (this->_numOfMoves % 2 == 0) {
			isVal = IS_WHITE_PIECE(piece->getType());
		}
		else {
			isVal = IS_BLACK_PIECE(piece->getType());
		}
	}
	return isVal;
}

int Game::lenOfPassibleMoves(const std::string& coord) const noexcept {
	int srcRow = 0;
	int srcColumn = 0;
	int len = 0;
	Piece* piece = nullptr;
	std::vector<std::string> moves;

	//get only the part with the coordinate to the curr position of the piece
	//srcRow = (int)(coord[0] - TO_CHAR);
	//srcColumn = (int)(coord[1] - NUM_STR_TO_INT) - 1;

	intArr points = Board::strToCoords(coord);

	srcRow = points.get()->at(SRC_START_INDEX);
	srcColumn = points.get()->at(SRC_START_INDEX + 1);

	piece = this->_board->getPiece(srcRow, srcColumn);
	if (piece != nullptr) {
		moves = piece->possibleMoves(coord);
		len = moves.size();

		// clean vector
		moves.clear();
		moves.resize(0);
	}

	return len;
}

//Logic funcs	

std::ostream& operator<<(std::ostream& os, const Game& g) {
	int row = 0;
	int column = 0;
	Piece* p = nullptr;

	for (row = 0; row < ROW_COLUMN; row++) {
		for (column = 0; column < ROW_COLUMN; column++) {

			p = g._board->getPiece(row, column);
			if (p == nullptr) {
				os << EMPTY << " ";
			}
			else {
				os << p->getType() << " ";
			}
		}
		os << std::endl;
	}

	return os;
}

std::string Game::play(const std::string& coordinates) noexcept {
	std::string code = "";
	//TODO: check move in the game level
	//TODO: raise error when the game is over
	code = this->codeForGraphics(coordinates);

	if (code == CODE_0 || code == CODE_1) { // code "0" - no errors found
		
		if (this->_board->movePeice(coordinates)) { //returns if the king was eaten
			code = CODE_8;
		}
		this->_numOfMoves++; //next turn only if code 0 or 1 (successe)
	}

	return code;
}

const char* Game::what() const noexcept {
	return (this->_numOfMoves % 2 == 0 ? WHITE_STR : BLACK_STR);
}

std::string Game::codeForGraphics(const std::string& coordinats) const noexcept {
	char type = ' ';
	intArr points;
	std::string code = CODE_0;
	int row = 0;
	int column = 0;

	try {
		code = this->_board->isPositionValid(coordinats);
	}
	catch (const Board& e) { // error - move is valid (no errors found)
		points = Board::strToCoords(coordinats);
		row = points.get()->at(SRC_START_INDEX);
		column = points.get()->at(SRC_START_INDEX + 1);

		type = this->_board->getPiece(row, column)->getType();

		//check the src coord (match the color) - the second part of code 2
		if (!isCurrTurnMatchColorSelected(this->_board->getPiece(row, column))) {
			code = CODE_2;
		}
		// code 6 - the move of the piece is valid
		else if (!isWayClear(this->_board->getPiece(row, column)->possibleMoves(coordinats)) ||
			(lenOfPassibleMoves(coordinats) == 0)) { // invalid move (logicly)
			code = CODE_6;
		}
		//code 4 - self check (first part - if king is moving)
		else if ((((type == W_KING_CHAR) || (type == B_KING_CHAR))) && //if this is a king, continue to the check
			isSelfChecked(coordinats, true)) { //getting the king of the current player
			code = CODE_4;
		}
		// code 4 - self check (second part - if the king mo moving) - UNCHECKED
		else if ((!((type == W_KING_CHAR) || (type == B_KING_CHAR))) && // not the king
			(isSelfChecked(getCoordinatesOfPiece(getKing(MY_KING))))) {
			code = CODE_4;
		}
		//code 1 (valid) - check if check on other player
		else if (isCheckedOnOpponent(getCoordinatesOfPiece(getKing(OPPO_KING)), coordinats)) {
			code = CODE_1;
		}
	}

	return code;
}

bool Game::isCheckedOnOpponent(const std::string& kingCoordinate, const std::string& pieceCoords) const noexcept {
	std::string kingDest = kingCoordinate.substr(kingCoordinate.size() - 2);
	std::string pieceDest = pieceCoords.substr(pieceCoords.size() - 2);
	std::string pieceSrc = pieceCoords.substr(0, 2);

	bool isCheck = false;
	std::string fullCoord = "";
	std::vector<std::string> allMoves;

	intArr coords;
	int rowPiece = 0;
	int columnPiece = 0;
	Piece* piece = nullptr;

	int row = 0;
	int column = 0;
	for (row = 0; row < ROW_COLUMN; row++) {
		for (column = 0; column < ROW_COLUMN; column++) {

			//transfer to the right coords
			coords = Board::strToCoords(Board::coordsToStr(row, column));
			rowPiece = coords.get()->at(SRC_START_INDEX);
			columnPiece = coords.get()->at(SRC_START_INDEX + 1);

			if (this->_board->getPiece(rowPiece, columnPiece) != nullptr && // make sure the piece is not nullptr
				//make sure the piece is not the king
				Board::coordsToStr(row, column) != kingDest &&
				// make sure the piece is not the same color as the king
				//((IS_BLACK_PIECE(this->_board->getPiece(rowPiece, columnPiece)->getType()) && IS_BLACK_PIECE(this->getCurrPlayerColor())) ||
				isCurrTurnMatchColorSelected(this->_board->getPiece(rowPiece, columnPiece))) {
				piece = this->_board->getPiece(rowPiece, columnPiece);

				fullCoord = Board::coordsToStr(row, column) + kingDest;
				allMoves = this->_board->getPiece(rowPiece, columnPiece)->possibleMoves(fullCoord);

				if (allMoves.size() != 0 && isWayClear(allMoves)) {
					isCheck = true;
				}

				//clear the vector
				allMoves.clear();
				allMoves.resize(0);
			}
		}
	}

	//check if the curr play coused check
	coords = Board::strToCoords(pieceSrc);
	rowPiece = coords.get()->at(SRC_START_INDEX);
	columnPiece = coords.get()->at(SRC_START_INDEX + 1);

	piece = this->_board->getPiece(rowPiece, columnPiece);
	allMoves = piece->possibleMoves(pieceDest + kingDest);

	if (allMoves.size() != 0 && isWayClear(allMoves)) {
		isCheck = true;
	}

	//clear the vector
	allMoves.clear();
	allMoves.resize(0);

	return isCheck;
}


bool Game::isSelfChecked(const std::string& kingCoordinate, const bool isKingPlaying) const noexcept {
	std::string kingDest = kingCoordinate.substr(kingCoordinate.size() - 2);
	bool isCheck = false;
	std::string fullCoord = "";
	std::string lastMove = "";
	std::vector<std::string> allMoves;

	intArr coords;
	int rowPiece = 0;
	int columnPiece = 0;
	Piece* p = nullptr;

	int row = 0;
	int column = 0;
	for (row = 0; row < ROW_COLUMN; row++) {
		for (column = 0; column < ROW_COLUMN; column++) {

			//transfer to the right coords
			coords = Board::strToCoords(Board::coordsToStr(row, column));
			rowPiece = coords.get()->at(SRC_START_INDEX);
			columnPiece = coords.get()->at(SRC_START_INDEX + 1);

			if (this->_board->getPiece(rowPiece, columnPiece) != nullptr && // make sure the piece is not nullptr
				//make sure the piece is not the king
				Board::coordsToStr(row, column) != kingDest &&
				// make sure the piece is not the same color as the king
				//((IS_BLACK_PIECE(this->_board->getPiece(rowPiece, columnPiece)->getType()) && IS_BLACK_PIECE(this->getCurrPlayerColor())) ||
				!isCurrTurnMatchColorSelected(this->_board->getPiece(rowPiece, columnPiece))) {
				p = this->_board->getPiece(rowPiece, columnPiece);

				fullCoord = Board::coordsToStr(row, column) + kingDest;
				allMoves = this->_board->getPiece(rowPiece, columnPiece)->possibleMoves(fullCoord);

				if (allMoves.size() != 0 && isWayClear(allMoves)) {
					isCheck = true;
				}

				//if king is playing - need to check that the king dont "block itself"
				if (isKingPlaying) {
					//try to get to the last elem, if vector is empty - skip all (using the try-block)
					try {
						lastMove = allMoves.at(allMoves.size() - 2);

						coords = Board::strToCoords(lastMove);
						rowPiece = coords.get()->at(SRC_START_INDEX);
						columnPiece = coords.get()->at(SRC_START_INDEX + 1);

						//check if the last move in moves is tha king that just moving
						if (this->_board->getPiece(rowPiece, columnPiece) != nullptr && //check that not nullptr
							//check that the king is on the last move
							(this->_board->getPiece(rowPiece, columnPiece)->getType() == W_KING_CHAR ||
								this->_board->getPiece(rowPiece, columnPiece)->getType() == B_KING_CHAR)) {
							isCheck = true;
						}
					}
					catch (std::out_of_range& e) {
						//.... skiping
					}
				}

				//clear the vector
				allMoves.clear();
				allMoves.resize(0);
			}
		}
	}

	return isCheck;
}



bool Game::isWayClear(std::vector<std::string> moves) const noexcept {
	bool isClear = true;

	int dstRow = 0;
	int dstColumn = 0;
	Piece* lastPiece = nullptr;
	intArr points;

	/*Not including the last index because the last contains the coord that might be
	with piece that the curr player can eat - check later*/
	
	int i = 0;
	int size = moves.size();
	for (i = 0; i < moves.size() - 1; i++) { // not include the ladt index
		/*dstRow = (int)(moves[i][0] - TO_CHAR);
		dstColumn = (int)(moves[i][1] - NUM_STR_TO_INT) - 1;*/
		try {
			points = Board::strToCoords(moves.at(i));

			dstRow = points.get()->at(SRC_START_INDEX);
			dstColumn = points.get()->at(SRC_START_INDEX + 1);

			if (this->_board->getPiece(dstRow, dstColumn) != nullptr) {
				isClear = false;
			}
		}
		catch (const std::out_of_range& e) {
			break;
			//none - catch if the vector is empty
		}
	}

	//check last index
	//get the last coord and the piece inside it
	try {
	
		points = Board::strToCoords(moves.at(moves.size() - 1));

		dstRow = points.get()->at(SRC_START_INDEX);
		dstColumn = points.get()->at(SRC_START_INDEX + 1);

		lastPiece = this->_board->getPiece(dstRow, dstColumn);

		//check
		if (lastPiece != nullptr && isCurrTurnMatchColorSelected(lastPiece)) { //if match - cannot get to the dest (base case is "isClear = true"
			isClear = false;
		}
	}
	catch (const std::out_of_range& e) {
		//none - catch if the vector is empty
	}
	

	return isClear;
}


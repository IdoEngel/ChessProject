#include "Game.h"

//Constractor/Destractor

Game::Game(const bool forException) {
	if (!forException) {
		this->_board = new Board();
		this->_playes[0] = Player(WHITE);
		this->_playes[1] = Player(BLACK);
		this->_numOfMoves = 0;
		this->_ifForException = false;
	}
	else {
		this->_ifForException = true;
		this->_board = nullptr;
		this->_numOfMoves = 0;
	}

}

Game::~Game() {
	delete this->_board;
}
//Helping/getters/private functions

Board Game::getBoard() const noexcept {
	return Board(this->_board);
}

char Game::getCurrPlayerColor() const noexcept {
	return (this->_numOfMoves % 2 == 0 ? this->_playes[0].getColor() : this->_playes[1].getColor());
}

Piece* Game::getKing() const noexcept {
	char kingColor = this->getCurrPlayerColor();
	Piece* king = nullptr;

	int row = 0;
	int column = 0;
	for (row = 0; row < ROW_COLUMN; row++) {
		for (column = 0; column < ROW_COLUMN; column++) {

			//make sure the piece is not nullptr
			if (this->_board->getPiece(row, column) != nullptr) {

				// if both are black
				if (IS_BLACK_PIECE(this->_board->getPiece(row, column)->getType()) && 
					IS_BLACK_PIECE(kingColor)) {
					king = this->_board->getPiece(row, column);
				}
				// if both are white
				else if (IS_WHITE_PIECE(this->_board->getPiece(row, column)->getType()) &&
					IS_WHITE_PIECE(kingColor)) {
					king = this->_board->getPiece(row, column);
				}
			}
		}
	}

	return king;
}

std::string Game::getCoordinates(const Piece* piece) const noexcept {
	char type = piece->getType();
	std::string coordinates = "";

	int row = 0;
	int column = 0;
	for (row = 0; row < ROW_COLUMN; row++) {
		for (column = 0; column < ROW_COLUMN; column++) {

			if (this->_board->getPiece(row, column) != nullptr) { // make sure the piece is not nullptr
				if (this->_board->getPiece(row, column)->getType() == type) { // if the type is the same
					coordinates += (char)(row + TO_CHAR);
					coordinates += (char)(column + NUM_STR_TO_INT);
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

//Logic funcs	

std::ostream& operator<<(std::ostream& os, const Game& g) {
	int row = 0;
	int column = 0;
	Piece* p = nullptr;

	for (row = 0; row < ROW_COLUMN; row++) {
		for (column = 0; column < ROW_COLUMN; column++) {

			p = g.getBoard().getPiece(row, column);
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

std::string Game::play(const std::string& coordinates) {
	std::string code = "";
	//TODO: check move in the game level
	//TODO: raise error when the game is over
	this->_board->isPositionValid(coordinates);
	this->_board->movePeice(coordinates);

	this->_numOfMoves++;

	return code;
}

const char* Game::what() const noexcept {
	return (this->_numOfMoves % 2 == 0 ? WHITE_STR : BLACK_STR);
}

std::string Game::codeForGraphics(const std::string& coordinats) const noexcept {
	std::string code = "0";
	try {
		code = this->_board->isPositionValid(coordinats);
	}
	catch (const Board& e) { // error - move is valid (no errors found)

		//check the src coord (match the color)
		if (!isCurrTurnMatchColorSelected(this->_board->getPiece(coordinats[0] - TO_CHAR, coordinats[1] - NUM_STR_TO_INT))) {
			code = CODE_2;
		}
		else if (isSelfCheck(getCoordinates(getKing()))) {
			code = CODE_4;
		}
	}

	return code;
}

bool Game::isSelfCheck(const std::string kingCoordinate) const noexcept {
	bool isCheck = false;
	std::string fullCoord = "";
	std::vector<std::string> allMoves;

	int row = 0;
	int column = 0;
	for (row = 0; row < ROW_COLUMN; row++) {
		for (column = 0; column < ROW_COLUMN; column++) {
			if (this->_board->getPiece(row, column) != nullptr && // make sure the piece is not nullptr
				//make sure the piece is not the king
				this->_board->getCoordinate(row, column) != kingCoordinate &&
				// make sure the piece is not the same color as the king
				(!(IS_BLACK_PIECE(this->_board->getPiece(row, column)->getType()) && IS_BLACK_PIECE(this->getCurrPlayerColor())) ||
				 !(IS_WHITE_PIECE(this->_board->getPiece(row, column)->getType()) && IS_WHITE_PIECE(this->getCurrPlayerColor())) )) {

				fullCoord = this->_board->getCoordinate(row, column) + kingCoordinate;
				allMoves = this->_board->getPiece(row, column)->possibleMoves(fullCoord);

				if (isWayClear(allMoves)) {
					isCheck = true;
				}
			}
		}
	}

	return isCheck;
}


bool Game::isWayClear(std::vector<std::string> moves) const {
	bool isClear = true;

	int dstRow = 0;
	int dstColumn = 0;

	int i = 0;
	for (i = 0; i < moves.size(); i++) {
		dstRow = (int)(moves[i][0] - TO_CHAR);
		dstColumn = (int)(moves[i][1] - NUM_STR_TO_INT);

		if (this->_board->getPiece(dstRow, dstColumn) != nullptr) {
			isClear = false;
		}
	}

	return isClear;
}

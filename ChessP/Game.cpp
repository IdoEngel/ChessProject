#include "Game.h"

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

Board Game::getBoard() const {
	return Board(this->_board);
}

char Game::getCurrPlayerColor() const {
	return (this->_numOfMoves % 2 == 0 ? this->_playes[0].getColor() : this->_playes[1].getColor());
}

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
}


void Game::play(const std::string& coordinates) {
	//TODO: check move in the game level
	this->_board->movePeice(coordinates);

	this->_numOfMoves++;	
}
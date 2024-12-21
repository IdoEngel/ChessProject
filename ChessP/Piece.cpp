#include "Piece.h"
Piece::Piece(const char type)
{
	this->_type = type;
}
Piece::~Piece()
{
	this->_type = '\0';
}
char Piece::getType() const
{
	return this->_type;
}
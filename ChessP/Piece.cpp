#include "Piece.h"
Piece::Piece(const char type, const std::string& position)
{
	this->_type = type;
	setPosition(position);
}
Piece::~Piece()
{
	this->_type = '\0';
}
void Piece::setPosition(const std::string& position)
{
	this->_position = position;
}
std::string Piece::getPositon() const
{
	return this->_position;
}
char Piece::getType() const
{
	return this->_type;
}
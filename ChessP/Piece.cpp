#include "Piece.h"
Piece::Piece(const char type, const std::string& position)
{
	this->_type = type;
	setPosition(position);   //calling func that sets the position//
}
Piece::~Piece()
{
	this->_type = '\0';  //setting type to null//
}
void Piece::setPosition(const std::string& position)
{
	this->_position = position;  //setting the position//
}
std::string Piece::getPositon() const
{
	return this->_position;   //returning the position//
}
char Piece::getType() const
{
	return this->_type;  //returning the type//
}
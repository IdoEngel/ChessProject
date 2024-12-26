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
//this func checks if the dst is diagnolly right to src by 1 square//
bool Piece::isDiagnollyRight(const std::string& dstPosition)
{
	if (dstPosition[START_POSITION_LETTER] + 1 == dstPosition[DST_POSITION_LETTER] &&
		dstPosition[START_POSITION_NUMBER] + 1 == dstPosition[DST_POSITION_NUMBER])
	{
		return true;
	}
	else
	{
		return false;
	}
}
//this func checks if the dst is diagnolly left to src by 1 square//
bool Piece::isDiagnollyLeft(const std::string& dstPosition)
{
	if (dstPosition[START_POSITION_LETTER] - 1 == dstPosition[DST_POSITION_LETTER] &&
		dstPosition[START_POSITION_NUMBER] + 1 == dstPosition[DST_POSITION_NUMBER])
	{
		return true;
	}
	else
	{
		return false;
	}
}
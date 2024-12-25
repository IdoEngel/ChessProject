#include "Knight.h"
//constractor//
Knight::Knight(const std::string& position, const char type) : Piece(type, position)
{
}
//distractor//
Knight::~Knight()
{
	this->_way.clear();
}
std::vector<std::string> Knight::possibleMoves(const std::string& dstPosition)
{
	this->_way.clear();
	std::string currSquare = std::string(1, dstPosition[START_POSITION_LETTER]) + dstPosition[START_POSITION_NUMBER];

}

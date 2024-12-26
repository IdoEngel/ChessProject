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
	std::string currSquare = std::string(1, dstPosition[DST_POSITION_LETTER]) + dstPosition[DST_POSITION_NUMBER];
	//checking if the dst square is 2 cols above the src square, and if it 1 row to the left or row 1 to the rigth//
	if (dstPosition[START_POSITION_NUMBER] + 2 == dstPosition[DST_POSITION_NUMBER] &&
		(dstPosition[START_POSITION_LETTER] + 1 == dstPosition[DST_POSITION_LETTER] ||
			dstPosition[START_POSITION_LETTER] - 1 == dstPosition[DST_POSITION_LETTER]))
	{
		this->_way.push_back(currSquare);
	}
	//checking if the dst square is 2 cols below the src square, and if it 1 row to the left or 1 row to the rigth//
	else if (dstPosition[START_POSITION_NUMBER] -  2 == dstPosition[DST_POSITION_NUMBER] &&
		(dstPosition[START_POSITION_LETTER] + 1 == dstPosition[DST_POSITION_LETTER] ||
			dstPosition[START_POSITION_LETTER] - 1 == dstPosition[DST_POSITION_LETTER]))
	{
		this->_way.push_back(currSquare);
	}
	//checking if the dst square is 2 rows to the rigth of the src square, and if it 1 col above or 1 col below//
	else if (dstPosition[START_POSITION_LETTER] + 2 == dstPosition[DST_POSITION_LETTER] &&
		(dstPosition[START_POSITION_NUMBER] + 1 == dstPosition[DST_POSITION_NUMBER] ||
			dstPosition[START_POSITION_NUMBER] - 1 == dstPosition[DST_POSITION_NUMBER]))
	{
		this->_way.push_back(currSquare);
	}
	//checking if the dst square is 2 rows to the left of the src square, and if it 1 col above or 1 col below//
	else if (dstPosition[START_POSITION_LETTER] - 2 == dstPosition[DST_POSITION_LETTER] &&
		(dstPosition[START_POSITION_NUMBER] + 1 == dstPosition[DST_POSITION_NUMBER] ||
			dstPosition[START_POSITION_NUMBER] - 1 == dstPosition[DST_POSITION_NUMBER]))
	{
		this->_way.push_back(currSquare);
	}
	return this->_way;
}

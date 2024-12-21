#include "King.h"
King::King(const std::string& position, const char type) : Piece(type)
{
	setPosition(position);
}
King::~King()
{
	this->_position.clear();
	this->_way.clear();
}
void King::setPosition(const std::string& position)
{
	this->_position = position;
}
std::string King::getPositon() const
{
	return this->_position;
}

std::vector<std::string> King::possibleMoves(const std::string& dstPosition)
{
	std::string currSquare = std::string(1, dstPosition[START_POSITION_LETTER]) + dstPosition[START_POSITION_NUMBER];
	if (currSquare[START_POSITION_LETTER] == dstPosition[DST_POSITION_LETTER])
	{
		if (currSquare[START_POSITION_NUMBER] + 1 == dstPosition[DST_POSITION_NUMBER])
		{
			currSquare[START_POSITION_NUMBER] += 1;
			this->_way.push_back(currSquare);
		}
		else if (currSquare[START_POSITION_NUMBER] - 1 == dstPosition[DST_POSITION_NUMBER])
		{
			currSquare[START_POSITION_NUMBER] -= 1;
			this->_way.push_back(currSquare);
		}
	}
	else if (currSquare[START_POSITION_NUMBER] == dstPosition[DST_POSITION_NUMBER])
	{
		if (currSquare[START_POSITION_LETTER] + 1 == dstPosition[DST_POSITION_LETTER])
		{
			currSquare[START_POSITION_LETTER] += 1;
			this->_way.push_back(currSquare);
		}
		else if (currSquare[START_POSITION_LETTER] - 1 == dstPosition[DST_POSITION_LETTER])
		{
			currSquare[START_POSITION_LETTER] -= 1;
			this->_way.push_back(currSquare);
		}
	}
	else if ((currSquare[START_POSITION_LETTER] + 1 == dstPosition[DST_POSITION_LETTER]) &&
		(currSquare[START_POSITION_NUMBER] + 1 == dstPosition[DST_POSITION_NUMBER]))
	{
		currSquare[START_POSITION_LETTER] += 1;
		currSquare[START_POSITION_NUMBER] += 1;
		this->_way.push_back(currSquare);
	}
	else if ((currSquare[START_POSITION_LETTER] + 1 == dstPosition[DST_POSITION_LETTER]) &&
		(currSquare[START_POSITION_NUMBER] - 1 == dstPosition[DST_POSITION_NUMBER]))
	{
		currSquare[START_POSITION_LETTER] += 1;
		currSquare[START_POSITION_NUMBER] -= 1;
		this->_way.push_back(currSquare);
	}
	else if ((currSquare[START_POSITION_LETTER] - 1 == dstPosition[DST_POSITION_LETTER]) &&
		(currSquare[START_POSITION_NUMBER] + 1 == dstPosition[DST_POSITION_NUMBER]))
	{
		currSquare[START_POSITION_LETTER] -= 1;
		currSquare[START_POSITION_NUMBER] += 1;
		this->_way.push_back(currSquare);
	}
	else if ((currSquare[START_POSITION_LETTER] - 1 == dstPosition[DST_POSITION_LETTER]) &&
		(currSquare[START_POSITION_NUMBER] - 1 == dstPosition[DST_POSITION_NUMBER]))
	{
		currSquare[START_POSITION_LETTER] -= 1;
		currSquare[START_POSITION_NUMBER] -= 1;
		this->_way.push_back(currSquare);
	}
	return this->_way;
}

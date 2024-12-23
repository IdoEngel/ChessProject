#include "Queen.h"
Queen::Queen(const std::string& position, const char type) : Piece(type, position)
{
}
Queen::~Queen()
{
	this->_way.clear();
}
std::vector<std::string> Queen::possibleMoves(const std::string& dstPosition)
{
	this->_way.clear();
	std::string currSquare = std::string(1, dstPosition[START_POSITION_LETTER]) + dstPosition[START_POSITION_NUMBER];
	if (dstPosition[START_POSITION_LETTER] == dstPosition[DST_POSITION_LETTER])
	{
		if (dstPosition[START_POSITION_NUMBER] < dstPosition[DST_POSITION_NUMBER])
		{
			while (currSquare[START_POSITION_NUMBER] < dstPosition[DST_POSITION_NUMBER])
			{
				currSquare[START_POSITION_NUMBER] += 1;
				this->_way.push_back(currSquare);
			}
		}
		else if (dstPosition[START_POSITION_NUMBER] > dstPosition[DST_POSITION_NUMBER])
		{
			while (currSquare[START_POSITION_NUMBER] > dstPosition[DST_POSITION_NUMBER])
			{
				currSquare[START_POSITION_NUMBER] -= 1;
				this->_way.push_back(currSquare);
			}
		}
	}
	else if (dstPosition[START_POSITION_NUMBER] == dstPosition[DST_POSITION_NUMBER])
	{
		if (dstPosition[START_POSITION_LETTER] < dstPosition[DST_POSITION_LETTER])
		{
			while (currSquare[START_POSITION_LETTER] < dstPosition[DST_POSITION_LETTER])
			{
				currSquare[START_POSITION_LETTER] += 1;
				this->_way.push_back(currSquare);
			}
		}
		else if (dstPosition[START_POSITION_LETTER] > dstPosition[DST_POSITION_LETTER])
		{
			while (currSquare[START_POSITION_LETTER] > dstPosition[DST_POSITION_LETTER])
			{
				currSquare[START_POSITION_LETTER] -= 1;
				this->_way.push_back(currSquare);
			}
		}
	}
	else if(dstPosition[START_POSITION_LETTER] < dstPosition[DST_POSITION_LETTER] && dstPosition[START_POSITION_NUMBER] < dstPosition[DST_POSITION_NUMBER])
	{
		while (currSquare[START_POSITION_LETTER] < dstPosition[DST_POSITION_LETTER] && currSquare[START_POSITION_NUMBER] < dstPosition[DST_POSITION_NUMBER])
		{
			currSquare[START_POSITION_LETTER] += 1;
			currSquare[START_POSITION_NUMBER] += 1;
			this->_way.push_back(currSquare);
		}
	}
	else if (dstPosition[START_POSITION_LETTER] > dstPosition[DST_POSITION_LETTER] && dstPosition[START_POSITION_NUMBER] > dstPosition[DST_POSITION_NUMBER])
	{
		while (currSquare[START_POSITION_LETTER] > dstPosition[DST_POSITION_LETTER] && currSquare[START_POSITION_NUMBER] > dstPosition[DST_POSITION_NUMBER])
		{
			currSquare[START_POSITION_LETTER] -= 1;
			currSquare[START_POSITION_NUMBER] -= 1;
			this->_way.push_back(currSquare);
		}
	}
	else if (dstPosition[START_POSITION_LETTER] > dstPosition[DST_POSITION_LETTER] && dstPosition[START_POSITION_NUMBER] < dstPosition[DST_POSITION_NUMBER])
	{
		while (currSquare[START_POSITION_LETTER] > dstPosition[DST_POSITION_LETTER] && currSquare[START_POSITION_NUMBER] < dstPosition[DST_POSITION_NUMBER])
		{
			currSquare[START_POSITION_LETTER] -= 1;
			currSquare[START_POSITION_NUMBER] += 1;
			this->_way.push_back(currSquare);
		}
	}
	else if (dstPosition[START_POSITION_LETTER] < dstPosition[DST_POSITION_LETTER] && dstPosition[START_POSITION_NUMBER] > dstPosition[DST_POSITION_NUMBER])
	{
		while (currSquare[START_POSITION_LETTER] < dstPosition[DST_POSITION_LETTER] && currSquare[START_POSITION_NUMBER] > dstPosition[DST_POSITION_NUMBER])
		{
			currSquare[START_POSITION_LETTER] += 1;
			currSquare[START_POSITION_NUMBER] -= 1;
			this->_way.push_back(currSquare);
		}
	}
	return this->_way;
}
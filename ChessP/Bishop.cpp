#include "Bishop.h"
//constractor//
Bishop::Bishop(const std::string& position, const char type) : Piece(type, position)
{
}
//distractor//
Bishop::~Bishop()
{
	this->_way.clear();
}
//func that returns all squares from src to dst//
std::vector<std::string> Bishop::possibleMoves(const std::string& dstPosition)
{
	this->_way.clear();
	int lettersDif = 0;
	int numsDiff = 0;
	std::string currSquare = std::string(1, dstPosition[START_POSITION_LETTER]) + dstPosition[START_POSITION_NUMBER];

	if (dstPosition[START_POSITION_LETTER] != dstPosition[DST_POSITION_LETTER] && dstPosition[START_POSITION_NUMBER] != dstPosition[DST_POSITION_NUMBER])
	{
		//checking if the src is to the left, down, and diagnolly to the dst
		if (dstPosition[START_POSITION_LETTER] < dstPosition[DST_POSITION_LETTER] && dstPosition[START_POSITION_NUMBER] < dstPosition[DST_POSITION_NUMBER])
		{
			//getting the letter difference//
			lettersDif = static_cast<int>(dstPosition[DST_POSITION_LETTER] - dstPosition[START_POSITION_LETTER]);
			//getting the number difference//
			numsDiff = dstPosition[DST_POSITION_NUMBER] - dstPosition[START_POSITION_NUMBER];
			//if the difference is equal, its rigth movement for diagnolly//
			if (lettersDif == numsDiff)
			{
				//getting all squares from src to dst//
				while (currSquare[START_POSITION_LETTER] < dstPosition[DST_POSITION_LETTER] && currSquare[START_POSITION_NUMBER] < dstPosition[DST_POSITION_NUMBER])
				{
					currSquare[START_POSITION_LETTER] += 1;
					currSquare[START_POSITION_NUMBER] += 1;
					this->_way.push_back(currSquare);   //adding to the vector//
				}
			}
		}
		//checking if the src is to the rigth, up, and diagnolly to the dst
		else if (dstPosition[START_POSITION_LETTER] > dstPosition[DST_POSITION_LETTER] && dstPosition[START_POSITION_NUMBER] > dstPosition[DST_POSITION_NUMBER])
		{
			//getting the letter difference//
			lettersDif = static_cast<int>(dstPosition[START_POSITION_LETTER] - dstPosition[DST_POSITION_LETTER]);
			//getting the number difference//
			numsDiff = dstPosition[START_POSITION_NUMBER] - dstPosition[DST_POSITION_NUMBER];
			//if the difference is equal, its rigth movement for diagnolly//
			if (lettersDif == numsDiff)
			{
				//getting all squares from src to dst//
				while (currSquare[START_POSITION_LETTER] > dstPosition[DST_POSITION_LETTER] && currSquare[START_POSITION_NUMBER] > dstPosition[DST_POSITION_NUMBER])
				{
					currSquare[START_POSITION_LETTER] -= 1;
					currSquare[START_POSITION_NUMBER] -= 1;
					this->_way.push_back(currSquare);   //adding to the vector//
				}
			}
		}
		//checking if the src is to the rigth, down, and diagnolly to the dst
		else if (dstPosition[START_POSITION_LETTER] > dstPosition[DST_POSITION_LETTER] && dstPosition[START_POSITION_NUMBER] < dstPosition[DST_POSITION_NUMBER])
		{
			//getting the letter difference//
			lettersDif = static_cast<int>(dstPosition[START_POSITION_LETTER] - dstPosition[DST_POSITION_LETTER]);
			//getting the number difference//
			numsDiff = dstPosition[DST_POSITION_NUMBER] - dstPosition[START_POSITION_NUMBER];
			//if the difference is equal, its rigth movement for diagnolly//
			if (lettersDif == numsDiff)
			{
				//getting all squares from src to dst//
				while (currSquare[START_POSITION_LETTER] > dstPosition[DST_POSITION_LETTER] && currSquare[START_POSITION_NUMBER] < dstPosition[DST_POSITION_NUMBER])
				{
					currSquare[START_POSITION_LETTER] -= 1;
					currSquare[START_POSITION_NUMBER] += 1;
					this->_way.push_back(currSquare);   //adding to the vector//
				}
			}
		}
		//checking if the src is to the left, up, and diagnolly to the dst
		else if (dstPosition[START_POSITION_LETTER] < dstPosition[DST_POSITION_LETTER] && dstPosition[START_POSITION_NUMBER] > dstPosition[DST_POSITION_NUMBER])
		{
			//getting the letter difference//
			lettersDif = static_cast<int>(dstPosition[DST_POSITION_LETTER] - dstPosition[START_POSITION_LETTER]);
			//getting the number difference//
			numsDiff = dstPosition[START_POSITION_NUMBER] - dstPosition[DST_POSITION_NUMBER];
			//if the difference is equal, its rigth movement for diagnolly//
			if (lettersDif == numsDiff)
			{
				//getting all squares from src to dst//
				while (currSquare[START_POSITION_LETTER] < dstPosition[DST_POSITION_LETTER] && currSquare[START_POSITION_NUMBER] > dstPosition[DST_POSITION_NUMBER])
				{
					currSquare[START_POSITION_LETTER] += 1;
					currSquare[START_POSITION_NUMBER] -= 1;
					this->_way.push_back(currSquare);   //adding to the vector//
				}
			}
		}
	}
	return this->_way;
}
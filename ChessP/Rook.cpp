#include "Rook.h"
Rook::Rook(const std::string& position, const char type) : Piece(type, position)
{
}
Rook::~Rook()
{
	this->_way.clear();  
}

std::vector<std::string> Rook::possibleMoves(const std::string& dstPosition) 
{
	this->_way.clear();
	//getting the first square of the way//
	std::string currSquare = std::string(1, dstPosition[START_POSITION_LETTER]) + dstPosition[START_POSITION_NUMBER];

	//checking if the dst point is in the same row//
	if (dstPosition[START_POSITION_LETTER] == dstPosition[DST_POSITION_LETTER])
	{
		//checking if the src square is below the dst square//
		if (dstPosition[START_POSITION_NUMBER] < dstPosition[DST_POSITION_NUMBER])
		{
			//getting all squares from the src square to the dst square included//
			while (currSquare[START_POSITION_NUMBER] < dstPosition[DST_POSITION_NUMBER])
			{
				currSquare[START_POSITION_NUMBER] += 1;  //increasing the number to get the next square//
				this->_way.push_back(currSquare);   //adding square to the way vector//
			}
		}
		//checking if the src square is abouv the dst square//
		else if (dstPosition[START_POSITION_NUMBER] > dstPosition[DST_POSITION_NUMBER])
		{
			//getting all squares from the src square to the dst square included//
			while (currSquare[START_POSITION_NUMBER] > dstPosition[DST_POSITION_NUMBER])
			{
				currSquare[START_POSITION_NUMBER] -= 1;  //decreasing the number to get to the next square//
				this->_way.push_back(currSquare);   //adding square to the way vector//
			}
		}
	}
	//checking if the dst square is in the same col//
	else if (dstPosition[START_POSITION_NUMBER] == dstPosition[DST_POSITION_NUMBER])
	{
		//checking if src square is to the left of dst square//
		if (dstPosition[START_POSITION_LETTER] < dstPosition[DST_POSITION_LETTER])
		{
			//getting all squares from the src square to the dst square included//
			while (currSquare[START_POSITION_LETTER] < dstPosition[DST_POSITION_LETTER])
			{
				currSquare[START_POSITION_LETTER] += 1;  //increasing the letter to get to the next square//
				this->_way.push_back(currSquare);   //adding square to the way vector//
			}
		}
		//checking if src square is to the rigth of dst square//
		else if (dstPosition[START_POSITION_LETTER] > dstPosition[DST_POSITION_LETTER])
		{
			//getting all squares from the src square to the dst square included//
			while (currSquare[START_POSITION_LETTER] > dstPosition[DST_POSITION_LETTER])
			{
				currSquare[START_POSITION_LETTER] -= 1;   //decreasing the letter to get to the next square//
				this->_way.push_back(currSquare);   //adding square to the way vector//
			}
		}
	}
	return this->_way;  //returning all squares from src to dst, empty if invalid movement for the piece//
}

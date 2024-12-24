#include "King.h"
//constractur//
King::King(const std::string& position, const char type) : Piece(type, position)
{
}
//distractor//
King::~King()
{
	this->_way.clear();
}

//func that returns the way to the dst square in a vetor//
std::vector<std::string> King::possibleMoves(const std::string& dstPosition)
{
	this->_way.clear();
	//getting the src square//
	std::string currSquare = std::string(1, dstPosition[START_POSITION_LETTER]) + dstPosition[START_POSITION_NUMBER];
	//checking if the movement is in the same row//
	if (currSquare[START_POSITION_LETTER] == dstPosition[DST_POSITION_LETTER])
	{
		//if the movement is 1 square up//
		if (currSquare[START_POSITION_NUMBER] + 1 == dstPosition[DST_POSITION_NUMBER])
		{
			currSquare[START_POSITION_NUMBER] += 1;  //getting the up square//
			this->_way.push_back(currSquare);   //adding to the vector//
		}
		//if the movement is 1 square down//
		else if (currSquare[START_POSITION_NUMBER] - 1 == dstPosition[DST_POSITION_NUMBER])
		{
			currSquare[START_POSITION_NUMBER] -= 1;   //getting the square
			this->_way.push_back(currSquare);  //adding to vector//
		}
	}
	//if the movement is in the same col//
	else if (currSquare[START_POSITION_NUMBER] == dstPosition[DST_POSITION_NUMBER])
	{
		//if the dst is 1 to the left// 
		if (currSquare[START_POSITION_LETTER] + 1 == dstPosition[DST_POSITION_LETTER])
		{
			currSquare[START_POSITION_LETTER] += 1;  //getting to the dst square//
			this->_way.push_back(currSquare);  //adding to the vector//
		}
		//if the dst is 1 to the rigth//
		else if (currSquare[START_POSITION_LETTER] - 1 == dstPosition[DST_POSITION_LETTER])
		{
			currSquare[START_POSITION_LETTER] -= 1;   //getting to the dst square//
			this->_way.push_back(currSquare); //adding to the vector//
		}
	}
	//if dst square is up, rigth, and diagnolly 
	else if ((currSquare[START_POSITION_LETTER] + 1 == dstPosition[DST_POSITION_LETTER]) &&
		(currSquare[START_POSITION_NUMBER] + 1 == dstPosition[DST_POSITION_NUMBER]))
	{
		//getting the square//
		currSquare[START_POSITION_LETTER] += 1;
		currSquare[START_POSITION_NUMBER] += 1;
		this->_way.push_back(currSquare);   //adding to the vector//
	}
	//if dst square is down, rigth, and diagnolly 
	else if ((currSquare[START_POSITION_LETTER] + 1 == dstPosition[DST_POSITION_LETTER]) &&
		(currSquare[START_POSITION_NUMBER] - 1 == dstPosition[DST_POSITION_NUMBER]))
	{
		//getting the square//
		currSquare[START_POSITION_LETTER] += 1;
		currSquare[START_POSITION_NUMBER] -= 1;
		//adding to the vector//
		this->_way.push_back(currSquare);
	}
	//if dst square is up, left, and diagnolly 
	else if ((currSquare[START_POSITION_LETTER] - 1 == dstPosition[DST_POSITION_LETTER]) &&
		(currSquare[START_POSITION_NUMBER] + 1 == dstPosition[DST_POSITION_NUMBER]))
	{
		//getting the square//
		currSquare[START_POSITION_LETTER] -= 1;
		currSquare[START_POSITION_NUMBER] += 1;
		this->_way.push_back(currSquare);   //adding to the vector//
	}
	//if dst square is down, left, and diagnolly 
	else if ((currSquare[START_POSITION_LETTER] - 1 == dstPosition[DST_POSITION_LETTER]) &&
		(currSquare[START_POSITION_NUMBER] - 1 == dstPosition[DST_POSITION_NUMBER]))
	{
		//getting the square//
		currSquare[START_POSITION_LETTER] -= 1;
		currSquare[START_POSITION_NUMBER] -= 1;
		this->_way.push_back(currSquare);   //adding to the vector//
	}
	return this->_way;   //returning the vector with the way//
}

#include "Pawn.h"
//constractor//
Pawn::Pawn(const std::string& position, const char type) : Piece(type, position)
{
}
//distractor//
Pawn::~Pawn()
{
	this->_way.clear();
}
//func that returns the way from src to dst in vector//
std::vector<std::string> Pawn::possibleMoves(const std::string& dstPosition)
{
	this->_way.clear();
	//getting the src square//
	std::string currSquare = std::string(1, dstPosition[START_POSITION_LETTER]) + dstPosition[START_POSITION_NUMBER];
	//calling func that checks if the piece is moving diagnolly to the left, for white player//
	if (isDiagnollyLeftW(dstPosition))
	{
		//getting the dst square//
		currSquare[START_POSITION_LETTER] -= 1;
		currSquare[START_POSITION_NUMBER] += 1;
		this->_way.push_back(currSquare);
	}
	//calling func that checks if the piece is moving diagnolly to the right, for white player//
	else if (isDiagnollyRightW(dstPosition))
	{
		//getting the dst square//
		currSquare[START_POSITION_LETTER] += 1;
		currSquare[START_POSITION_NUMBER] += 1;
		this->_way.push_back(currSquare);
	}
	//calling func that checks if the piece is moving diagnolly to the right, for black player//
	else if (isDiagnollyRightB(dstPosition))
	{
		//getting the dst square//
		currSquare[START_POSITION_LETTER] += 1;
		currSquare[START_POSITION_NUMBER] -= 1;
		this->_way.push_back(currSquare);
	}
	//calling func that checks if the piece is moving diagnolly to the left, for white player//
	else if (isDiagnollyLeftB(dstPosition))
	{
		//getting the dst square//
		currSquare[START_POSITION_LETTER] -= 1;
		currSquare[START_POSITION_NUMBER] -= 1;
		this->_way.push_back(currSquare);
	}
	//checking if the dst square is 1 square above the dst, for white//
	else if(dstPosition[START_POSITION_LETTER] == dstPosition[DST_POSITION_LETTER] &&
		dstPosition[START_POSITION_NUMBER] + 1 == dstPosition[DST_POSITION_NUMBER])
	{
		//getting the dst square//
		currSquare[START_POSITION_NUMBER] += 1;
		this->_way.push_back(currSquare);
	}
	//checking if the dst square is 1 square above the dst, for black//
	else if (dstPosition[START_POSITION_LETTER] == dstPosition[DST_POSITION_LETTER] &&
		dstPosition[START_POSITION_NUMBER] - 1 == dstPosition[DST_POSITION_NUMBER])
	{
		//getting the dst square//
		currSquare[START_POSITION_NUMBER] -= 1;
		this->_way.push_back(currSquare);
	}
	//checking if the dst square is 2 squares above the src square, for white//
	else if (dstPosition[START_POSITION_LETTER] == dstPosition[DST_POSITION_LETTER] &&
		dstPosition[START_POSITION_NUMBER] + 2 == dstPosition[DST_POSITION_NUMBER])
	{
		//getting the 2 squares of the way to the dst//
		currSquare[START_POSITION_NUMBER] += 1;
		this->_way.push_back(currSquare);
		currSquare[START_POSITION_NUMBER] += 1;
		this->_way.push_back(currSquare);
	}
	//checking if the dst square is 2 squares above the src square, for black//
	else if (dstPosition[START_POSITION_LETTER] == dstPosition[DST_POSITION_LETTER] &&
		dstPosition[START_POSITION_NUMBER] - 2 == dstPosition[DST_POSITION_NUMBER])
	{
		//getting the 2 squares of the way to the dst//
		currSquare[START_POSITION_NUMBER] -= 1;
		this->_way.push_back(currSquare);
		currSquare[START_POSITION_NUMBER] -= 1;
		this->_way.push_back(currSquare);
	}
	return this->_way;
}

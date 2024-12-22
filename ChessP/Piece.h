#pragma once
#include <iostream>
#include <string>
#include <vector>
#define START_POSITION_LETTER 0
#define START_POSITION_NUMBER 1
#define DST_POSITION_LETTER 2
#define DST_POSITION_NUMBER 3
class Piece
{
public:
	Piece(const char type, const std::string& position); 	//constractor//
	virtual ~Piece();    //distractor//
	/*
	this function returns the type
	*/
	char getType() const;
	void setPosition(const std::string& position);   //setter of position//
	std::string getPositon() const;   //getter of cosition//
	/*
	pure virtual function - returns the possible way to dst, points of the way in a vector.
	*/
	virtual std::vector<std::string> possibleMoves(const std::string& dstPosition) = 0;
private:
	std::string _position;
	char _type;
};
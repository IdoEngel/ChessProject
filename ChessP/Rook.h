#pragma once
#include "Piece.h"

class Rook : Piece
{
public:
	Rook(const std::string& position, const char type);  //constractor//
	~Rook();   //distractor//
	void setPosition(const std::string& position);  //setter  of the position//
	std::string getPositon() const;   //getter of the position//
	/*
	 returns the possible way to dst, points of the way in a vector.
	*/
	virtual std::vector<std::string> possibleMoves(const std::string& dstPosition) override;
private:
	std::string _position;
	std::vector < std::string> _way;
};
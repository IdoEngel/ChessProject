#pragma once
#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(const std::string& position, const char type);   //constractor//
	~Knight();   //distractor//
	/*
	 returns the possible way to dst, points of the way in a vector.
	*/
	virtual std::vector<std::string> possibleMoves(const std::string& dstPosition) override;
private:
	std::vector < std::string> _way;
};

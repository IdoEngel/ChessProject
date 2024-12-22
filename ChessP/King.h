#pragma once
#include "Piece.h"
class King : public Piece
{
public:
	King(const std::string& position, const char type);   //constractor//
	~King();   //distractor//
	/*
	 returns the possible way to dst, points of the way in a vector.
	*/
	virtual std::vector<std::string> possibleMoves(const std::string& dstPosition) override;
private:
	std::vector < std::string> _way;
};

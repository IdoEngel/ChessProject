#pragma once
#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(const std::string& position, const char type);   //constractor//
	~Pawn();   //distractor//
	/*
	 returns the possible way to dst, points of the way in a vector.
	*/
	virtual std::vector<std::string> possibleMoves(const std::string& dstPosition) override;
private:
	std::vector < std::string> _way;
};


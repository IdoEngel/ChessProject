#pragma once
#include "Piece.h"

class Pown : public Piece
{
public:
	Pown(const std::string& position, const char type);   //constractor//
	~Pown();   //distractor//
	/*
	 returns the possible way to dst, points of the way in a vector.
	*/
	virtual std::vector<std::string> possibleMoves(const std::string& dstPosition) override;
private:
	std::vector < std::string> _way;
};


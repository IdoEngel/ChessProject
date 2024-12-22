#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(const std::string& position, const char type); //constractor//
	~Bishop();   //distractor//
	/*
	 returns the possible way to dst, points of the way in a vector.
	*/
	virtual std::vector<std::string> possibleMoves(const std::string& dstPosition) override;
private:
	std::vector < std::string> _way;
};

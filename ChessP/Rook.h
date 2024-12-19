#pragma once
#include "Piece.h"
class Rook : Piece
{
public:
	Rook(const std::string& position, const char type);  //constractor//
	~Rook();   //distractor//
	void setPosition(const std::string& position) const;  //setter  of the position//
	std::string getPositon() const;   //getter of the position//
	/*
	returns if the dst position is valid for the rook movement.
	boolian value.
	*/
	bool possibleMoves(const std::string& dstPosition) const override;
private:
	std::string _position;
};
#pragma once
#include "Piece.h"
class King : Piece
{
public:
	King(const std::string& position, const char type);   //constractor//
	~King();   //distractor//
	void setPosition(const std::string& position) const;   //setter of position//
	std::string getPositon() const;   //getter of cosition//
	/*
	returns if the dst position is valid for the king movement.
	boolian value.
	*/
	bool possibleMoves(const std::string& dstPosition) const override;
private:
	std::string _position;
};

#pragma once
#include "Piece.h"
class Rook : public Piece
{
public:
	Rook(const std::string& position, const char type);  //constractor//
	virtual ~Rook();   //distractor//
	void setPosition(const std::string& position) const;  //setter  of the position//
	std::string getPositon() const;   //getter of the position//
	/*
	returns if the dst position is valid for the bishop movement.
	boolian value.
	*/
	virtual std::string* possibleMoves(const std::string& dstPosition) const override;
private:
	std::string _position;
};
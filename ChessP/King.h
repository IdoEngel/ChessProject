#pragma once
#include "Piece.h"
class King : public Piece
{
public:
	King(const std::string& position, const char type);   //constractor//
	virtual ~King();   //distractor//
	void setPosition(const std::string& position) const;   //setter of position//
	std::string getPositon() const;   //getter of cosition//
	/*
	returns if the dst position is valid for the bishop movement.
	boolian value.
	*/
	virtual std::string* possibleMoves(const std::string& dstPosition) const override;
private:
	std::string _position;
};

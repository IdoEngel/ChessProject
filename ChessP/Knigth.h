#pragma once
#include "Piece.h"
class Knigth : Piece
{
public:
	Knigth(const std::string& position, const char type);   //constractor//
	~Knigth();   //distractor//
	void setPosition(const std::string& position) const;    //setter of positions//
	std::string getPositon() const;   //getter of position//
	/*
	returns if the dst position is valid for the knigth movement.
	boolian value.
	*/
	bool possibleMoves(const std::string& dstPosition) const override;
private:
	std::string _position;
};

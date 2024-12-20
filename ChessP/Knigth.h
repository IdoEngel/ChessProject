#pragma once
#include "Piece.h"

class Knigth : public Piece
{
public:
	Knigth(const std::string& position, const char type);   //constractor//
	virtual ~Knigth();   //distractor//
	void setPosition(const std::string& position) const;    //setter of positions//
	std::string getPositon() const;   //getter of position//

	/*
	returns if the dst position is valid for the bishop movement.
	boolian value.
	*/
	virtual std::string* possibleMoves(const std::string& dstPosition) const override;
private:
	std::string _position;
};

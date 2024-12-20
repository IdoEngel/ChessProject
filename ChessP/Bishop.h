#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(const std::string& position, const char type); //constractor//
	virtual ~Bishop();   //distractor//
	void setPosition(const std::string& position) const;   //setter of position//
	std::string getPositon() const;   //getter of position//
	/*
	returns if the dst position is valid for the bishop movement.
	boolian value.
	*/
	virtual std::string* possibleMoves(const std::string& dstPosition) const override;
private:
	std::string _position;
};

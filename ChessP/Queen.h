#pragma once
#include "Piece.h"
class Queen : Piece
{
public:
	Queen(const std::string& position, const char type);   //constractor//
	~Queen();  //distractor//
	void setPosition(const std::string& position) const;   //setter of position//
	std::string getPositon() const;   //getter of position//
	/*
	returns if the dst position is valid for the queen movement.
	boolian value.
	*/
	bool possibleMoves(const std::string& dstPosition) const override;
private:
	std::string _position;
};


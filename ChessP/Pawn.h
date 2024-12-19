#pragma once
#include "Piece.h"
class Pown : Piece
{
public:
	Pown(const std::string& position, const char type);   //constractor//
	~Pown();   //distractor//
	void setPosition(const std::string& position) const;   //setter of position//
	std::string getPositon() const;   //getter of position//
	/*
	returns if the dst position is valid for the pown movement.
	boolian value.
	*/
	bool possibleMoves(const std::string& dstPosition) const override;
private:
	std::string _position;
};


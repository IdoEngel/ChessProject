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
	returns if the dst position is valid for the bishop movement.
	boolian value.
	*/
	bool isPossibleMove(const std::string& dstPosition, const Board& board) const override;
private:
	std::string _position;
};


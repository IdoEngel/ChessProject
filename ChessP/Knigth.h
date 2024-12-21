#pragma once
#include "Piece.h"

class Knigth : public Piece
{
public:
	Knigth(const std::string& position, const char type);   //constractor//
	~Knigth();   //distractor//
	void setPosition(const std::string& position);    //setter of positions//
	std::string getPositon() const;   //getter of position//
	/*
	 returns the possible way to dst, points of the way in a vector.
	*/
	virtual std::vector<std::string> possibleMoves(const std::string& dstPosition) override;
private:
	std::string _position;
	std::vector < std::string> _way;
};

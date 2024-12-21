#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(const std::string& position, const char type); //constractor//
	virtual ~Bishop();   //distractor//
	void setPosition(const std::string& position);   //setter of position//
	std::string getPositon() const;   //getter of position//
	/*
	 returns the possible way to dst, points of the way in a vector.
	*/
	virtual std::vector<std::string> possibleMoves(const std::string& dstPosition) override;
private:
	std::string _position;
	std::vector < std::string> _way;
};

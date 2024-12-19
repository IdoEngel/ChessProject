#include <iostream>
#include <string>
class Piece 
{
public:
	Piece(const char type); 	//constractor//
	virtual ~Piece();    //distractor//
	/*
	this function returns the type
	*/
	char getType() const;
	/*
	pure virtual function - returns if the dst position is valid, based on the moves
	that allowed for each piece.
	*/
	virtual bool possibleMoves(const std::string& dstPosition) const = 0;
private:
	char _type;
};
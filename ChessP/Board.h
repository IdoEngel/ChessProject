#pragma once

#include <string>
#include <exception>

class Board : std::exception {
public:

	/*Constractor - creates an instance of the class with the board peices in the defualt position
	input: bool - forException (if instace created for excption no need to create all the peices, just the function 'what'.
		Default value if 'false' - creating the peaces)
	output: none*/
	Board(const bool forException = false);

	/*Copy constractor for return types in functions*/
	Board(const Board& other);

	//Distractor
	~Board();

	/*Movrs the peice to the coordinate loction and return true, if its valid - if not - do noting and return false
	input: string - coordinate (coordinate with src and dst)
	output: is the move occured?*/
	bool movePeice(const std::string& coordinate) noexcept;

	/*Check if the src position the and dst position of the 'coordinate' is valid 
		if not valid retrun the error - if valid RAISE an excpion (typed Board)
	input: string - coordinate (coordinate with src and dst)
	output: the error code if occured*/
	std::string isPositionValid(const std::string& coordinate);

	/*RAISE if the 'isPositionValid' not found an error
	input: none
	output: msg error - "No error codes found"*/
	const char* what() const noexcept override;

private:
	Piece* _pieces;
};

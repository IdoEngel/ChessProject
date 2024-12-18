#pragma once

#define WHITE 'w'
#define BLACK 'b'

class Player {
public:

	/*Constractor - creates in instance of the class
	No input or output*/
	Player();

	//Distractor
	~Player();

	/*Checks if the player won in the game in the current time
	input: Board - brd (the board to check if the player won
	output: Am I won? (true if won) (bool typed)*/
	bool amIWon(const Board& brd) noexcept;

private:
	const char _color;
};
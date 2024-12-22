#pragma once

#define WHITE 'W'
#define BLACK 'b'
#define NONE ' ';

class Player {
public:

	/*Constractor - creates in instance of the class
	No input or output*/
	Player(const char color);

	//Constactor - default
	Player();

	/*Get the color of the player*/
	char getColor() const noexcept;

	bool isValidPlayer() const noexcept;

private:
	char _color;
	bool _haveError;
};
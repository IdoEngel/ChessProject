#include <iostream>
#include  <string.h>
#include "Game.h"
void main()
{
	std::string coords;
	Game g;
	bool isValid = true;
	int errorCode =0;
	std::string toExit;
	do
	{
		std::cout << "Enter the coordinates of the source square and the destination square:" << std::endl;
		//getting the coords from the user//
		std::cin >> coords;
		//trying to make a move with the coords//
		errorCode = std::stoi(g.play(coords));
		switch (errorCode)   //checking what is the return value
		{
		case 0:   //for valid move//
			std::cout << g << std::endl;
			break;
		case 1:   //valid move, player made check on opponent//
			std::cout << "Check on opponent!" << std::endl;
			std::cout << g << std::endl;
			break;
		case 2:   //error code 2 - src square doesnt have a piece for curr player//
			std::cout << "Error! no curr player piece in src square!" << std::endl;
			std::cout << g << std::endl;
			break;
		case 3:  //error code 3 - theres a piece of the curr palyer in the dst square//
			std::cout << "Error! curr player piece in dst square!" << std::endl;
			std::cout << g << std::endl;
			break;
		case 4:   //error code 4 - movement coused a check on curr player//
			std::cout << "Error! Check on yourself!" << std::endl;
			std::cout << g << std::endl;
			break;
		case 5:   //error code 5 - invalid indexes of movement//
			std::cout << "Error! invalid indexes for squares!" << std::endl;
			std::cout << g << std::endl;
			break;
		case 6:   //error code 6 - invalid movement of the chosen piece//
			std::cout << "Error! Invalid movement of curr piece!" << std::endl;
			std::cout << g << std::endl;
			break;
		case 7:  //error code 7 - same src and dst squares//
			std::cout << "Error! src square and dst square are equal!" << std::endl;
			std::cout << g << std::endl;
			break;
		case 8:  //valid movement, paleyer won the game//
			std::cout << "Checkmate!" << std::endl;
			std::cout << g << std::endl;
		}
		std::cout << "Do you want to exit the game? enter 0 to continue, any other key to exit" << std::endl;
		//checking if user want to play another move//
		std::cin >> toExit;
	} while (toExit == "0");
}
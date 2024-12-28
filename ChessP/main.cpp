#include <iostream>
#include  <string.h>
#include "Game.h"
#include "Exceptions.h"

#define PLAYING_ON_CONSOLE false
#define PLAYING_ON_GRAPHICS true

int main()
{
	Game* g = nullptr;
	std::string coords;
	std::string isGraphic;

	try {
		std::cout << "Do you want to run on Graphic or on Console? Enter 0 for Graphic, other key for console" << std::endl;
		std::cin >> isGraphic;
		if (isGraphic == "0")
		{
			g = new Game(PLAYING_ON_GRAPHICS);
		}
		else
		{
			g = new Game(PLAYING_ON_CONSOLE);
		}
	}
	catch (const ChessExceptions::PipeException& e) {
		std::cout << e.what();
		std::exit(0);
	}
	
	try {
		while (true) {
			std::cout << g->play() << std::endl;
			std::cout << *g;
		}
	}
	catch (const ChessExceptions::GameExcption& e) {
		std::cout << "Chackmate!!" << std::endl;
	}

	delete g;

	return 0;
}
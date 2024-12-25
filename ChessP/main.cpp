#include <iostream>
#include  <string.h>
#include "Game.h"
#include "PipeException.h"

#define PLAYING_ON_CONSOLE false
#define PLAYING_ON_GRAPHICS true

void main()
{
	Game* g = nullptr;
	std::string coords;

	try {
		 g = new Game(PLAYING_ON_GRAPHICS);
	}
	catch (const PipeException& e) {
		std::cout << e.what();
		std::exit(0);
	}
	
	try {
		while (true) {
			std::cout << g->play() << std::endl;
			std::cout << *g;
		}
	}
	catch (const Game& e) {
		std::cout << "Chackmate!!" << std::endl;
	}

	delete g;
}
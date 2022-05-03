#include <iostream>
#include "header.h"

using namespace sf;

int main()
{
	// Init Game engine
	Game game;

	// Game Loop
	while (game.running())
	{

		// Update
		game.update();


		// Render
		game.render();

	}

	// End of Application
	return 0;
}
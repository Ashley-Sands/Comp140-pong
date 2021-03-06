// 20180208SerialSDL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SDL.h"
#include "Game.h"

Game* game = 0;

//Time
int lastUpdateTick = 0;
int deltaTime = 0;			// time in ticks

int main(int argc, char* argv[])
{
	// new game instance
	game = new Game();

	// initialise the game
	game->init("SDL Serial", 100, 100, 860, 480, 0);

	lastUpdateTick = SDL_GetTicks();

	// create a game loop
	while (game->running()) {

		// choose a framerate - in this case we are using 1000%40 which means 
		// 25 frames per second (quite slow)
		int increment = SDL_GetTicks() % 8;

		// if modulo returns 0 trigger one frame in our game
		if (increment == 0) {

			deltaTime = SDL_GetTicks() - lastUpdateTick;
			lastUpdateTick = SDL_GetTicks();

			game->handleEvents(deltaTime);
			game->update( deltaTime );
			game->render();

		}
	}

	// when the game ends clean SDL and Serial
	game->clean();

    return 0;
}


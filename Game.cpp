#include "stdafx.h"
#include "Game.h"
#include <iostream>

using std::cout;

/*
* Constructor - not used in this case
*
*/
Game::Game()
{
	
}

/*
	Decontructor - also not used in this case
*/
Game::~Game()
{
}

bool Game::initSerialConnection()
{

	serial = new SerialInterface();

	return true;
}
/*
* init - used to initialise and setup SDL
* Return true if everything is successful
*/
bool Game::init(const char * title, int xpos, int ypos, int width, int height, int flags)
{
	// initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		cout << "SDL init success \n";

		// Create a window
		mainWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		// if window succesful..
		if (mainWindow != 0) {
			cout << "Window creation success \n";

			// create renderer
			mainRenderer = SDL_CreateRenderer(mainWindow, -1, 0);

			// if renderer successful...
			if (mainRenderer != 0) {
				cout << "Renderer creation success \n";
				SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
			}
			else {
				cout << "renderer failed \n";
				return false;
			}
		}
		else {
			cout << "window failed \n";
			return false;
		}

	}
	else {
		cout << "SDL fail \n";
		return false;
	}

	isRunning = true;
	cout << "SDL init success \n";

	initSerialConnection();
	cout << "SDL init success \n";

	//Set the player one and two start position.
	playerOnePosition.x = 50;
	playerOnePosition.y = 100;
	playerOnePosition.w = 25;
	playerOnePosition.h = 75;

	playerTwoPosition.x = 540;
	playerTwoPosition.y = 540;
	playerTwoPosition.w = 25;
	playerTwoPosition.h = 75;

	return true;
}

void Game::render()
{
	// set background color
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);
	
	// clear previous frame
	SDL_RenderClear(mainRenderer);

	// draw to the screen here!
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(mainRenderer,&playerOnePosition);
	SDL_RenderFillRect(mainRenderer,&playerTwoPosition);
	
	// render new frame
	SDL_RenderPresent(mainRenderer);
}

/*
* update - Process all variables !in charge of anything to do with rendering
*
*/
void Game::update()
{
	
}
/*
* handleEvents - Controler Events for the controler.
*/
void Game::HandleControlerEvents()
{
	if(!serial->connect)
	serial->getPositions();
	playerOnePosition.y = (serial->getPot1() / 1023.0f) * 405;
	playerTwoPosition.y = (serial->getPot2() / 1023.0f) * 405;

}

void Game::HandleKeyboardEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		case SDL_KEYDOWN:
			//Player onw inputs.
			if (event.key.keysym.sym == SDLK_w)
			{
				playerOnePosition.y -= 5.0f;
			}
			else if (event.key.keysym.sym == SDLK_s)
			{
				playerOnePosition.y += 5.0f;
			}
			
			//Player two inputs.
			if (event.key.keysym.sym == SDLK_UP)
			{
				playerTwoPosition.y -= 5.0f;
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				playerTwoPosition.y += 5.0f;
			}

			//Spwan Ball if on is not present.
			//if(event.key.keysym.sym == SDLK_SPACE)
				//Do ball things!!

			break;
		default:
			break;
		}

	}
}

/*
* handleEvents - Poll Events and uses switch case to process specific events
*/
void Game::handleEvents()
{
	// use controler inputs if avable.
	if (serial->connect)
		HandleControlerEvents();
	else
		HandleKeyboardEvents();

	// Clamp the paddle position.
	playerOnePosition.y = ClampPaddlePosition(playerOnePosition.y);
	playerTwoPosition.y = ClampPaddlePosition(playerTwoPosition.y);

}
/*
* 
*/
float Game::ClampPaddlePosition(float yPosition)
{
	if (yPosition < 0) yPosition = 0;
	else if (yPosition > 405) yPosition = 405;

	return yPosition;
}
/*
* clean - Clean up SDL and close the port
*/
void Game::clean()
{	
	cout << "Cleaning SDL \n";
	SDL_DestroyWindow(mainWindow);
	SDL_DestroyRenderer(mainRenderer);
	SDL_Quit();
}



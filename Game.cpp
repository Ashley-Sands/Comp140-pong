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
	playerOnePaddle = new Transform("p_one");
	playerTwoPaddle = new Transform("p_two");
	pongBall = new ball("ball");
}

/*
	Decontructor - also not used in this case
*/
Game::~Game()
{
	delete playerOnePaddle;
	delete playerTwoPaddle;
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

	//Set the player one and two start.
	playerOnePaddle->SetRect(Vector2(50, 100), Vector2(25, 75));
	playerOnePaddle->SetColor(255, 255, 255, 255);

	playerTwoPaddle->SetRect(Vector2(540, 100), Vector2(25, 75));
	playerTwoPaddle->SetColor(255, 255, 255, 255);

	pongBall->SetRect( Vector2(250, 150), Vector2(20, 20) );
	pongBall->SetColor(255, 255, 0, 255);


	return true;
}

void Game::render()
{
	// set background color
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);
	
	// clear previous frame
	SDL_RenderClear(mainRenderer);

	// draw player one and two to screen
	playerOnePaddle->Render(mainRenderer);
	playerTwoPaddle->Render(mainRenderer);
	pongBall->Render(mainRenderer);

	// render new frame
	SDL_RenderPresent(mainRenderer);
}

/*
* update - Process all variables !in charge of anything to do with rendering
*
*/
void Game::update(int deltaTime)
{
	pongBall->Update(deltaTime);
	pongBall->OnCollision(playerOnePaddle);
	pongBall->OnCollision(playerTwoPaddle);
}
/*
* handleEvents - Controler Events for the controler.
*/
void Game::HandleControlerEvents()
{

	serial->getPositions();

	// Get and set player one and two positions
	float playerOnePos = (serial->getPot1() / 1023.0f) * 405.0f;
	float playerTwoPos = (serial->getPot1() / 1023.0f) * 405.0f;

	playerOnePaddle->SetPosition( Vector2(0, playerOnePos ) );
	playerOnePaddle->SetPosition( Vector2(0, playerTwoPos ) );

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
				playerOnePaddle->MoveTransform( 0, -paddleMoveSpeed );
			else if (event.key.keysym.sym == SDLK_s)
				playerOnePaddle->MoveTransform( 0, paddleMoveSpeed );
			
			//Player two inputs.
			if (event.key.keysym.sym == SDLK_UP)
				playerTwoPaddle->MoveTransform(0, -paddleMoveSpeed);
			else if (event.key.keysym.sym == SDLK_DOWN)
				playerTwoPaddle->MoveTransform(0, paddleMoveSpeed);


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
	if (serial->connect && !ignoreSerial)
		HandleControlerEvents();
	else
		HandleKeyboardEvents();

	// Clamp the paddle position.
	float p1_clampedY = ClampPaddlePosition(playerOnePaddle->GetPosition().y, 0, 405);
	float p2_clampedY = ClampPaddlePosition(playerTwoPaddle->GetPosition().y, 0, 405);

	playerOnePaddle->SetPositionY(p1_clampedY);
	playerTwoPaddle->SetPositionY(p2_clampedY);

}

/*
* 
*/
float Game::ClampPaddlePosition(float yPosition, float min, float max)
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



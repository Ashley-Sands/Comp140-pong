#include "stdafx.h"
#include "Game.h"
#include "SDL_ttf.h"
#include <string>
#include <iostream>
#include <windows.h>

using std::cout;

/*
* Constructor - not used in this case
*
*/
Game::Game()
{
	topBounds = new Transform("top_bounds");
	bottomBounds = new Transform("bottom_bounds");

	playerOnePaddle = new Transform("p_one");
	playerTwoPaddle = new Transform("p_two");
	pongBall = new ball("ball");

	scoreText = new Text_Transform();

}

/*
	Decontructor - also not used in this case
*/
Game::~Game()
{
	delete playerOnePaddle, playerTwoPaddle;
	delete topBounds, bottomBounds;
	delete pongBall;
}

bool Game::initSerialConnection()
{

	if (forceComPort < 0)
		serial = new SerialInterface();
	else
		serial = new SerialInterface(forceComPort);


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

		if (TTF_Init() == 0)
		{
			cout << "SDL ttf init success \n";
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
		else
		{
			cout << "SDL ttf fail \n";
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

	serial->send("N");		// reset the controller

	windowSize = new Vector2(width, height);

	// sound top and bottom bounds
	topBounds->SetRect(Vector2(0, -20), Vector2(width, 20));
	topBounds->SetColor(100, 100, 100, 255);

	bottomBounds->SetRect(Vector2(0, height), Vector2(width, 20));
	bottomBounds->SetColor(100, 100, 100, 255);

	//Set the player one and two start.
	playerOnePaddle->SetRect(Vector2(50, 100), Vector2(25, 75));
	playerOnePaddle->SetColor(255, 255, 255, 255);

	playerTwoPaddle->SetRect(Vector2(780, 100), Vector2(25, 75));
	playerTwoPaddle->SetColor(255, 255, 255, 255);

	ResetBall();
	pongBall->SetColor(255, 255, 0, 255);

	scoreText->SetColor(255, 255, 255, 255);
	scoreText->SetRect(Vector2((windowSize->x / 2) - 75, 5), Vector2(150, 50));
	scoreText->SetText("::  0 - 0 ::");

	return true;
}

void Game::render()
{
	// set background color
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);
	
	// clear previous frame
	SDL_RenderClear(mainRenderer);

	// draw bounds
	topBounds->Render(mainRenderer);
	bottomBounds->Render(mainRenderer);

	// draw player one and two to screen
	playerOnePaddle->Render(mainRenderer);
	playerTwoPaddle->Render(mainRenderer);
	pongBall->Render(mainRenderer);

	scoreText->Render(mainRenderer);

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
	
	// top / bottom collision
	pongBall->OnCollision(topBounds);
	pongBall->OnCollision(bottomBounds);

	// paddle collision and send message to flash hit LED
	if (pongBall->OnCollision(playerOnePaddle))
		serial->send("H");

	if (pongBall->OnCollision(playerTwoPaddle))
		serial->send("J");

	//Check if the ball is in X bounds!
	BallIsInBounds();
	
}
/*
* handleEvents - Controler Events for the controler.
*/
void Game::HandleControlerEvents()
{

	serial->getPositions();

	// Get and set player one and two positions
	float playerOnePos = (serial->getPot1() / 1023.0f) * 405.0f;
	float playerTwoPos = (serial->getPot2() / 1023.0f) * 405.0f;

	playerOnePaddle->SetPosition( Vector2(50, playerOnePos ) );
	playerTwoPaddle->SetPosition( Vector2(780, playerTwoPos ) );

}

void Game::HandleKeyboardEvents(int deltaTime)
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
			if (GetAsyncKeyState('W')) //(event.key.keysym.sym == SDLK_w)
				playerOnePaddle->MoveTransform( 0, -paddleMoveSpeed , deltaTime);
			else if (GetAsyncKeyState('S')) //event.key.keysym.sym == SDLK_s)
				playerOnePaddle->MoveTransform( 0, paddleMoveSpeed, deltaTime);
			
			//Player two inputs.
			if (GetAsyncKeyState(VK_UP) ) //event.key.keysym.sym == SDLK_UP)
				playerTwoPaddle->MoveTransform(0, -paddleMoveSpeed, deltaTime);
			else if (GetAsyncKeyState(VK_DOWN) ) //(event.key.keysym.sym == SDLK_DOWN)
				playerTwoPaddle->MoveTransform(0, paddleMoveSpeed, deltaTime);


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
void Game::handleEvents(int deltaTime)
{
	// use controler inputs if avable.
	if (serial->connect && !ignoreSerial)
		HandleControlerEvents();
	else
		HandleKeyboardEvents(deltaTime);

	// Clamp the paddle position.
	float p1_clampedY = ClampPaddlePosition(playerOnePaddle->GetPosition().y, 0, 405);
	float p2_clampedY = ClampPaddlePosition(playerTwoPaddle->GetPosition().y, 0, 405);

	playerOnePaddle->SetPositionY(p1_clampedY);
	playerTwoPaddle->SetPositionY(p2_clampedY);

}

void Game::ResetBall()
{
	pongBall->SetRect(Vector2(((windowSize->x/2) - 10), ((windowSize->y / 2) - 10)), Vector2(20, 20));
}

void Game::BallIsInBounds()
{

	if (pongBall->GetPosition().x < -25)
	{
		ResetBall();
		playerTwoScore++;
		serial->send("L");

	}
	else if (pongBall->GetPosition().x > windowSize->x + 25)
	{
		ResetBall();
		playerOneScore++;
		serial->send("R");

	}

	scoreText->SetText("::  "+ std::to_string(playerOneScore) +" - "+ std::to_string( playerTwoScore ) +" ::");

}
/*
* 
*/
float Game::ClampPaddlePosition(float yPosition, float min, float max)
{
	if (yPosition < 50) yPosition = 50;
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



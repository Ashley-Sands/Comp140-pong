#pragma once
#include "SDL.h"
#include <serial\serial.h>
#include "SerialInterface.h"
#include "Transform.h"
#include "ball.h"
#include "Text_Transform.h"

class Game
{
public:
	Game();
	~Game();

	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void render();
	// Main game update
	// @Param int deltaTime:	Amount of ticks since the last up date.
	void update(int deltaTime);
	void HandleControlerEvents();
	void HandleKeyboardEvents(int deltaTime);
	void handleEvents(int deltaTime);
	
	void ResetBall();
	void BallIsInBounds();

	void clean();

	bool initSerialConnection();
	bool running() { return isRunning; };

	void CheckForWiner();

	void ResetGame();

private:
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	bool isRunning;

	Vector2* windowSize;

	//SDL_Rect playerOnePosition;
	//SDL_Rect playerTwoPosition;

	float paddleMoveSpeed = 250.0f;

	Transform* topBounds;
	Transform* bottomBounds;

	Transform* playerOnePaddle;
	Transform* playerTwoPaddle;
	ball* pongBall;

	Text_Transform* scoreText;
	Text_Transform* gameOverText;

	SerialInterface* serial;

	float ClampPaddlePosition(float yPosition, float min, float max);

	bool ignoreSerial = false;
	int forceComPort = 3;		// set to -1 to use the first port found.

	int playerOneScore = 0;
	int playerTwoScore = 0;

	bool gameOver = false;

};


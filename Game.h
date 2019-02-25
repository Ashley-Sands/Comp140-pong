#pragma once
#include "SDL.h"
#include <serial\serial.h>
#include "SerialInterface.h"
#include "Transform.h"
#include "ball.h"

class Game
{
public:
	Game();
	~Game();

	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void render();
	void update();
	void HandleControlerEvents();
	void HandleKeyboardEvents();
	void handleEvents();
	void clean();

	bool initSerialConnection();
	bool running() { return isRunning; };

private:
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	bool isRunning;

	//SDL_Rect playerOnePosition;
	//SDL_Rect playerTwoPosition;

	float paddleMoveSpeed = 5.0f;

	Transform* playerOnePaddle;
	Transform* playerTwoPaddle;
	ball* pongBall;

	SerialInterface* serial;

	float ClampPaddlePosition(float yPosition, float min, float max);

	bool ignoreSerial = true;

};


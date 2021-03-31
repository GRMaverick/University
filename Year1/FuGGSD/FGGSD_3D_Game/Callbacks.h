#pragma once
#include "Game.h"

class Game;

namespace Callbacks
{
	void Init(Game* game);													// Initialisation Method
	void Display();																// Display Callback
	void Timer(int preferredRefesh);									// Timer Callback
	void Keyboard(unsigned char key, int x, int y);			// Keyboard Callback
	void cameraMenu(int value);										// A menu callback
	void shipMenu(int value);
	void processMenu(int value);
	void KeyboardUp(unsigned char key, int x, int y);
};


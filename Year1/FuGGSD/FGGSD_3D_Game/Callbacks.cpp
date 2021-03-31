#include "Callbacks.h"
#include "Game.h"

namespace Callbacks
{
	namespace
	{
		Game* game = nullptr;
	}
	void Init(Game* gameMain)
	{
		game = gameMain;
	}
	void Display()
	{
		if (game != nullptr)
			game->Draw();
	}
	void Timer(int preferredRefresh)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		game->Update();
		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
		glutTimerFunc(preferredRefresh - updateTime, Callbacks::Timer, preferredRefresh);
	}
	void Keyboard(unsigned char key, int x, int y)
	{
		game->Keyboard(key, x, y);
	}
	void processMenu(int value){
		if (value == 1 || value == 2)
		{
			game->UpdateCamera(value);
		}
		if (value == 3 || value == 4 || value == 5)
		{
			game->UpdateShip(value);
		}
	}
	void KeyboardUp(unsigned char key, int x, int y){
		game->Keyboard(key, x, y);
	}
};


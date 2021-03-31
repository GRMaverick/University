//------------------------------------------------------------------------
//  Author: Paul Roberts 2016
//------------------------------------------------------------------------

#ifndef _GAMESCREEN_CONWAY_H
#define _GAMESCREEN_CONWAY_H

#include "../GameScreen.h"
#include "../Commons.h"
#include <SDL.h>

using namespace::std;

class Texture2D;

class GameScreen_Conway : GameScreen
{
//--------------------------------------------------------------------------------------------------
public:
	GameScreen_Conway(SDL_Renderer* renderer);
	~GameScreen_Conway();

	void Render();
	void Update(size_t deltaTime, SDL_Event e);

//--------------------------------------------------------------------------------------------------
protected:

	//TODO: Students to code these functions.
	void UpdateMap()								;//{;}
	void UpdateMapSecondary();
	void CreateRandomMap(int percentageInactive)	;//{;}
	void LoadMap(std::string path)					;//{;}
	bool IsInBounds(int _row, int _column);
//--------------------------------------------------------------------------------------------------
private:
	int**		mMap;

	Texture2D*	mWhiteTile;
	Texture2D*	mBlackTile;

	bool		mPause;
	int mTick;

	int GetLivingNeighbors(int _row, int _column);
	int IsAlive(int _row, int _column);
};


#endif //_GAMESCREEN_CONWAY_H
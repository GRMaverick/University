//------------------------------------------------------------------------
//  Author: Paul Roberts 2016
//------------------------------------------------------------------------

#include "GameScreen_Conway.h"
#include <stdlib.h>
#include "../Texture2D.h"
#include "ConwayConstants.h"
#include "../TinyXML/tinyxml.h"
#include <vector>
#include <chrono>
#include <ctime>

//--------------------------------------------------------------------------------------------------

GameScreen_Conway::GameScreen_Conway(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mTick = 0;

	mMap = new int*[kConwayScreenWidth/kConwayTileDimensions];
	for(int i =0; i < kConwayScreenWidth/kConwayTileDimensions; i++)
		mMap[i] = new int[kConwayScreenHeight/kConwayTileDimensions];

	//Get all required textures.
	mWhiteTile = new Texture2D(renderer);
	mWhiteTile->LoadFromFile("Images/Conway/WhiteTile.png");
	mBlackTile = new Texture2D(renderer);
	mBlackTile->LoadFromFile("Images/Conway/BlackTile.png");

	//Start map has 50% active cells.
	CreateRandomMap(75);

	//Start game in frozen state.
	mPause = true;
}

//--------------------------------------------------------------------------------------------------

GameScreen_Conway::~GameScreen_Conway()
{
	delete mWhiteTile;
	mWhiteTile = NULL;

	delete mBlackTile;
	mBlackTile = NULL;

	for(int i =0; i < kConwayScreenWidth/kConwayTileDimensions; i++)
	{
		delete mMap[i];
		mMap[i] = NULL;
	}
	delete mMap;
	mMap = NULL;
}

//--------------------------------------------------------------------------------------------------

void GameScreen_Conway::Render()
{
	std::cout << "RENDER" << std::endl;
	for(int x = 0; x < kConwayScreenWidth/kConwayTileDimensions; x++)
	{
		for(int y = 0; y < kConwayScreenHeight/kConwayTileDimensions; y++)
		{
			switch(mMap[x][y])
			{
				case 0:
					mBlackTile->Render(Vector2D(x*kConwayTileDimensions,y*kConwayTileDimensions));
				break;
				
				case 1:
					mWhiteTile->Render(Vector2D(x*kConwayTileDimensions,y*kConwayTileDimensions));
				break;
				default:
					std::cout << "Value is wrong" << std::endl;
					break;
			}
		}
	}
}

//--------------------------------------------------------------------------------------------------

void GameScreen_Conway::Update(size_t deltaTime, SDL_Event e)
{
	//Additional input outside of player.
	switch(e.type)
	{
		//Deal with mouse click input.
		case SDL_KEYUP:
			switch(e.key.keysym.sym)
			{
				case SDLK_SPACE:
 					mPause = !mPause;
				break;

				case SDLK_r:
					mPause = true;
					CreateRandomMap(75);
				break;

				case SDLK_l:
					mPause = true;
					LoadMap("Conway/ConwaySeed.xml");
				case SDLK_0:
				{
					std::chrono::time_point<std::chrono::system_clock> start, end;
					start = std::chrono::system_clock::now();
					std::time_t sTime = std::chrono::system_clock::to_time_t(start);
					std::cout << "Update Started: " << std::ctime(&sTime);
					UpdateMap();
					end = std::chrono::system_clock::now();
					std::time_t eTime = std::chrono::system_clock::to_time_t(end);
					std::cout << "Update Ended: " << std::ctime(&eTime);
					std::chrono::duration<double> elapsed_seconds = end - start;
					std::cout << "Elapsed Time: " << elapsed_seconds.count() << "s" << std::endl;
				}

				break;
			}
		break;
	
		default:
		break;
	}
	
	if (!mPause)
	{
		//std::chrono::time_point<std::chrono::system_clock> start, end;
		//start = std::chrono::system_clock::now();
		//std::time_t sTime = std::chrono::system_clock::to_time_t(start);
		//std::cout << "Update Started: " << std::ctime(&sTime);
		UpdateMapSecondary();
		//end = std::chrono::system_clock::now();
		//std::time_t eTime = std::chrono::system_clock::to_time_t(end);
		//std::cout << "Update Ended: " << std::ctime(&eTime);
		//std::chrono::duration<double> elapsed_seconds = end - start;
		//std::cout << "Elapsed Time: " << elapsed_seconds.count() << "s" << std::endl;
	}
}

//--------------------------------------------------------------------------------------------------

void GameScreen_Conway::UpdateMap()
{
	std::vector<std::vector<int>> newMap;

	for (int i = 0; i < kConwayScreenWidth / kConwayTileDimensions; i++)
	{
		std::vector<int> element;
		for (int j = 0; j < kConwayScreenHeight / kConwayTileDimensions; j++)
		{
			element.push_back(0);
		}
		newMap.push_back(element);
	}

	for (int i = 0; i < kConwayScreenWidth / kConwayTileDimensions; i++)
	{
		for (int j = 0; j < kConwayScreenHeight / kConwayTileDimensions; j++)
		{
			int neighbors = GetLivingNeighbors(i, j);
			
			if (IsAlive(i, j))
			{
				if (neighbors < 2)
				{
					// Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
					newMap[i][j] = 0;
				}
				if (neighbors == 2 || neighbors == 3)

				{
					// Any live cell with two or three live neighbours lives on to the next generation.
					newMap[i][j] = 1;
				}
				if (neighbors > 3)
				{
					// Any live cell with more than three live neighbours dies, as if by overpopulation.
					newMap[i][j] = 0;
				}
			}
			else
			{
				// Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
				if (neighbors == 3)
				{
					newMap[i][j] = 1;
				}
			}
		}
	}

	//for (int i = 0; i < 20; i++)
	//{
	//	for (int j = 0; j < 40; j++)
	//	{
	//		std::cout << mMap[i][j] << " ";
	//	}
	//	std::cout << std::endl;
	//}

	//std::cout << std::endl;

	//for (int i = 0; i < 20; i++)
	//{
	//	for (int j = 0; j < 40; j++)
	//	{
	//		std::cout << newMap[i][j] << " ";
	//	}
	//	std::cout << std::endl;
	//}

	for (int i = 0; i < kConwayScreenWidth / kConwayTileDimensions; i++)
	{
		for (int j = 0; j < kConwayScreenHeight / kConwayTileDimensions; j++)
		{
			mMap[i][j] = newMap[i][j];
		}
	}
}
void GameScreen_Conway::UpdateMapSecondary()
{
	int neighbours[kConwayScreenWidth / kConwayTileDimensions][kConwayScreenWidth / kConwayTileDimensions];

	// Check Neighbours
	for (int i = 0; i < kConwayScreenWidth / kConwayTileDimensions; i++)
	{
		for (int j = 0; j < kConwayScreenHeight / kConwayTileDimensions; j++)
		{
			neighbours[i][j] = 0;

			if (i - 1 >= 0)
				neighbours[i][j] += mMap[i - 1][j];

			if (i + 1 < kConwayScreenWidth / kConwayTileDimensions)
				neighbours[i][j] += mMap[i + 1][j];

			if (j - 1 >= 0)
				neighbours[i][j] += mMap[i][j - 1];

			if (j + 1 < kConwayScreenHeight / kConwayTileDimensions)
				neighbours[i][j] += mMap[i][j + 1];

			if (i - 1 >= 0 && j - 1 >= 0)
				neighbours[i][j] += mMap[i - 1][j - 1];

			if (i + 1 < kConwayScreenWidth / kConwayTileDimensions && j - 1 >= 0)
				neighbours[i][j] += mMap[i + 1][j - 1];

			if (i - 1 >= 0 && j + 1 < kConwayScreenHeight / kConwayTileDimensions)
				neighbours[i][j] += mMap[i - 1][j + 1];

			if (i + 1 < kConwayScreenWidth / kConwayTileDimensions && j + 1 < kConwayScreenHeight / kConwayTileDimensions)
				neighbours[i][j] += mMap[i + 1][j + 1];
		}
	}

	// Apply Rules
	for (int i = 0; i < kConwayScreenWidth / kConwayTileDimensions; i++)
	{
		for (int j = 0; j < kConwayScreenHeight / kConwayTileDimensions; j++)
		{
			//1. Any living cell with less than 2 live neighbour dies.
			if (mMap[i][j] == 1 && neighbours[i][j] < 2)
				mMap[i][j] = 0;

			//2. Any living cell with 2 or 3 live cells lives on to next generation.
			if (mMap[i][j] == 1 && (neighbours[i][j] == 2 || neighbours[i][j] == 3))
				mMap[i][j] = 1;

			//3. Any live cell with more than 3 live neighbours dies.
			if (mMap[i][j] == 1 && neighbours[i][j] > 3)
				mMap[i][j] = 0;

			//4. Any dead cell with exactly 3 live neighbours becomes a living cell.
			if (mMap[i][j] == 0 && neighbours[i][j] == 3)
				mMap[i][j] = 1;
		}
	}
}

int GameScreen_Conway::GetLivingNeighbors(int _row, int _column)
{
	int count = 0;

	for (int i = _row - 1; i <= _row + 1; i++)
	{
		if (i >= 0 && i < kConwayScreenWidth / kConwayTileDimensions)
		{
			for (int j = _column - 1; j <= _column + 1; j++)
			{
				if (j >= 0 && j < kConwayScreenHeight / kConwayTileDimensions)
				{
					if (i != _row || j != _column)
					{
						if (IsAlive(i, j))
						{
							count++;
						}
					}
				}
			}
		}
	}

	return count;
}
int GameScreen_Conway::IsAlive(int _row, int _column)
{
	return (mMap[_row][_column] == 1);
}
bool GameScreen_Conway::IsInBounds(int _row, int _column)
{
	return ((_row >= 0 && _row < kConwayScreenWidth) && (_column >= 0 && _column < kConwayScreenHeight));
}

//--------------------------------------------------------------------------------------------------

void GameScreen_Conway::CreateRandomMap(int percentageInactive)
{
	int randomNumber = 0;
	int liveCount = 0;
	for(int x = 0; x < kConwayScreenWidth/kConwayTileDimensions; x++)
	{
		for(int y = 0; y < kConwayScreenHeight/kConwayTileDimensions; y++)
		{
			randomNumber = (rand() % 100)+1;

			if (randomNumber > percentageInactive)
			{
				mMap[x][y] = 1;
				liveCount++;
			}
			else
			{
				mMap[x][y] = 0;
			}
		}
	}

	std::cout << "Initial Live Count: " << liveCount << std::endl;
}

//--------------------------------------------------------------------------------------------------

void GameScreen_Conway::LoadMap(std::string path)
{
	//Get the whole xml document.
	TiXmlDocument doc;
	if(!doc.LoadFile(path))
	{
		cerr << doc.ErrorDesc() << endl;
	}

	//Now get the root element.
	TiXmlElement* root = doc.FirstChildElement();
	if(!root)
	{
		cerr << "Failed to load file: No root element." << endl;
		doc.Clear();
	}
	else
	{
		//Jump to the first 'objectgroup' element.
		for(TiXmlElement* groupElement = root->FirstChildElement("objectgroup"); groupElement != NULL; groupElement = groupElement->NextSiblingElement())
		{
			string name = groupElement->Attribute("name");
			if(name == "Seed")
			{
				int x = 0;
				int y = 0;

				//Jump to the first 'object' element - within 'objectgroup'
				for(TiXmlElement* objectElement = groupElement->FirstChildElement("object"); objectElement != NULL; objectElement = objectElement->NextSiblingElement())
				{
					string name = objectElement->Attribute("name");
					if(name == "TileTypes")
					{
						//Reset x position of map to 0 at start of each element.
						x = 0;

						//Split up the comma delimited connections.
						stringstream ss(objectElement->Attribute("value"));
						int i;
						while(ss >> i)
						{
							mMap[x][y] = i;

							if(ss.peek() == ',')
								ss.ignore();

							//Increment the x position.
							x++;
						}

						//Move down to the next y position in the map.
						y++;
					}
				}
			}
		}
	}
}
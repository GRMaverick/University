//------------------------------------------------------------------------
//  Author: Paul Roberts 2017
//------------------------------------------------------------------------

#include "GameScreen_Lunar.h"
#include <stdlib.h>
#include "../Texture2D.h"
#include "LunarConstants.h"
#include "LunarLander.h"
#include <time.h>
#include <fstream>

//--------------------------------------------------------------------------------------------------

GameScreen_Lunar::GameScreen_Lunar(SDL_Renderer* renderer) : GameScreen(renderer)
{
	srand(static_cast <unsigned> (time(0)));

	//Set up the platform to land on.
	mPlatform = new Texture2D(renderer);
	mPlatform->LoadFromFile("Images/Lunar/Platform.png");

	//Create a lunar lander to use for tests.
	mPlatformPosition = Vector2D(198,430);

	//Player controlled lander.
	mLunarLander = new LunarLander(renderer, Vector2D(400,125), Rect2D(mPlatformPosition.x, mPlatformPosition.y, mPlatform->GetWidth(), mPlatform->GetHeight()));

	//AI controlled landers.
	mGeneration = 0;
	GenerateRandomChromosomes();
	for(int i = 0; i < kNumberOfAILanders; i++)
		mAILanders[i] = new LunarLander(renderer, Vector2D(400,125), Rect2D(mPlatformPosition.x, mPlatformPosition.y, mPlatform->GetWidth(), mPlatform->GetHeight()));
	RestartGA();
	mAllowMutation = true;
	mAccumulatedDeltaTime = 0;
	//-------------------------------------

	//Start game in frozen state.
	mPause = true;

	//Start game in player control.
	mAIOn = false;

	mTotalFitness = 0;
	mSelectionMethod = SelectionMethod_RWS;
	mCrossoverMethod = CrossoverMethod_SinglePointCrossover;
}

//--------------------------------------------------------------------------------------------------

GameScreen_Lunar::~GameScreen_Lunar()
{
	delete mPlatform;
	mPlatform = NULL;

	delete mLunarLander;
	mLunarLander = NULL;

	for(int i = 0; i < kNumberOfAILanders; i++)
		delete *mAILanders;
}

//--------------------------------------------------------------------------------------------------

void GameScreen_Lunar::Render()
{
	mPlatform->Render(mPlatformPosition);

	if(mAIOn)
	{
		for(int i = 0; i < kNumberOfAILanders; i++)
			mAILanders[i]->Render();
	}
	else
		mLunarLander->Render();
}

//--------------------------------------------------------------------------------------------------

void GameScreen_Lunar::Update(size_t deltaTime, SDL_Event e)
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
					if(mPause)
						cout << "Paused" << endl;
					else
						cout << "Unpaused" << endl;
				break;

				case SDLK_a:
					mAIOn = !mAIOn;
					if(mAIOn)
						cout << "AI on" << endl;
					else
						cout << "AI off" << endl;
				break;

				case SDLK_LEFT:
					if(!mAIOn)
						mLunarLander->TurnLeft(deltaTime);
				break;

				case SDLK_RIGHT:
					if(!mAIOn)
						mLunarLander->TurnRight(deltaTime);
				break;

				case SDLK_UP:
					if(!mAIOn)
						mLunarLander->Thrust();
				break;

				case SDLK_r:
					if (!mAIOn)
					{
						mLunarLander->Reset();
						return;
					}
					else
					{
						mGeneration = 500;
					}
				break;
			}
		break;
	
		default:
		break;
	}
	
	if(!mPause)
	{
		mAccumulatedDeltaTime += deltaTime;
		if (mAccumulatedDeltaTime > 50)
		{
			//Reset the count.
			mAccumulatedDeltaTime = 0;

			if (!mAIOn)
				mLunarLander->Update(deltaTime, e);
			else
				UpdateAILanders(deltaTime, e);
		}
	}
}

//--------------------------------------------------------------------------------------------------

void GameScreen_Lunar::GenerateRandomChromosomes()
{
	for(int lander = 0; lander < kNumberOfAILanders; lander++)
	{
		for(int action = 0; action < kNumberOfChromosomeElements; action++)
		{
			mChromosomes[lander][action] = (LunarAction)(rand()%LunarAction_MaxActions);
		}
	}
}

//--------------------------------------------------------------------------------------------------

void GameScreen_Lunar::ClearChromosomes()
{
	for(int lander = 0; lander < kNumberOfAILanders; lander++)
	{
		for(int action = 0; action < kNumberOfChromosomeElements; action++)
		{
			mChromosomes[lander][action] = LunarAction_None;
		}
	}
}

//--------------------------------------------------------------------------------------------------

void GameScreen_Lunar::UpdateAILanders(size_t deltaTime, SDL_Event e)
{
	int numberDeadOrLanded = 0;

	for (int i = 0; i < kNumberOfAILanders; i++)
	{
		mAILanders[i]->Update(deltaTime, e);

		if (!mAILanders[i]->IsAlive() || mAILanders[i]->HasLanded())
			numberDeadOrLanded++;
	}

	int landed = 0;
	for (int i = 0; i < kNumberOfAILanders; i++)
	{
		if (mAILanders[i]->HasLanded())
		{
			landed++;
		}
	}
	
	if (landed == kNumberOfAILanders)
	{
		SaveSolution();
		mPause = true;
	}
	else
	{
		//Are all finished?
		if (numberDeadOrLanded == kNumberOfAILanders)
		{
			CalculateFitness();
			return;
		}

		//Move on to the next action in the Chromosomes.
		mCurrentAction++;
		if (mCurrentAction >= kNumberOfChromosomeElements)
			return;

		//Assign all actions to landers.
		for (int i = 0; i < kNumberOfAILanders; i++)
		{
			switch (mChromosomes[i][mCurrentAction])
			{
			case LunarAction_LunarLeft:
				mAILanders[i]->TurnLeft(deltaTime);
				break;

			case LunarAction_LunarRight:
				mAILanders[i]->TurnRight(deltaTime);
				break;

			case LunarAction_LunarThrust:
				mAILanders[i]->Thrust();
				break;
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------

void GameScreen_Lunar::CalculateFitness()
{
	//Todo: Code this function.

	for (int lander = 0; lander < kNumberOfAILanders; lander++)
	{
		mFitnessValues[lander] = 0;

		if (mAILanders[lander]->HasLanded())
		{
			mFitnessValues[lander] += kLandingBonus;
		}
		else
		{
			double distance = Vec2DDistance(mPlatformPosition, mAILanders[lander]->GetPosition());
			double rotationFitness = ((cos(mAILanders[lander]->GetRotationAngle())) + 1) / 2;
			double survivalTime = mAILanders[lander]->GetSurvivalTime() * kAirTimeWeight;

			mFitnessValues[lander] = rotationFitness + survivalTime + ((kLunarScreenWidth - distance)  * kDistWeight);
		}

		mTotalFitness += mFitnessValues[lander];
	}

	Selection();
}

int GameScreen_Lunar::IsNearLanding(int lander)
{
	if (mAILanders[lander]->HasLanded())
	{
		return 0;
	}
	else
	{
		return (int)(mAILanders[lander]->GetCentralPosition() - Vector2D(mPlatformPosition.x, mPlatformPosition.y + 20)).Length();
	}
}

//--------------------------------------------------------------------------------------------------

void GameScreen_Lunar::Selection()
{
	switch (mSelectionMethod)
	{
		case SelectionMethod_TournamentSelection:
			TournamentSelection();
			break;
		case SelectionMethod_RWS:
			RouletteWheelSelection();
			break;
		case SelectionMethod_SUS:
			StochasticUniversalSampling();
			break;
		case SelectionMethod_None:
		default:
			std::cout << "No SELECTION selected!" << std::endl;
			break;
	}
	Crossover();
}
void GameScreen_Lunar::TournamentSelection()
{

}
void GameScreen_Lunar::RouletteWheelSelection()
{
	for(int lander = 0; lander < kNumberOfAILanders; lander++)
	{
		int slice = (rand() % (0, mTotalFitness + 1));
		int select = 0;
		int total = 0;

		while (total < slice)
		{
			if (total < 0)
			{
				total = 0;
			}

			if (total + mFitnessValues[select] > slice)
			{
				break;
			}
			else
			{
				total += mFitnessValues[select];
				select++;
			}
		}

		for (int gene = 0; gene < kNumberOfChromosomeElements; gene++)
		{
			mSelectedAIChromosomes[lander][gene] = mChromosomes[select][gene];
		}
	}
}
void GameScreen_Lunar::StochasticUniversalSampling()
{

}

//--------------------------------------------------------------------------------------------------

void GameScreen_Lunar::Crossover()
{
	switch (mCrossoverMethod)
	{
		case CrossoverMethod_SinglePointCrossover:
			SinglePointCrossover();
			break;
		case CrossoverMethod_NPointCrossover:
			NPointCrossover(2);
			break;
		case CrossoverMethod_UniformCrossover:
			UniformCrossover();
			break;
		case CrossoverMethod_None:
		default:
			std::cout << "No CROSSOVER selected!" << std::endl;
			break;
	}

	Mutation();
}
void GameScreen_Lunar::SinglePointCrossover()
{
	for (int lander = 0; lander < kNumberOfAILanders; lander+=2)
	{
		if ((rand() % 10000) > kCrossoverRate)
		{
			for (int gene = 0; gene < kNumberOfChromosomeElements; gene++)
			{
				mChromosomes[lander][gene] = mSelectedAIChromosomes[lander][gene];
				mChromosomes[lander + 1][gene] = mSelectedAIChromosomes[lander+1][gene];
			}
		}
		else
		{
			int crossoverPoint = (rand() % kNumberOfChromosomeElements);

			for (int gene = 0; gene < crossoverPoint; gene++)
			{
				mChromosomes[lander][gene] = mSelectedAIChromosomes[lander][gene];
				mChromosomes[lander + 1][gene] = mSelectedAIChromosomes[lander + 1][gene];
			}
			for (int gene = crossoverPoint; gene < kNumberOfChromosomeElements; gene++)
			{
				mChromosomes[lander][gene] = mSelectedAIChromosomes[lander + 1][gene];
				mChromosomes[lander + 1][gene] = mSelectedAIChromosomes[lander][gene];
			}
		}
	}
}
void GameScreen_Lunar::NPointCrossover(int points)
{
	for (int lander = 0; lander < kNumberOfAILanders; lander += 2)
	{
		if ((rand() % 10000) > kCrossoverRate)
		{
			for (int gene = 0; gene < kNumberOfChromosomeElements; gene++)
			{
				mChromosomes[lander][gene] = mSelectedAIChromosomes[lander][gene];
				mChromosomes[lander + 1][gene] = mSelectedAIChromosomes[lander + 1][gene];
			}
		}
		else
		{
			std::vector<int> pointsVector;
			pointsVector.push_back(0);
			for (int i = 0; i < points; i++)
			{
				pointsVector.push_back(rand() % kNumberOfChromosomeElements);
			}

			int start = pointsVector[0];
			int next = pointsVector[1];
			for (int sections = 0; sections < pointsVector.size(); sections++)
			{
				for (int gene = start; gene < next; gene++)
				{
					if (!(sections % 2))
					{
						mChromosomes[lander][gene] = mSelectedAIChromosomes[lander][gene];
						mChromosomes[lander + 1][gene] = mSelectedAIChromosomes[lander + 1][gene];
					}
					else
					{
						mChromosomes[lander][gene] = mSelectedAIChromosomes[lander + 1][gene];
						mChromosomes[lander + 1][gene] = mSelectedAIChromosomes[lander][gene];
					}
				}
				
				if (sections == pointsVector.size() - 1)
				{
					start = pointsVector.back();
					next = kNumberOfChromosomeElements;
				}
				else
				{
					start = pointsVector[sections];
					next = pointsVector[sections + 1];
				}
			}
		}
	}
}
void GameScreen_Lunar::UniformCrossover() 
{

}

//--------------------------------------------------------------------------------------------------

void GameScreen_Lunar::Mutation()
{
	//Todo: Code this function.

	for (int i = 0; i < kNumberOfAILanders; i++)
	{
		for (int j = 0; j < kNumberOfChromosomeElements; j++)
		{
			if ((rand() % 10000) < kMutationRate)
			{
				mChromosomes[i][j] = (LunarAction)(rand() % LunarAction_MaxActions);
			}
		}
	}

	RestartGA();
}

//--------------------------------------------------------------------------------------------------

void GameScreen_Lunar::RestartGA()
{


	if(mGeneration >= 500)
	{
		GenerateRandomChromosomes();
		mGeneration = 0;
		mAllowMutation = true;
		cout << endl << "---FAILED (Restart)---" << endl << endl;
	}

	for(int i = 0; i < kNumberOfAILanders; i++)
	{
		mFitnessValues[i] = 0.0f;
		mAILanders[i]->Reset();
	}

	mTotalFitness = 0;
	mAccumulatedDeltaTime = 0;
	mCurrentAction		  = 0;
	//mPause				  = true;
	//cout << "Paused" << endl;
	mGeneration++;
	cout << "---GENERATION " << mGeneration << "---" << endl;
}

//--------------------------------------------------------------------------------------------------

void GameScreen_Lunar::SaveSolution()
{
	//Output the solution of the first chromosome - They should all match at the point we output so it
	//shouldn't matter which chromosome is used for the solution.
	ofstream outFile("Solution.txt");
	if(outFile.is_open())
	{
		for(int action = 0; action < kNumberOfChromosomeElements; action++)
		{
			switch(mChromosomes[0][action])
			{
				case LunarAction_None:
					outFile << "0";
				break;
			
				case LunarAction_LunarThrust:
					outFile << "1";
				break;

				case LunarAction_LunarLeft:
					outFile << "2";
				break;

				case LunarAction_LunarRight:
					outFile << "3";
				break;
			}
		
			outFile << ",";
		}

		outFile << endl << "Generations taken: " << mGeneration;
		outFile << endl << "Platform start (" << mPlatformPosition.x << "," << mPlatformPosition.y << ")";
		outFile << endl << "Ship start (" << mAILanders[0]->GetStartPosition().x << "," << mAILanders[0]->GetStartPosition().y << ")";

		outFile.close();
	}
}

//--------------------------------------------------------------------------------------------------

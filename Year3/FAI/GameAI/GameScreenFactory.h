#pragma once

#include "GameScreenManager.h"

class GameScreenFactory
{
public:
	static GameScreenManager* Create(std::string _desiredGameScreen);
};
#pragma once

#include <vector>

#include "..\Common\StepTimer.h"

class IEntity;

class ISystem
{
public:
	virtual ~ISystem(void) { }
	virtual void Update(DX::StepTimer const& timer) = 0;
};
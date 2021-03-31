#pragma once

#include "IMessage.h"

class FireProjectileMessage : public IMessage
{
public:
	FireProjectileMessage(void) { }
	virtual ~FireProjectileMessage(void) { }
};
#pragma once

#include "IMessage.h"

class ReloadWeaponMessage : public IMessage
{
public:
	ReloadWeaponMessage(void) { };
	virtual ~ReloadWeaponMessage(void) { };
};
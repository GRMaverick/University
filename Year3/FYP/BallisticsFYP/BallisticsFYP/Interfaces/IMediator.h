#pragma once

#include "SingleDelegate.h"

class IMessage;

class IMediator
{
public:
	virtual ~IMediator(void) { }

	virtual void Send(IMessage* message) = 0;
	virtual void RegisterReceiveCallback(SingleDelegate<void, IMessage*> callback) = 0;
};
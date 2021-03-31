#pragma once

#include "Delegate.h"
#include "IMediator.h"

class IMessage;

class SystemsMediator : public IMediator
{
public:
	Delegate<void, IMessage*>	m_ReceptionCallback;

	SystemsMediator(void);
	~SystemsMediator(void);

	void Send(IMessage* message) override;
	void RegisterReceiveCallback(SingleDelegate<void, IMessage*> callback) override;

};
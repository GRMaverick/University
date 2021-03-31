#include "pch.h"
#include "SystemsMediator.h"

SystemsMediator::SystemsMediator(void)
{

}

SystemsMediator::~SystemsMediator(void)
{

}

void SystemsMediator::Send(IMessage* message)
{
	m_ReceptionCallback(message);
}

void SystemsMediator::RegisterReceiveCallback(SingleDelegate<void, IMessage*> callback)
{
	m_ReceptionCallback += callback;
}
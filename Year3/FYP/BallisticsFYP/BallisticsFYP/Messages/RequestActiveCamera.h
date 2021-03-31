#pragma once

#include "IMessage.h"

class RequestActiveCamera : public IMessage
{
public:
	RequestActiveCamera(void);
	virtual ~RequestActiveCamera(void);
};
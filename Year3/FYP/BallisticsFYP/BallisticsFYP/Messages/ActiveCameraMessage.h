#pragma once
#include "IMessage.h"
#include "StaticCameraComponent.h"
#include <string>

class ActiveCameraMessage : public IMessage
{
public:
	ActiveCameraMessage(const std::string& camera);
	~ActiveCameraMessage(void);

	std::string GetActiveCamera(void);

private:
	std::string m_CameraName;
};
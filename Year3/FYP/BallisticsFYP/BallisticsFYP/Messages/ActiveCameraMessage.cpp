#include "pch.h"
#include "ActiveCameraMessage.h"

ActiveCameraMessage::ActiveCameraMessage(const std::string& camera)
{
	m_CameraName = camera;
}

ActiveCameraMessage::~ActiveCameraMessage(void)
{
}

std::string ActiveCameraMessage::GetActiveCamera(void)
{
	return m_CameraName;
}
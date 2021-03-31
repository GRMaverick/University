#include "pch.h"
#include "SetActiveCamera.h"

SetActiveCamera::SetActiveCamera(const std::string& name)
{
	m_Name = name;
}

SetActiveCamera::~SetActiveCamera(void)
{
}

std::string SetActiveCamera::GetNewActiveCamera(void)
{
	return m_Name;
}
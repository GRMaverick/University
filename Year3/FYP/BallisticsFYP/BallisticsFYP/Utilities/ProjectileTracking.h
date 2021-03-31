#pragma once

#include <map>
#include <string>
#include <vector>

#include "Vector3.h"

using namespace Mathematics::Structures;

struct ProjectileInformation
{
public:
	int Frame;
	Vector3 Position;
};

class ProjectileTracking
{
public:
	static void RegisterPosition(const std::string& name, const int& frame, const Vector3& position);
	static void ExportReport(const std::string& filepath);

private:
	static std::map<std::string, std::vector<ProjectileInformation>> m_ProjectileData;
};
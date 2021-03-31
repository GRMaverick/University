#include "pch.h"
#include "ProjectileTracking.h"

#include <fstream>
#include <iostream>

std::map<std::string, std::vector<ProjectileInformation>> ProjectileTracking::m_ProjectileData = std::map<std::string, std::vector<ProjectileInformation>>();

void ProjectileTracking::RegisterPosition(const std::string& name, const int& frame, const Vector3& position)
{
	ProjectileInformation info;
	info.Frame = frame;
	info.Position = position;

	m_ProjectileData[name].push_back(info);
}

void ProjectileTracking::ExportReport(const std::string& filepath)
{
	Platform::String^ localFolder = Windows::Storage::ApplicationData::Current->LocalFolder->Path;

	std::wstring folderNameW(localFolder->Begin());
	std::string folderNameA(folderNameW.begin(), folderNameW.end());

	const char* charStr = folderNameA.c_str();
	char filename[512];

	for (auto iter = m_ProjectileData.begin(); iter != m_ProjectileData.end(); ++iter)
	{
		sprintf_s(filename, "%s\\%s\\%s", charStr, filepath.c_str(), std::string(iter->first + ".csv").c_str());

		std::ofstream ofs;
		ofs.open(filename, std::ofstream::out);
		if (ofs.is_open())
		{
			ofs << "FRAME\tPOS_X\tPOS_Y\tPOS_Z" << std::endl;
			for (ProjectileInformation info : iter->second)
			{
				ofs << info.Frame << "\t" << info.Position.x << "\t" << info.Position.y << "\t" << info.Position.z << std::endl;
			}
			ofs.close();
		}
		else
		{
			std::cout << filename << ": File IO FAILED!" << std::endl;
			return;
		}
	}
}
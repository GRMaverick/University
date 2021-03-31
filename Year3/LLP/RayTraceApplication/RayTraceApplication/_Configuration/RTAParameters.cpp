#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "RTAParameters.h"

int RTAParameters::MaxFrames = 0;
int RTAParameters::ResolutionWidth = 0;
int RTAParameters::ResolutionHeight = 0;
int RTAParameters::NumberOfThreads = 0;
int RTAParameters::FramesPerSecond = 0;

bool RTAParameters::Parallel = false;
bool RTAParameters::Physics = false;
bool RTAParameters::MethodProfiling = false;

std::string RTAParameters::ReportPath = "";
std::string RTAParameters::RootOutputPath = "";
std::string RTAParameters::ApplicationType = "";
std::string RTAParameters::MP4OutputPath = "";
std::string RTAParameters::PPMOutputPath = "";
std::string RTAParameters::FilenameTemplate = "";

bool RTAParameters::LoadParametersCSV(char* filename)
{
	std::ifstream ifs(filename, std::ifstream::in);
	
	if (!ifs.is_open())
	{
		std::cout << filename << ": File IO FAILED!" << std::endl;
		return false;
	}

	std::string line;

	while (std::getline(ifs, line))
	{
		std::string token;
		std::vector<std::string> columns;
		std::istringstream ssTokens(line);

		while (std::getline(ssTokens, token, '\t'))
		{
			columns.push_back(token);
		}

		if (columns[0] == "FPS")
		{
			FramesPerSecond = atoi(columns[1].c_str());
		}
		else if (columns[0] == "FilenameTemplate")
		{
			FilenameTemplate = columns[1];
		}
		else if (columns[0] == "MP4OutputPath")
		{
			MP4OutputPath = columns[1];
		}
		else if (columns[0] == "PPMOutputPath")
		{
			PPMOutputPath = columns[1];
		}
		else if (columns[0] == "ResolutionWidth")
		{
			ResolutionWidth = atoi(columns[1].c_str());
		}
		else if (columns[0] == "ResolutionHeight")
		{
			ResolutionHeight = atoi(columns[1].c_str());
		}
		else if (columns[0] == "MaxFrames")
		{
			MaxFrames = atoi(columns[1].c_str());
		}
		else if (columns[0] == "Threads")
		{
			NumberOfThreads = atoi(columns[1].c_str());
		}
		else if (columns[0] == "ReportPath")
		{
			ReportPath = columns[1];
		}
		else if (columns[0] == "Parallel")
		{
			Parallel = (columns[1] == "True") ? true : false;
		}
		else if (columns[0] == "Physics")
		{
			Physics = (columns[1] == "True") ? true : false;
		}
		else if (columns[0] == "MethodProfiling")
		{
			MethodProfiling = (columns[1] == "True") ? true : false;
		}
	}

	return true;
}
void RTAParameters::DisplayParameters()
{
#ifdef _DEBUG
	std::cout << "======= RTA Parameters ======="				<< std::endl;
	std::cout << "FPS: "							<< FramesPerSecond		<< std::endl;
	std::cout << "Max Frames: "			<< MaxFrames				<< std::endl;
	std::cout << "Resolution Width: "		<< ResolutionWidth			<< std::endl;
	std::cout << "Resolution Height: "	<< ResolutionHeight		<< std::endl;
	std::cout << "MP4 Output Path: "		<< MP4OutputPath			<< std::endl;
	std::cout << "PPM Output Path: "	<< PPMOutputPath			<< std::endl;
	std::cout << "Filename Template: "	<< FilenameTemplate		<< std::endl;
	std::cout << std::endl;
#endif
}
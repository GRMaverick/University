#include <iostream>

#include "Timer.h"
#include "AppManager.h"
#include "TimerManager.h"
#include "BaseApplication.h"
#include "BackendApplication.h"
#include "MemoryPoolManager.h"

void CleanupManagers()
{
	MemoryPoolManager* pMemManager = MemoryPoolManager::Instance();
	delete pMemManager;
}

void SmoothScaling();

int main(int argc, char* argv[])
{
	bool bPreview = false;
	bool bBaseline = false;

#if _DEBUG
	std::cout << "Debug Executable - ";
	#ifdef MaxSpeedOptimisation
		std::cout << "Executing with Maximum Speed Optimisation" << std::endl;	
	#endif
	#ifdef FullOptimisation
		std::cout << "Executing with Full Optimisation" << std::endl;
	#endif
	#ifdef MethodCallOptimisation
		std::cout << "Executing with Method Call Optimisation" << std::endl;
	#endif
	#ifdef Baseline
		std::cout << "Executing Baseline" << std::endl;
		bBaseline = true;
	#endif
#else
	std::cout << "Release Executable - ";
	#ifdef MaxSpeedOptimisation
		std::cout << "Executing with Maximum Speed Optimisation" << std::endl;
	#endif
	#ifdef FullOptimisation
		std::cout << "Executing with Full Optimisation" << std::endl;
	#endif
	#ifdef MethodCallOptimisation
		std::cout << "Executing with Method Call Optimisation" << std::endl;
	#endif
	#ifdef Baseline
		std::cout << "Executing Baseline" << std::endl;
		bBaseline = true;
	#endif
#endif

	if (argc == 2)
	{
		if (std::string(argv[1]) == "preview")
		{
			bPreview = true;
		}
		else
		{
			bPreview = false;
		}
	}

	if (bBaseline)
	{
		std::cout << "Executing Baseline" << std::endl;
		SmoothScaling();
	}
	else
	{
		BaseApplication* application = new BackendApplication(bPreview);
		application->Run();
		delete application;

		CleanupManagers();
		return 0;
	}
}
#include <sstream>

#include "Timer.h"
#include "Sphere.h"
#include "Vector3.h"
#include "Rendering.h"
#include "RTAParameters.h"

void SmoothScaling()
{
	std::vector<Sphere> spheres;
	
	TimerManager::Instance()->CreateTimer("Frames");

	std::cout << "======= Loading: Baseline Render Config =======" << std::endl << std::endl;
	RTAParameters::LoadParametersCSV("Config\\BackendConfiguration.txt");

	std::stringstream ss1, ss2, ss3, ss4, ss5, ss6;
	ss1 << "mkdir \"" << RTAParameters::MP4OutputPath << "\"" << std::endl;
	ss2 << "mkdir \"" << RTAParameters::PPMOutputPath << "\"" << std::endl;
	ss3 << "mkdir \"" << RTAParameters::ReportPath << "\"" << std::endl;
	ss4 << "mkdir \"" << RTAParameters::ReportPath << "Memory\\\"" << std::endl;
	ss5 << "mkdir \"" << RTAParameters::ReportPath << "Timings\\\"" << std::endl;
	ss6 << "mkdir \"" << RTAParameters::ReportPath << "MethodCalls\\\"" << std::endl;

	std::system(ss1.str().c_str());
	std::system(ss2.str().c_str());
	std::system(ss3.str().c_str());
	std::system(ss4.str().c_str());
	std::system(ss5.str().c_str());
	std::system(ss6.str().c_str());

	for (float r = 0; r <= 10; r++)
	{
		spheres.push_back(Sphere(Vector3(0.0, -10004, -20), 10000, Vector3(0.20, 0.20, 0.20), 0, 0.0));
		spheres.push_back(Sphere(Vector3(0.0, 0, -20), r / 100, Vector3(1.00, 0.32, 0.36), 1, 0.5));
		spheres.push_back(Sphere(Vector3(5.0, -1, -15), 2, Vector3(0.90, 0.76, 0.46), 1, 0.0));
		spheres.push_back(Sphere(Vector3(5.0, 0, -25), 3, Vector3(0.65, 0.77, 0.97), 1, 0.0));

		TimerManager::Instance()->GetTimer("Frames")->StartTracking(std::string("Frame_" + std::to_string(r)), r);
		Renderer::BaselineRender(spheres, r);
		TimerManager::Instance()->GetTimer("Frames")->EndTracking(std::string("Frame_" + std::to_string(r)));

		std::cout << "Rendered and saved spheres" << r << ".ppm - Time Taken: " << TimerManager::Instance()->GetTimer("Frames")->GetExecutionTime(std::string("Frame_" + std::to_string(r))) << std::endl;
		spheres.clear();
	}

	TimerManager::Instance()->GetTimer("Frames")->ExportReport();
}
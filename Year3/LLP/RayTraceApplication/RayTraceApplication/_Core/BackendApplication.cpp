#include <sstream>
#include <iostream>

#include "Floor.h"
#include "Timer.h"
#include "Sphere.h"
#include "Physics.h"
#include "Collisions.h"
#include "Rendering.h"
#include "FfmpegUtility.h"
#include "MethodProfiler.h"
#include "TimerManager.h"
#include "RTAParameters.h"
#include "BackendApplication.h"
#include "MemoryPoolManager.h"

BackendApplication::BackendApplication(bool preview)
{
	this->Initialise(preview);
}
BackendApplication::~BackendApplication(void)
{
	delete m_Floor;

	delete m_SpheresArray[0];
	delete m_SpheresArray[1];
	delete m_SpheresArray[2];
	delete m_SpheresArray[3];
	delete m_SpheresArray[4];
	delete m_SpheresArray[5];
}

void BackendApplication::Initialise(bool preview)
{
	std::cout << "======= Ray Tracing Application =======" << std::endl << std::endl;
	std::cout << "==== Initialising Backend Application ====" << std::endl << std::endl;

	m_Preview = preview;

	if (!m_Preview)
	{
		std::cout << "======= Loading: Render Config =======" << std::endl << std::endl;
		RTAParameters::LoadParametersCSV("Config\\BackendConfiguration.txt");
	}
	else
	{
		std::cout << "======= Loading: Preview Config =======" << std::endl << std::endl;
		RTAParameters::LoadParametersCSV("Config\\PreviewBackendConfiguration.txt");
	}

	RTAParameters::DisplayParameters();

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

	m_Floor = new Floor(Vector3(0.0f), Vector3(1000.0f, 0.0f, 1000.0f), 1.0f);

	if (RTAParameters::Physics)
	{
		m_SpheresArray[0] = new Sphere(Vector3(0.0f, 5.0f, 10.0f), 0.5f, Vector3(0.20f, 0.20f, 0.20f), 0.0f, 0.0f, 0.0f, 1.0f, 0.5f);
		m_SpheresArray[1] = new Sphere(Vector3(0.0f, 6.0f, -20.0f), 1.5f, Vector3(1.00f, 0.32f, 0.36f), 1.0f, 0.5f, 0.0f, 2.0f, 0.3f);

		m_SpheresArray[2] = new Sphere(Vector3(5.0f, 6.0f, -15.0f), 0.5f, Vector3(0.90f, 0.76f, 0.46f), 1.0f, 0.0f, 0.0f, 2.0f, 0.2f);
		m_SpheresArray[3] = new Sphere(Vector3(5.0f, 5.0f, -30.0f), 1.25f, Vector3(0.65f, 0.77f, 0.97f), 1.0f, 0.0f, 0.0f, 1.0f, 0.4f);

		m_SpheresArray[4] = new Sphere(Vector3(-5.0f, 5.0f, -15.0f), 0.5f, Vector3(0.90f, 0.76f, 0.46f), 1.0f, 0.0f, 0.0f, 2.0f, 0.4f);
		m_SpheresArray[5] = new Sphere(Vector3(-5.0f, 6.0f, -30.0f), 1.25f, Vector3(0.65f, 0.77f, 0.97f), 1.0f, 0.0f, 0.0f, 1.0f, 0.3f);
	}
	else
	{
		m_SpheresArray[0] = new Sphere(Vector3(0.0f, -5.0f, 10.0f), 5.0f, Vector3(0.20f, 0.20f, 0.20f), 0.0f, 0.0f, 0.0f, 1.0f);
		m_SpheresArray[1] = new Sphere(Vector3(0.0f, 0.0f, -20.0f), 1.0f, Vector3(1.00f, 0.32f, 0.36f), 1.0f, 0.5f, 0.0f, 1.0f);

		m_SpheresArray[2] = new Sphere(Vector3(5.0f, -1.0f, -15.0f), 2.0f, Vector3(0.90f, 0.76f, 0.46f), 1.0f, 0.0f, 0.0f, 1.0f);
		m_SpheresArray[3] = new Sphere(Vector3(5.0f, 0.0f, -30.0f), 3.0f, Vector3(0.65f, 0.77f, 0.97f), 1.0f, 0.0f, 0.0f, 1.0f);

		m_SpheresArray[4] = new Sphere(Vector3(-5.0f, -1.0f, -15.0f), 2.0f, Vector3(0.90f, 0.76f, 0.46f), 1.0f, 0.0f, 0.0f, 1.0f);
		m_SpheresArray[5] = new Sphere(Vector3(-5.0f, 0.0f, -30.0f), 3.0f, Vector3(0.65f, 0.77f, 0.97f), 1.0f, 0.0f, 0.0f, 1.0f);
	}

	if (!preview)
	{
		MemoryPoolManager::Instance()->GenerateReport("Frame_0");

		TimerManager::Instance()->CreateTimer("FileIO");
		TimerManager::Instance()->CreateTimer("Frames");
		TimerManager::Instance()->CreateTimer("RenderThreads");
	}
}
void BackendApplication::Run(void)
{
	if (!m_Preview)
	{
		std::cout << "==== Executing Backend Application ====" << std::endl;
	}

	for (int frame = 0; frame < RTAParameters::MaxFrames; frame++)
	{
		if (!m_Preview)
		{
			if (RTAParameters::Physics)
			{
				Update(0.016f);
			}
		}

		Render(frame);

		if (!m_Preview)
		{
			MemoryPoolManager::Instance()->GenerateReport("Frame_" + std::to_string(frame + 1));
			MemoryPoolManager::Instance()->ExportReport();

			if (RTAParameters::MethodProfiling)
				MethodProfiler::ExportReport();
		}
	}

	if (!m_Preview)
	{
		FfmpegUtility::ExecuteCompression();
		TimerManager::Instance()->GetTimer("FileIO")->ExportReport();
		TimerManager::Instance()->GetTimer("Frames")->ExportReport();
		TimerManager::Instance()->GetTimer("RenderThreads")->ExportReport();
	}
}
void BackendApplication::Update(float deltaTime)
{
	for (int i = 0; i < MAX_SPHERES; i++)
	{
		Physics::ApplyGravity(m_SpheresArray[i], deltaTime);

		if (Collisions::SphereFloorCollision(m_SpheresArray[i], m_Floor))
		{
			Collisions::ResolveCollision(m_SpheresArray[i], m_Floor);
		}
	}
}
void BackendApplication::Render(int frame)
{
	if (RTAParameters::Parallel)
	{
		Renderer::ParallelRender(m_SpheresArray, MAX_SPHERES, frame, RTAParameters::NumberOfThreads);
	}
	else
	{
		Renderer::Render(m_SpheresArray, MAX_SPHERES, frame);
	}
}
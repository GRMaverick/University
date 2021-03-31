#include <sstream>
#include <iostream>

#include "Floor.h"
#include "Timer.h"
#include "Sphere.h"
#include "Rendering.h"
#include "FfmpegUtility.h"
#include "RTAParameters.h"
#include "ParallelStaticApp.h"
#include "MemoryPoolManager.h"

ParallelStaticApp::ParallelStaticApp(void)
{
	this->Initialise();
}
ParallelStaticApp::~ParallelStaticApp(void)
{
	delete m_Floor;

	delete m_SpheresArray[0];
	delete m_SpheresArray[1];
	delete m_SpheresArray[2];
	delete m_SpheresArray[3];
	delete m_SpheresArray[4];
	delete m_SpheresArray[5];
}

void ParallelStaticApp::Initialise(void)
{
	std::cout << "Initialising Static Parallel Application" << std::endl << std::endl;

	RTAParameters::LoadParametersCSV("Config\\ParallelStaticConfig.txt");
	RTAParameters::DisplayParameters();

	std::stringstream ss1, ss2, ss3, ss4;
	ss1 << "mkdir \"" << RTAParameters::MP4OutputPath << "\"" << std::endl;
	ss2 << "mkdir \"" << RTAParameters::PPMOutputPath << "\"" << std::endl;
	ss3 << "mkdir \"" << RTAParameters::ReportPath << "\"" << std::endl;
	ss4 << "mkdir \"" << RTAParameters::ReportPath << "Memory\\\"" << std::endl;
	std::system(ss1.str().c_str());
	std::system(ss2.str().c_str());
	std::system(ss3.str().c_str());
	std::system(ss4.str().c_str());

	m_Floor = new Floor(Vector3(0.0f), Vector3(1000.0f, 0.0f, 1000.0f), 1.0f);

	m_SpheresArray[0] = new Sphere(Vector3(0.0f, -5.0f, 10.0f), 5.0f, Vector3(0.20f, 0.20f, 0.20f), 0.0f, 0.0f, 0.0f, 1.0f);
	m_SpheresArray[1] = new Sphere(Vector3(0.0f, 0.0f, -20.0f), 1.0f, Vector3(1.00f, 0.32f, 0.36f), 1.0f, 0.5f, 0.0f, 1.0f);

	m_SpheresArray[2] = new Sphere(Vector3(5.0f, -1.0f, -15.0f), 2.0f, Vector3(0.90f, 0.76f, 0.46f), 1.0f, 0.0f, 0.0f, 1.0f);
	m_SpheresArray[3] = new Sphere(Vector3(5.0f, 0.0f, -30.0f), 3.0f, Vector3(0.65f, 0.77f, 0.97f), 1.0f, 0.0f, 0.0f, 1.0f);

	m_SpheresArray[4] = new Sphere(Vector3(-5.0f, -1.0f, -15.0f), 2.0f, Vector3(0.90f, 0.76f, 0.46f), 1.0f, 0.0f, 0.0f, 1.0f);
	m_SpheresArray[5] = new Sphere(Vector3(-5.0f, 0.0f, -30.0f), 3.0f, Vector3(0.65f, 0.77f, 0.97f), 1.0f, 0.0f, 0.0f, 1.0f);

	MemoryPoolManager::Instance()->GenerateReport("Frame_Start");

	Timer::Start();
}
void ParallelStaticApp::Run(void)
{
	std::cout << "Running Static Parallel Application" << std::endl;
	std::cout << "Number of Threads: " << RTAParameters::NumberOfThreads << std::endl << std::endl;

	for (int frame = 0; frame < RTAParameters::MaxFrames; frame++)
	{
		Update(0.016f);
		Render(frame);

		MemoryPoolManager::Instance()->GenerateReport("Frame_" + std::to_string(frame));
	}

	FfmpegUtility::ExecuteCompression();

	Timer::ExportReport();
	MemoryPoolManager::Instance()->ExportReport();
}
void ParallelStaticApp::Update(float deltaTime)
{

}
void ParallelStaticApp::Render(int frame)
{
	Renderer::ParallelRender(m_SpheresArray, MAX_SPHERES, frame, RTAParameters::NumberOfThreads);
}
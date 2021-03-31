#include <sstream>
#include <iostream>

#include "Floor.h"
#include "Timer.h"
#include "Sphere.h"
#include "Physics.h"
#include "Collisions.h"
#include "Rendering.h"
#include "FfmpegUtility.h"
#include "RTAParameters.h"
#include "MemoryPoolManager.h"
#include "ParallelPhysicsApp.h"

ParallelPhysicsApp::ParallelPhysicsApp(void)
{
	this->Initialise();
}
ParallelPhysicsApp::~ParallelPhysicsApp(void)
{
	delete m_Floor;

	delete m_SpheresArray[0];
	delete m_SpheresArray[1];
	delete m_SpheresArray[2];
	delete m_SpheresArray[3];
	delete m_SpheresArray[4];
	delete m_SpheresArray[5];
}

void ParallelPhysicsApp::Initialise(void)
{
	std::cout << "Initialising Physics Parallel Application" << std::endl << std::endl;

	RTAParameters::LoadParametersCSV("Config\\ParallelPhysicsConfig.txt");
	RTAParameters::DisplayParameters();

	std::stringstream ss1, ss2, ss3;
	ss1 << "mkdir \"" << RTAParameters::MP4OutputPath << "\"" << std::endl;
	ss2 << "mkdir \"" << RTAParameters::PPMOutputPath << "\"" << std::endl;
	ss3 << "mkdir \"" << RTAParameters::ReportPath << "\"" << std::endl;
	std::system(ss1.str().c_str());
	std::system(ss2.str().c_str());
	std::system(ss3.str().c_str());

	m_Floor = new Floor(Vector3(0.0f), Vector3(1000.0f, -100.0f, 1000.0f), 1.0f);

	m_SpheresArray[0] = new Sphere(Vector3(0.0f, 5.0f, 10.0f), 0.5f, Vector3(0.20f, 0.20f, 0.20f), 0.0f, 0.0f, 0.0f, 1.0f, 0.5f);
	m_SpheresArray[1] = new Sphere(Vector3(0.0f, 6.0f, -20.0f), 1.5f, Vector3(1.00f, 0.32f, 0.36f), 1.0f, 0.5f, 0.0f, 2.0f, 0.3f);

	m_SpheresArray[2] = new Sphere(Vector3(5.0f, 6.0f, -15.0f), 0.5f, Vector3(0.90f, 0.76f, 0.46f), 1.0f, 0.0f, 0.0f, 2.0f, 0.2f);
	m_SpheresArray[3] = new Sphere(Vector3(5.0f, 5.0f, -30.0f), 1.25f, Vector3(0.65f, 0.77f, 0.97f), 1.0f, 0.0f, 0.0f, 1.0f, 0.4f);

	m_SpheresArray[4] = new Sphere(Vector3(-5.0f, 5.0f, -15.0f), 0.5f, Vector3(0.90f, 0.76f, 0.46f), 1.0f, 0.0f, 0.0f, 2.0f, 0.4f);
	m_SpheresArray[5] = new Sphere(Vector3(-5.0f, 6.0f, -30.0f), 1.25f, Vector3(0.65f, 0.77f, 0.97f), 1.0f, 0.0f, 0.0f, 1.0f, 0.3f);

	MemoryPoolManager::Instance()->GenerateReport("Frame_Start");

	Timer::Start();
}
void ParallelPhysicsApp::Run(void)
{
	std::cout << "Running Physics Parallel Application" << std::endl;
	std::cout << "Number of Threads: " << RTAParameters::NumberOfThreads << std::endl << std::endl;

	for (int frame = 0; frame < RTAParameters::MaxFrames; frame++)
	{
		Update((float)(1 / (float)RTAParameters::FramesPerSecond));
		Render(frame);

		MemoryPoolManager::Instance()->GenerateReport("Frame_" + std::to_string(frame));
	}

	FfmpegUtility::ExecuteCompression();

	std::system("pause");
}
void ParallelPhysicsApp::Update(float deltaTime)
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
void ParallelPhysicsApp::Render(int frame)
{
	Renderer::ParallelRender(m_SpheresArray, MAX_SPHERES, frame, RTAParameters::NumberOfThreads);
}
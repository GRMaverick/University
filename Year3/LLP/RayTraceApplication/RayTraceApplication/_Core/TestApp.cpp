#include <iostream>

#include "Timer.h"
#include "Octree.h"
#include "Sphere.h"
#include "RTAParameters.h"
#include "MemoryPoolManager.h"
#include "TestApp.h"

TestApp::TestApp(void)
{
	this->Initialise();
}
TestApp::~TestApp(void)
{
	if (m_Octree) delete m_Octree;

	if (m_SpheresArray[0]) delete m_SpheresArray[0];
	if (m_SpheresArray[1]) delete m_SpheresArray[1];

	//if (m_SpheresArray[2]) delete m_SpheresArray[2];
	//if (m_SpheresArray[3]) delete m_SpheresArray[3];
	//if (m_SpheresArray[4]) delete m_SpheresArray[4];
	//if (m_SpheresArray[5]) delete m_SpheresArray[5];
}

void TestApp::Initialise(void)
{
	std::cout << "Initialising Test Application" << std::endl << std::endl;

	RTAParameters::LoadParametersCSV("Config\\SequentialStaticConfig.txt");
	RTAParameters::DisplayParameters();
	

	m_SpheresArray[0] = new Sphere(Vector3(0.0f, 5.0f, 10.0f), 0.5f, Vector3(0.20f, 0.20f, 0.20f), 0.0f, 0.0f, 0.0f, 1.0f, 0.5f);
	m_SpheresArray[1] = new Sphere(Vector3(0.0f, 6.0f, -20.0f), 0.5f, Vector3(1.00f, 0.32f, 0.36f), 1.0f, 0.5f, 0.0f, 2.0f, 0.3f);

	std::vector<Sphere*> spheres;
	spheres.push_back(m_SpheresArray[0]);
	spheres.push_back(m_SpheresArray[1]);

	m_Octree = new Octree(new BoundingBox(Vector3(0.0f), Vector3(255.0f)), spheres);

	//m_SpheresArray[2] = new Sphere(Vector3(5.0f, 6.0f, -15.0f), 0.5f, Vector3(0.90f, 0.76f, 0.46f), 1.0f, 0.0f, 0.0f, 2.0f, 0.2f);
	//m_SpheresArray[3] = new Sphere(Vector3(5.0f, 5.0f, -30.0f), 1.25f, Vector3(0.65f, 0.77f, 0.97f), 1.0f, 0.0f, 0.0f, 1.0f, 0.4f);

	//m_SpheresArray[4] = new Sphere(Vector3(-5.0f, 5.0f, -15.0f), 0.5f, Vector3(0.90f, 0.76f, 0.46f), 1.0f, 0.0f, 0.0f, 2.0f, 0.4f);
	//m_SpheresArray[5] = new Sphere(Vector3(-5.0f, 6.0f, -30.0f), 1.25f, Vector3(0.65f, 0.77f, 0.97f), 1.0f, 0.0f, 0.0f, 1.0f, 0.3f);

	MemoryPoolManager::Instance()->GenerateReport("Frame_" + std::to_string(0));

	Timer::Start();
}
void TestApp::Run(void)
{
	std::cout << "Running Test Application" << std::endl;

	//for (int frame = 0; frame < RTAParameters::MaxFrames; frame++)
	//{
		Update((float)(1 / (float)RTAParameters::FramesPerSecond));
		Render(1);

		MemoryPoolManager::Instance()->GenerateReport("Frame_" + std::to_string(0));
	//}
}
void TestApp::Update(float deltaTime)
{
	m_Octree->UpdateTree();
	MemoryPoolManager::Instance()->GenerateReport("Frame_" + std::to_string(0));
}
void TestApp::Render(int frame)
{
}
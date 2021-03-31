#include "pch.h"
#include "BallisticsFYPMain.h"
#include "Common\DirectXHelper.h"
#include "InputManager.h"

#include "TimerManager.h"

#include <iostream>

using namespace BallisticsFYP;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Concurrency;

// Loads and initializes application assets when the application is loaded.
BallisticsFYPMain::BallisticsFYPMain(const std::shared_ptr<DX::DeviceResources>& deviceResources) :	m_deviceResources(deviceResources)
{
	m_deviceResources->RegisterDeviceNotify(this);
	
	m_fpsTextRenderer = std::unique_ptr<SampleFpsTextRenderer>(new SampleFpsTextRenderer(m_deviceResources));

	m_BallisticsScene = std::unique_ptr<BallisticsSceneRenderer>(new BallisticsSceneRenderer(m_deviceResources));

	// Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/

	TimerManager::Instance()->CreateTimer("UpdateTimer");
	TimerManager::Instance()->CreateTimer("RenderTimer");
}

BallisticsFYPMain::~BallisticsFYPMain()
{
	m_deviceResources->RegisterDeviceNotify(nullptr);
}

void BallisticsFYPMain::CreateWindowSizeDependentResources() 
{
	m_sceneRenderer->CreateWindowSizeDependentResources();
}

void BallisticsFYPMain::Update() 
{
	m_timer.Tick([&]()
	{
		std::string trackingFrame = std::string("Frame" + std::to_string(m_timer.GetFrameCount()));
		TimerManager::Instance()->GetTimer("UpdateTimer")->StartTracking(trackingFrame, m_timer.GetFrameCount());
		{
			m_BallisticsScene->Update(m_timer);
			m_fpsTextRenderer->Update(m_timer);
		}
		TimerManager::Instance()->GetTimer("UpdateTimer")->EndTracking(trackingFrame);
	});
}

bool BallisticsFYPMain::Render() 
{
	bool bReturn = false;

		if (m_timer.GetFrameCount() == 0)
		{
			bReturn = false;
		}
		else
		{
			m_fpsTextRenderer->Render();
			m_deviceResources->Present();

			bReturn = true;
		}

	return bReturn;
}

void BallisticsFYPMain::OnDeviceLost()
{
	//m_sceneRenderer->ReleaseDeviceDependentResources();
	m_fpsTextRenderer->ReleaseDeviceDependentResources();
	m_BallisticsScene->ReleaseDeviceDependentResources();
}

void BallisticsFYPMain::OnDeviceRestored()
{
	//m_sceneRenderer->CreateDeviceDependentResources();
	m_fpsTextRenderer->CreateDeviceDependentResources();
	m_BallisticsScene->CreateDeviceDependentResources();

	CreateWindowSizeDependentResources();
}

#include "pch.h"
#include "BallisticsSceneRenderer.h"

//
// Standard Template Library
//
#include <iostream>

//
// Messages
//
#include "SetActiveCamera.h"
#include "SetAmmunitionType.h"
#include "ReloadWeaponMessage.h"
#include "RetractHammerMessage.h"
#include "FireProjectileMessage.h"

//
// Components
//
#include "WeaponComponent.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "FPSCameraComponent.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "ProjectileComponent.h"
#include "LineRenderComponent.h"
#include "StaticCameraComponent.h"
#include "FollowCameraComponent.h"

//
// Systems
//
#include "RenderSystem.h"
#include "CameraSystem.h"
#include "InternalBallisticsSystem.h"
#include "ExternalBallisticsSystem.h"
#include "TerminalBallisticsSystem.h"

//
// Managers
//
#include "InputManager.h"
#include "EntityManager.h"
#include "SystemsManager.h"
#include "ComponentManager.h"

//
// Mediators
//
#include "SystemsMediator.h"

//
// Prefabs
//
#include "M43_762_39.h"
#include "NATO_556x45.h"

//
// Utilities
//
#include "OBJLoader.h"
#include "DDSTextureLoader.h"
#include "GeometryGenerator.h"
#include "..\Common\DirectXHelper.h"

#include <string>
#include <windows.h>

//
// Profiling
//
#include "TimerManager.h"
#include "ProjectileTracking.h"

namespace BallisticsFYP
{
	BallisticsSceneRenderer::BallisticsSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources)
	{		
		m_IsFPSActive = true;
		m_DeviceResources = deviceResources;
		
		CreateDeviceDependentResources();
		CreateWindowSizeDependentResources();
		
		InitialiseEntities();
		InitialiseComponents();
		InitialiseSystems();
		InitialiseControls();

		LineRenderComponent::InitialiseShader(m_DeviceResources);
	}
	BallisticsSceneRenderer::~BallisticsSceneRenderer(void)
	{
	}

	void BallisticsSceneRenderer::InitialiseEntities(void)
	{
		EntitiesManager->RegisterEntity("Floor");
		EntitiesManager->RegisterEntity("Target50");
		EntitiesManager->RegisterEntity("Target100");
		EntitiesManager->RegisterEntity("Target200");
		EntitiesManager->RegisterEntity("FPSCamera");
		EntitiesManager->RegisterEntity("StaticCamera");
		EntitiesManager->RegisterEntity("FollowCamera");
		EntitiesManager->RegisterEntity("Primary_Weapon");
	}
	void BallisticsSceneRenderer::InitialiseComponents(void)
	{
		#pragma region RenderComponents
			#pragma region Primary_Weapon
				Material materialG36C = Material();
				materialG36C.ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
				materialG36C.diffuse = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
				materialG36C.specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
				materialG36C.specularPower = 0.0f;
		
				ID3D11ShaderResourceView* pTextureG36C;
				DX::ThrowIfFailed(CreateDDSTextureFromFile(m_DeviceResources->GetD3DDevice(), L"Assets\\Textures\\G36C_D.dds", nullptr, &pTextureG36C));

				RenderComponent* pRenderComponentG36C = new RenderComponent();
				pRenderComponentG36C->SetTexture(pTextureG36C)
					->SetMaterial(materialG36C)
					->AddGeometry(OBJLoader::Load("Assets\\OBJs\\G36C.obj", m_DeviceResources->GetD3DDevice(), true));
				ComponentsManager->RegisterComponent("Primary_Weapon", "Render", pRenderComponentG36C);
			#pragma endregion
			#pragma region Cube
				Material materialCube= Material();
				materialG36C.ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
				materialG36C.diffuse = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
				materialG36C.specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
				materialG36C.specularPower = 0.0f;

				ID3D11ShaderResourceView* pTextureCube;
				DX::ThrowIfFailed(CreateDDSTextureFromFile(m_DeviceResources->GetD3DDevice(), L"Assets\\Textures\\stone.dds", nullptr, &pTextureCube));

				RenderComponent* pRenderComponentCube = new RenderComponent();
				pRenderComponentCube->SetTexture(pTextureCube)
					->SetMaterial(materialCube)
					->AddGeometry(GeometryGenerator::BuildCube(m_DeviceResources->GetD3DDevice(), 1, 1, 1));
				ComponentsManager->RegisterComponent("Cube", "Render", pRenderComponentCube);
			#pragma endregion
			#pragma region Floor
				Material materialFloor = Material();
				materialFloor.ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
				materialFloor.diffuse = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
				materialFloor.specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
				materialFloor.specularPower = 0.0f;

				ID3D11ShaderResourceView* pTextureFloor;
				DX::ThrowIfFailed(CreateDDSTextureFromFile(m_DeviceResources->GetD3DDevice(), L"Assets\\Textures\\stone.dds", nullptr, &pTextureFloor));

				RenderComponent* pRenderComponentFloor = new RenderComponent();
				pRenderComponentFloor->SetTexture(pTextureFloor)
					->SetMaterial(materialFloor)
					->AddGeometry(GeometryGenerator::BuildQuad(m_DeviceResources->GetD3DDevice(), 1000, 1000));
				ComponentsManager->RegisterComponent("Floor", "Render", pRenderComponentFloor);
			#pragma endregion
			#pragma region Target
				Material materialTarget = Material();
				materialTarget.ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
				materialTarget.diffuse = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
				materialTarget.specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
				materialTarget.specularPower = 0.0f;

				ID3D11ShaderResourceView* pTextureTarget;
				DX::ThrowIfFailed(CreateDDSTextureFromFile(m_DeviceResources->GetD3DDevice(), L"Assets\\Textures\\Targets.dds", nullptr, &pTextureTarget));

				RenderComponent* pRenderComponentTarget50 = new RenderComponent();
				pRenderComponentTarget50->SetTexture(pTextureTarget)
					->SetMaterial(materialTarget)
					->AddGeometry(GeometryGenerator::BuildQuad(m_DeviceResources->GetD3DDevice(), 1, 1));
				ComponentsManager->RegisterComponent("Target50", "Render", pRenderComponentTarget50);

				RenderComponent* pRenderComponentTarget100 = new RenderComponent();
				pRenderComponentTarget100->SetTexture(pTextureTarget)
					->SetMaterial(materialTarget)
					->AddGeometry(GeometryGenerator::BuildQuad(m_DeviceResources->GetD3DDevice(), 1, 1));
				ComponentsManager->RegisterComponent("Target100", "Render", pRenderComponentTarget100);

				RenderComponent* pRenderComponentTarget200 = new RenderComponent();
				pRenderComponentTarget200->SetTexture(pTextureTarget)
					->SetMaterial(materialTarget)
					->AddGeometry(GeometryGenerator::BuildQuad(m_DeviceResources->GetD3DDevice(), 1, 1));
				ComponentsManager->RegisterComponent("Target200", "Render", pRenderComponentTarget200);
			#pragma endregion
		#pragma endregion

		#pragma region TransformComponents
				TransformComponent* pTransformComponentFPSCamera = new TransformComponent();
					pTransformComponentFPSCamera->SetPosition(0.0f, 1.4f, 0.0f)
					->SetRotation(0.0f, 0.0f, 0.0f)
					->SetScale(1.0f, 1.0f, 1.0f);
				ComponentsManager->RegisterComponent("FPSCamera", "Transform", pTransformComponentFPSCamera);

				TransformComponent* pTransformComponentCube = new TransformComponent();
				pTransformComponentCube->SetPosition(0.0f, 0.0f, 15.0f)
					->SetRotation(0.0f, 0.0f, 0.0f)
					->SetScale(1.0f, 1.0f, 1.0f);
				ComponentsManager->RegisterComponent("Cube", "Transform", pTransformComponentCube);

				TransformComponent* pTransformComponentG36C = new TransformComponent();
				pTransformComponentG36C->SetPosition(0.25, -0.2f, 0.5f)
					->SetRotation(0.0f, 90.0f, 0.0f)
					->SetScale(1.0f, 1.0f, 1.0f)
					->SetParent(pTransformComponentFPSCamera);
				ComponentsManager->RegisterComponent("Primary_Weapon", "Transform", pTransformComponentG36C);

				TransformComponent* pTransformComponentFloor = new TransformComponent();
				pTransformComponentFloor->SetPosition(50.0f, -2.0f, -50.0f)
					->SetRotation(90.0f, 0.0f, 0.0f)
					->SetScale(2.0f, 2.0f, 2.0f);
				ComponentsManager->RegisterComponent("Floor", "Transform", pTransformComponentFloor);
				
				TransformComponent* pTransformComponentTarget50 = new TransformComponent();
				pTransformComponentTarget50->SetPosition(-10.0f, 0.0f, 50.0f)
					->SetRotation(0.0f, 0.0f, 0.0f)
					->SetScale(2.0f, 2.0f, 2.0f);
				ComponentsManager->RegisterComponent("Target50", "Transform", pTransformComponentTarget50);

				TransformComponent* pTransformComponentTarget100 = new TransformComponent();
				pTransformComponentTarget100->SetPosition(0.0f, 0.0f, 100.0f)
					->SetRotation(0.0f, 0.0f, 0.0f)
					->SetScale(2.0f, 2.0f, 2.0f);
				ComponentsManager->RegisterComponent("Target100", "Transform", pTransformComponentTarget100);

				TransformComponent* pTransformComponentTarget200 = new TransformComponent();
				pTransformComponentTarget200->SetPosition(10.0f, 0.0f, 200.0f)
					->SetRotation(0.0f, 0.0f, 0.0f)
					->SetScale(2.0f, 2.0f, 2.0f);
				ComponentsManager->RegisterComponent("Target200", "Transform", pTransformComponentTarget200);
		#pragma endregion

		#pragma region CameraComponents
				StaticCameraComponent* pStaticCameraComponent = new StaticCameraComponent();
				pStaticCameraComponent->SetActive(false);
				pStaticCameraComponent->SetPosition(Vector3(0.0f, 12.0f, -20.0f));
				pStaticCameraComponent->SetTarget(Vector3(0.0f, 0.0f, 1.0f));
				pStaticCameraComponent->SetUp(Vector3(0.0f, 1.0f, 0.0f));
				pStaticCameraComponent->SetNearDepth(0.01f);
				pStaticCameraComponent->SetFarDepth(10000.0f);
				pStaticCameraComponent->SetWindowWidth(m_DeviceResources->GetOutputSize().Width);
				pStaticCameraComponent->SetWindowHeight(m_DeviceResources->GetOutputSize().Height);
				ComponentsManager->RegisterComponent("StaticCamera", "Camera", pStaticCameraComponent);

				FPSCameraComponent* pFPSCameraComponent = new FPSCameraComponent(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f),
					m_DeviceResources->GetOutputSize().Width, m_DeviceResources->GetOutputSize().Height, 0.01f, 10000.0f);
				pFPSCameraComponent->SetActive(true);
				ComponentsManager->RegisterComponent("FPSCamera", "Camera", pFPSCameraComponent);

				FollowCameraComponent* pFollowCameraComponent = new FollowCameraComponent(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f),
					m_DeviceResources->GetOutputSize().Width, m_DeviceResources->GetOutputSize().Height, 0.01f, 10000.0f);
				pFollowCameraComponent->SetActive(false);
				ComponentsManager->RegisterComponent("FollowCamera", "Camera", pFollowCameraComponent);
		#pragma endregion

		#pragma region WeaponComponents
		WeaponComponent* pWeaponComponentG36C = new WeaponComponent();
		pWeaponComponentG36C->SetActive(true)
			->SetName("Primary_Weapon")
			->SetRateOfFire(750)
			->SetBarrelTwistRate(7)
			->SetRoundsRemaining(30)
			->SetRoundsPerMagazine(30)
			->SetProjectile(new NATO_556x45())
			->SetFiringMode(WeaponComponent::FiringMode_SemiAutomatic);
		ComponentsManager->RegisterComponent("Primary_Weapon", "Weapon", pWeaponComponentG36C);
		#pragma endregion

		#pragma region CollisionComponents
		Vector3 offset = Vector3(0.0f, 0.0f, 0.0f);
		CollisionComponent* pCollisionComponentTarget100 = new CollisionComponent();
		pCollisionComponentTarget100->SetBoundingRadius(10.0f)
			->AddCollidingPlane(Plane(pTransformComponentTarget100->GetPosition(), Mathematics::Structures::Vector3(0.0f, 0.0f, -1.0f), Mathematics::Structures::Vector3(2.0f, 2.0f, 2.0f)));
		ComponentsManager->RegisterComponent("Target100", "Collision", pCollisionComponentTarget100);
		#pragma endregion 
			
		ProjectileComponent::SetApplicableForces(0
			| APPLICABLE_FORCE_GRAVITY
			| APPLICABLE_FORCE_DRAG
			| APPLICABLE_FORCE_WIND
			//| APPLICABLE_FORCE_LIFT
			//| APPLICABLE_FORCE_MAGNUS
			| APPLICABLE_FORCE_CORIOLIS 
		);
	}
	void BallisticsSceneRenderer::InitialiseSystems(void)
	{
		m_pMediator = std::make_shared<SystemsMediator>();

		RenderSystem* pRenderSystem = new RenderSystem();
		pRenderSystem->Initialise(m_DeviceResources);
		pRenderSystem->RegisterMediator(m_pMediator);

		CameraSystem* pCameraSystem = new CameraSystem();
		pCameraSystem->RegisterMediator(m_pMediator);

		InternalBallisticsSystem* pInternalBallistics = new InternalBallisticsSystem();
		pInternalBallistics->Initialise(m_DeviceResources);
		pInternalBallistics->RegisterMediator(m_pMediator);

		ExternalBallisticsSystem* pExternalBallistics = new ExternalBallisticsSystem();
		pExternalBallistics->SetGravity(-9.81f)
			->SetNorth(0.0f, 1.0f)
			->SetAirDensity(1.225f)
			->SetEarthTurnSpeed(1037.56f)
			->SetWindVector(Vector3(0.0f, 0.0f, 0.0f))
			->RegisterMediator(m_pMediator);

		TerminalBallisticsSystem* pTerminalBallistics = new TerminalBallisticsSystem();
		pTerminalBallistics->RegisterMediator(m_pMediator);

		SystemManager->RegisterSystem(pInternalBallistics);
		SystemManager->RegisterSystem(pExternalBallistics);
		SystemManager->RegisterSystem(pTerminalBallistics);
		SystemManager->RegisterSystem(pCameraSystem);
		SystemManager->RegisterSystem(pRenderSystem);

		SetActiveCamera* pSetActiveCamera = new SetActiveCamera("FPSCamera");
		m_pMediator->Send(pSetActiveCamera);
		delete pSetActiveCamera;
	}
	void BallisticsSceneRenderer::InitialiseControls(void)
	{
		//
		// Mouse Inputs
		//
		InputManager::Instance()->MouseMoved += ref new Delegates::MouseMoved([&](float x, float y)
		{
			dynamic_cast<FPSCameraComponent*>(ComponentsManager->GetComponent("FPSCamera", "Camera"))->Rotate(y * 0.00025f, x * 0.00025f);
		});
		InputManager::Instance()->LeftMouseButtonDown += ref new Delegates::MousePressed([&]()
		{
			FireProjectileMessage* pFireProjectileMessage = new FireProjectileMessage();
			m_pMediator->Send(pFireProjectileMessage);
			delete pFireProjectileMessage;
		});
		InputManager::Instance()->LeftMouseButtonUp += ref new Delegates::MouseReleased([&]()
		{
			RetractHammerMessage* pRetractHammerMessage = new RetractHammerMessage();
			m_pMediator->Send(pRetractHammerMessage);
			delete pRetractHammerMessage;
		});

		//
		// Keyboard Inputs
		//
		InputManager::Instance()->RegisterKeyboardCallback(Windows::System::VirtualKey::W, ref new Delegates::KeyPressed([&]()
		{
			dynamic_cast<FPSCameraComponent*>(ComponentsManager->GetComponent("FPSCamera", "Camera"))->Advance(0.25f);
		}));
		InputManager::Instance()->RegisterKeyboardCallback(Windows::System::VirtualKey::S, ref new Delegates::KeyPressed([&]()
		{
			dynamic_cast<FPSCameraComponent*>(ComponentsManager->GetComponent("FPSCamera", "Camera"))->Advance(-0.25f);
		}));
		InputManager::Instance()->RegisterKeyboardCallback(Windows::System::VirtualKey::A, ref new Delegates::KeyPressed([&]()
		{
			dynamic_cast<FPSCameraComponent*>(ComponentsManager->GetComponent("FPSCamera", "Camera"))->Strafe(-0.25f);
		}));
		InputManager::Instance()->RegisterKeyboardCallback(Windows::System::VirtualKey::D, ref new Delegates::KeyPressed([&]()
		{
			dynamic_cast<FPSCameraComponent*>(ComponentsManager->GetComponent("FPSCamera", "Camera"))->Strafe(0.25f);
		}));	
		InputManager::Instance()->RegisterKeyboardCallback(Windows::System::VirtualKey::R, ref new Delegates::KeyPressed([&]()
		{
			ReloadWeaponMessage* pReloadWeaponMessage = new ReloadWeaponMessage();
			m_pMediator->Send(pReloadWeaponMessage);
			delete pReloadWeaponMessage;
		}));
		InputManager::Instance()->RegisterKeyboardCallback(Windows::System::VirtualKey::E, ref new Delegates::KeyPressed([&]()
		{
			TimerManager::Instance()->ExportReport("");
			ProjectileTracking::ExportReport("");
		}));
		InputManager::Instance()->RegisterKeyboardCallback(Windows::System::VirtualKey::B, ref new Delegates::KeyPressed([&]()
		{
			if (m_BulletTimeActivated)
			{
			}
			else
			{

			}
		}));
		InputManager::Instance()->RegisterKeyboardCallback(Windows::System::VirtualKey::Number1, ref new Delegates::KeyPressed([&]
		{
			SetAmmunitionType* pSetAmmoTypeMessage = new SetAmmunitionType("5.56x45mm");
			m_pMediator->Send(pSetAmmoTypeMessage);
			delete pSetAmmoTypeMessage;
		}));
		InputManager::Instance()->RegisterKeyboardCallback(Windows::System::VirtualKey::Number2, ref new Delegates::KeyPressed([&]
		{
			SetAmmunitionType* pSetAmmoTypeMessage = new SetAmmunitionType("7.62x39mm");
			m_pMediator->Send(pSetAmmoTypeMessage);
			delete pSetAmmoTypeMessage;
		}));
		InputManager::Instance()->RegisterKeyboardCallback(Windows::System::VirtualKey::Number3, ref new Delegates::KeyPressed([&]
		{
			SetAmmunitionType* pSetAmmoTypeMessage = new SetAmmunitionType("9x19mm");
			m_pMediator->Send(pSetAmmoTypeMessage);
			delete pSetAmmoTypeMessage;
		}));
		InputManager::Instance()->RegisterKeyboardCallback(Windows::System::VirtualKey::NumberPad1, ref new Delegates::KeyReleased([&]()
		{
			SetActiveCamera* pActiveCameraMessage = new SetActiveCamera("FPSCamera");
			m_pMediator->Send(pActiveCameraMessage);
			delete pActiveCameraMessage;
		}));
		InputManager::Instance()->RegisterKeyboardCallback(Windows::System::VirtualKey::NumberPad2, ref new Delegates::KeyReleased([&]()
		{
			SetActiveCamera* pActiveCameraMessage = new SetActiveCamera("StaticCamera");
			m_pMediator->Send(pActiveCameraMessage);
			delete pActiveCameraMessage;
		}));
		InputManager::Instance()->RegisterKeyboardCallback(Windows::System::VirtualKey::NumberPad3, ref new Delegates::KeyReleased([&]()
		{
			SetActiveCamera* pActiveCameraMessage = new SetActiveCamera("FollowCamera");
			m_pMediator->Send(pActiveCameraMessage);
			delete pActiveCameraMessage;
		}));

		//
		// Xbox One Controller Inputs
		//
		InputManager::Instance()->SetLeftTriggerDeadzone(0.9f);
		InputManager::Instance()->SetRightTriggerDeadzone(0.9f);
		InputManager::Instance()->ButtonXPressed += ref new Delegates::ButtonPressed([&]()
		{
			ReloadWeaponMessage* pReloadWeaponMessage = new ReloadWeaponMessage();
			m_pMediator->Send(pReloadWeaponMessage);
			delete pReloadWeaponMessage;
		});
		InputManager::Instance()->RightTriggerPulled += ref new Delegates::TriggerPulled([&]()
		{
			FireProjectileMessage* pFireProjectileMessage = new FireProjectileMessage();
			m_pMediator->Send(pFireProjectileMessage);
			delete pFireProjectileMessage;
		});
		InputManager::Instance()->LeftStickMoved += ref new Delegates::StickMoved([&](float x, float y)
		{
			dynamic_cast<FPSCameraComponent*>(ComponentsManager->GetComponent("FPSCamera", "Camera"))->Advance(y * 0.2f);
			dynamic_cast<FPSCameraComponent*>(ComponentsManager->GetComponent("FPSCamera", "Camera"))->Strafe(x * 0.2f);
		});		
		InputManager::Instance()->RightStickMoved += ref new Delegates::StickMoved([&](float x, float y)
		{
			dynamic_cast<FPSCameraComponent*>(ComponentsManager->GetComponent("FPSCamera", "Camera"))->Rotate(-y * 0.05f, x * 0.05f);
		});
	}

	void BallisticsSceneRenderer::Update(DX::StepTimer const& timer)
	{
		InputManager::Instance()->Update();
		SystemManager->Update(timer);
	}

	void BallisticsSceneRenderer::CreateDeviceDependentResources(void)
	{
	}
	void BallisticsSceneRenderer::CreateWindowSizeDependentResources(void)
	{
	}
	void BallisticsSceneRenderer::ReleaseDeviceDependentResources(void)
	{
	}
}
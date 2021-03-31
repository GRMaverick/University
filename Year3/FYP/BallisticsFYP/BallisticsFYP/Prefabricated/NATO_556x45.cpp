#include "pch.h"
#include "NATO_556x45.h"

#include "EntityManager.h"
#include "ComponentManager.h"

#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "CollisionComponent.h"
#include "ProjectileComponent.h"
#include "TransformComponent.h"
#include "LineRenderComponent.h"

#include "OBJLoader.h"
#include "DDSTextureLoader.h"
#include "GeometryGenerator.h"
#include "../Common/DirectXHelper.h"
#include "../Common/DeviceResources.h"

float NATO_556x45::Length = 0.2f;
float NATO_556x45::Mass = 0.00356f;
float NATO_556x45::MuzzleVelocity = 920.0f;
float NATO_556x45::DragCoefficient = 0.325f;
float NATO_556x45::LiftCoefficient = 0.325f;
float NATO_556x45::FrontalArea = 0.00002552f;

NATO_556x45::NATO_556x45(void)
{
	m_ProjectileType = "556x45mm";
}
NATO_556x45::NATO_556x45(const std::string& name)
{
	m_Name = name;
	m_ProjectileType = "556x45mm";

	EntitiesManager->RegisterEntity(m_Name);
}
NATO_556x45::~NATO_556x45(void)
{

}

IProjectilePrefab* NATO_556x45::Clone(void)
{
	return new NATO_556x45();
}
IProjectilePrefab* NATO_556x45::Clone(const std::string& name)
{
	return new NATO_556x45(name);
}

bool NATO_556x45::Initialise(std::shared_ptr<DX::DeviceResources> deviceResources)
{
	InitialisePhysics();
	InitialiseCollision();
	InitialiseProjectile();
	InitialiseTransform();
	InitialiseRender(deviceResources);

#if defined(_DEBUG)
	InitialiseLineRender(deviceResources);
#endif

	return true;
}
bool NATO_556x45::InitialisePhysics(void)
{
	PhysicsComponent* pComponent = new PhysicsComponent();
	pComponent->SetMass(Mass)
		->SetVelocity(Vector3(0.0f, 0.0f, 0.0f))
		->SetNetforce(Vector3(0.0f, 0.0f, 0.0f))
		->SetAcceleration(Vector3(0.0f, 0.0f, 0.0f));
	ComponentsManager->RegisterComponent(m_Name, "Physics", pComponent);

	return true;
}
bool NATO_556x45::InitialiseCollision(void)
{
	CollisionComponent* pComponent = GeometryGenerator::ReadCollisionVertices("Assets\\OBJs\\Bullet.obj");
	pComponent->SetBoundingRadius(0.5f);
	ComponentsManager->RegisterComponent(m_Name, "Collision", pComponent);
	
	return true;
}
bool NATO_556x45::InitialiseProjectile(void)
{
	ProjectileComponent* pComponent = new ProjectileComponent();
	pComponent->SetFrontalArea(FrontalArea)
		->SetLength(Length)
		->SetRevolutionsPerMinute(0)
		->SetMuzzleVelocity(MuzzleVelocity)
		->SetDragCoefficient(DragCoefficient)
		->SetLiftCoefficient(LiftCoefficient)
		->SetBallisticPipelineState(ProjectileComponent::PipelineState_None);
	ComponentsManager->RegisterComponent(m_Name, "Projectile", pComponent);

	return true;
}
bool NATO_556x45::InitialiseTransform(void)
{
	TransformComponent* pComponent = new TransformComponent();
	pComponent->SetScale(Vector3(0.3f, 0.3f, 0.3f))
		->SetPosition(Vector3(0.0f, 0.0f, 0.0f))
		->SetRotation(Vector3(90.0f, 0.0f, 0.0f));
	ComponentsManager->RegisterComponent(m_Name, "Transform", pComponent);

	return true;
}
bool NATO_556x45::InitialiseRender(std::shared_ptr<DX::DeviceResources> deviceResources)
{
	Material material = Material();
	material.ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	material.diffuse = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
	material.specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	material.specularPower = 0.0f;

	ID3D11ShaderResourceView* texture;
	DX::ThrowIfFailed(CreateDDSTextureFromFile(deviceResources->GetD3DDevice(), L"Assets\\Textures\\stone.dds", nullptr, &texture));

	RenderComponent* pComponent = new RenderComponent();
	pComponent->SetTexture(texture)
		->SetMaterial(material)
		->AddGeometry(OBJLoader::Load("Assets\\OBJs\\Bullet.obj", deviceResources->GetD3DDevice(), true));
	ComponentsManager->RegisterComponent(m_Name, "Render", pComponent);

	return true;
}
bool NATO_556x45::InitialiseLineRender(std::shared_ptr<DX::DeviceResources> deviceResources)
{
	LineRenderComponent* pTrajectoryTracingComponent = new LineRenderComponent(m_Name + "_Trajectory");
	pTrajectoryTracingComponent->InitialiseBuffers(deviceResources->GetD3DDevice(), 1000);
	pTrajectoryTracingComponent->SetLineColour(DirectX::Colors::Red);
	ComponentsManager->RegisterComponent(m_Name, "LineRender_Trajectory", pTrajectoryTracingComponent);

	LineRenderComponent* pForceTracingComponent = new LineRenderComponent(m_Name + "_Forces");
	pForceTracingComponent->InitialiseBuffers(deviceResources->GetD3DDevice(), 100);
	pForceTracingComponent->SetLineColour(DirectX::Colors::Yellow);
	ComponentsManager->RegisterComponent(m_Name, "LineRender_Forces", pForceTracingComponent);

	return true;
}
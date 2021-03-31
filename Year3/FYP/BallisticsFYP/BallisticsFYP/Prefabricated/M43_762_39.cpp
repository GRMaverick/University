#include "pch.h"
#include "M43_762_39.h"

#include "EntityManager.h"
#include "ComponentManager.h"

#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "ProjectileComponent.h"
#include "LineRenderComponent.h"

#include "OBJLoader.h"
#include "DDSTextureLoader.h"
#include "GeometryGenerator.h"
#include "../Common/DirectXHelper.h"
#include "../Common/DeviceResources.h"

float M43_762_39::Mass = 0.0079f;
float M43_762_39::MuzzleVelocity = 716.0f;
float M43_762_39::DragCoefficient = 0.225f;
float M43_762_39::FrontalArea = 0.00004927f;

M43_762_39::M43_762_39(void)
{
	m_ProjectileType = "762x39mm";
}
M43_762_39::M43_762_39(const std::string& name)
{
	m_Name = name;
	m_ProjectileType = "762x39mm";
	EntitiesManager->RegisterEntity(m_Name);
}
M43_762_39::~M43_762_39(void)
{

}

IProjectilePrefab* M43_762_39::Clone(void)
{
	return new M43_762_39();
}
IProjectilePrefab* M43_762_39::Clone(const std::string& name)
{
	return new M43_762_39(name);
}

bool M43_762_39::Initialise(std::shared_ptr<DX::DeviceResources> deviceResources)
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
bool M43_762_39::InitialisePhysics(void)
{
	PhysicsComponent* pComponent = new PhysicsComponent();
	pComponent->SetMass(Mass)
		->SetVelocity(Vector3(0.0f, 0.0f, 0.0f))
		->SetNetforce(Vector3(0.0f, 0.0f, 0.0f))
		->SetAcceleration(Vector3(0.0f, 0.0f, 0.0f));
	ComponentsManager->RegisterComponent(m_Name, "Physics", pComponent);

	return true;
}
bool M43_762_39::InitialiseCollision(void)
{
	CollisionComponent* pComponent = GeometryGenerator::ReadCollisionVertices("Assets\\OBJs\\Bullet.obj");
	pComponent->SetBoundingRadius(0.5f);
	ComponentsManager->RegisterComponent(m_Name, "Collision", pComponent);

	return true;
}
bool M43_762_39::InitialiseProjectile(void)
{
	ProjectileComponent* pComponent = new ProjectileComponent();
	pComponent->SetFrontalArea(FrontalArea)
		->SetMuzzleVelocity(MuzzleVelocity)
		->SetDragCoefficient(DragCoefficient)
		->SetBallisticPipelineState(ProjectileComponent::PipelineState_None);
	ComponentsManager->RegisterComponent(m_Name, "Projectile", pComponent);

	return true;
}
bool M43_762_39::InitialiseTransform(void)
{
	TransformComponent* pComponent = new TransformComponent();
	pComponent->SetScale(Vector3(0.3f, 0.3f, 0.3f))
		->SetPosition(Vector3(0.0f, 0.0f, 0.0f))
		->SetRotation(Vector3(90.0f, 0.0f, 0.0f));
	ComponentsManager->RegisterComponent(m_Name, "Transform", pComponent);

	return true;
}
bool M43_762_39::InitialiseRender(std::shared_ptr<DX::DeviceResources> deviceResources)
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
bool M43_762_39::InitialiseLineRender(std::shared_ptr<DX::DeviceResources> deviceResources)
{
	LineRenderComponent* pTrajectoryTracingComponent = new LineRenderComponent(m_Name + "_Trajectory");
	pTrajectoryTracingComponent->InitialiseBuffers(deviceResources->GetD3DDevice(), 1000);
	pTrajectoryTracingComponent->SetLineColour(DirectX::Colors::Blue);
	ComponentsManager->RegisterComponent(m_Name, "LineRender_Trajectory", pTrajectoryTracingComponent);

	LineRenderComponent* pForceTracingComponent = new LineRenderComponent(m_Name + "_Forces");
	pForceTracingComponent->InitialiseBuffers(deviceResources->GetD3DDevice(), 100);
	pForceTracingComponent->SetLineColour(DirectX::Colors::Yellow);
	ComponentsManager->RegisterComponent(m_Name, "LineRender_Forces", pForceTracingComponent);

	return true;
}
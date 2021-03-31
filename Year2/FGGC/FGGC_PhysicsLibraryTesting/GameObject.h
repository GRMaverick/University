#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>

#include "Appearance.h"
#include "DPhysX Framework/Transform.h"
#include "DPhysX Framework/Particle.h"
#include "DPhysX Framework/RigidBody.h"

using namespace std;
using namespace DirectX;

class GameObject
{
public:
	GameObject(string type, Appearance * appearance, Transform * transform, Particle * particleModel);
	GameObject(string type, Appearance * appearance, Transform * transform, RigidBody * particleModel);

	~GameObject();

	string GetType() const { return _type; }

	Appearance * GetAppearance() const { return _appearance; }
	Transform * GetTransform() const { return _transform; }
	//Particle * GetParticleModel() const { return _particleModel; }
	RigidBody& GetRigidBody() const { return *_rigidBody; }

	void Update(float deltaTime);
	void Draw(ID3D11DeviceContext * pImmediateContext);

private:
	string _type;

	Appearance * _appearance;
	Transform * _transform;
	//Particle * _particleModel;
	RigidBody* _rigidBody;
};


#include "GameObject.h"

//GameObject::GameObject(string type, Appearance * appearance, Transform * transform, Particle * particleModel) : _appearance(appearance), _type(type), _transform(transform), _particleModel(particleModel)
//{
//
//}

GameObject::GameObject(string type, Appearance * appearance, Transform * transform, RigidBody * particleModel) : _appearance(appearance), _type(type), _transform(transform), _rigidBody(particleModel)
{

}

GameObject::~GameObject()
{
	//delete _particleModel;	
	delete _rigidBody;
	//delete _transform;
}

void GameObject::Update(float deltaTime)
{
	//_particleModel->Update(deltaTime);
	_rigidBody->Update(deltaTime);
	_transform->Update(deltaTime);
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	_appearance->Draw(pImmediateContext);
}

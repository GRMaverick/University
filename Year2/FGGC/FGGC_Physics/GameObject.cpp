#include "GameObject.h"

GameObject::GameObject(string type, Appearance* appearance, Transform* transform, ParticleModel * particleModel)
{
	_appearance = appearance;
	_transform = transform;
	_particleModel = particleModel;
	_type = type;
}
GameObject::~GameObject()
{
}

void GameObject::Update(float t)
{
	_transform->Update(t);
	_particleModel->Update(t);
	
	if (!_children.empty())
	{
		for each(GameObject* child in _children)
			child->Update(t);
	}
}
void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	_appearance->Draw(pImmediateContext);
}

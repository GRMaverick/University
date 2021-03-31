#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>

#include "Commons.h"
#include "Components.h"

using namespace std;
using namespace DirectX;

// Build the DLL Files in Library Project
// Include in Additional Libraries (Properties > Linker > General)
// Include in Additional Dependancies (Properties > Linker > Input)

class GameObject
{
public:
	GameObject(string type, Appearance* appearance, Transform * transform, ParticleModel * particleModel);
	~GameObject();

	string GetType() const { return _type; }

	Appearance * GetAppearance() const { return _appearance; }
	Transform * GetTransform() const { return _transform; }
	ParticleModel * GetParticleModel() const { return _particleModel; }

	virtual void Update(float t);
	virtual void Draw(ID3D11DeviceContext * pImmediateContext);

	inline void SetBBox(BoundingBox bb) { bbox = bb; }
	inline BoundingBox GetBBox() const { return bbox; }

	inline void AddChild(GameObject* child) { _children.push_back(child); child->GetTransform()->SetParent(_transform); }
	inline void RemoveFirst() { _children.front()->GetTransform()->SetParent(nullptr); _children.pop_back(); }
	inline vector<GameObject*> GetChildren() { return _children; }
	
private:
	string _type;

	BoundingBox bbox;

	Transform* _transform;
	Appearance* _appearance;
	ParticleModel* _particleModel;
	vector<GameObject*> _children;
};


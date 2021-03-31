#pragma once
#include "GameObjects.h"
#include "Structures.h"

class Gun : public GameObjects
{
private: 
	Vector3* _position;
	OBJMesh* _mesh;
public:
	Gun(OBJMesh* mesh);
	~Gun();

	void Draw();
	void Update();
};


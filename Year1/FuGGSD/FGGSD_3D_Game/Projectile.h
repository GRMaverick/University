#pragma once
#include "GameObjects.h"
#include "Structures.h"

class Projectile : public GameObjects
{
private:
	Vector3* _position;
	OBJMesh* _mesh;
public:
	Projectile(OBJMesh* mesh);
	~Projectile();

	void Draw();
	void Update();
	void Trajectory();
};


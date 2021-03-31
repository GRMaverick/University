#pragma once
#include "Level.h"
#include "Structures.h"

class Ground : public Level
{
private: 
	Vector3* _position;
	OBJMesh* _mesh;
public:
	Ground(OBJMesh* mesh);
	~Ground();

	void Draw();
	void Update();
};


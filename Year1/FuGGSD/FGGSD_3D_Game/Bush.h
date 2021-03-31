#pragma once
#include "Structures.h"
#include "Level.h"

class Bush : public Level
{
private: 
	OBJMesh* _mesh;
	Vector3* _position;

public:
	Bush(OBJMesh* mesh);
	~Bush();

	void Draw();
	void Update();
};


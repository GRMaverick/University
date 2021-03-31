#pragma once
#include "Level.h"

class Tree : public Level
{
private: 
	OBJMesh* _mesh;
	Vector3* _position;
public:
	Tree(OBJMesh* mesh);
	~Tree();

	void Draw();
	void Update();
};


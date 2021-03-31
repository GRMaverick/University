#pragma once
#include "Headers_Structures.h"
#include "Texture2D.h"
class Fighter
{
private:
	Vector3* _position;
	Texture2D* _texture;
	OBJMesh* _mesh;

public:
	Fighter();
	~Fighter();

	void virtual Draw() = 0;
	void virtual Update() = 0;
	void virtual UpdateAngle(char key) = 0;
};


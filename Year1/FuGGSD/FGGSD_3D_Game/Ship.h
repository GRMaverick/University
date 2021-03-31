#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "GL\freeglut.h"
#include "Headers_Structures.h"
#include "Texture2D.h"

class Ship
{
private:
	// Variables
	OBJMesh* _mesh;
	Texture2D* _texture;
	Vector3* _position;

	float _rotation;
	char _key;

	bool _sBool;
	bool _dBool;
	bool _aBool;
	bool _wBool;

public:

	// Constructors
	Ship();
	Ship(OBJMesh* mesh, Material* material, float x, float y, float z);

	// Destructors
	~Ship();

	// Gameloop Methods
	void Draw();
	void Update();
	void UpdateAngle(char key);
	bool UpdateAngleUp(char key);

	// Getters
	OBJMesh* GetMesh();
	Vector3* GetPostion();
};


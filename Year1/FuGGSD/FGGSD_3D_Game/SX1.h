#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "GL\freeglut.h"
#include "Headers_Structures.h"
#include "Texture2D.h"

class SX1
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
	SX1();
	SX1(OBJMesh* mesh);

	// Destructors
	~SX1();

	// Gameloop Methods
	void Draw();
	void Update();
	void UpdateAngle(char key);
	bool UpdateAngleUp(char key);

	//Setters
	void SetMesh(OBJMesh* mesh);
	void SetPosition(Vector3* position);
	void SetTexture(Texture2D* texture);

	// Getters
	OBJMesh* GetMesh();
	Vector3* GetPostion();
	Texture2D* GetTexture();
};


#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "GL\freeglut.h"
#include "Headers_Structures.h"
#include "Texture2D.h"

class Normandy
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
	Normandy();
	Normandy(OBJMesh* mesh);

	// Destructors
	~Normandy();

	// Gameloop Methods
	void Draw();
	void Update();
	void UpdateAngle(char key);
	
	//Setters
	void SetMesh(OBJMesh* mesh);
	void SetPosition(Vector3* position);
	void SetTexture(Texture2D* texture);

	// Getters
	OBJMesh* GetMesh();
	Vector3* GetPostion();
	Texture2D* GetTexture();
};


#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"

#include "Headers_Structures.h"
#include "Texture2D.h"

class Cube
{
private:
	// Variables
	Vector3* _position;
	Mesh* _mesh;
	Texture2D* _texture;
	Material* _material;

	float _rotation;

public:
	// Constructors
	Cube();
	Cube(Mesh* mesh, Material* material, float x, float y, float z);

	// Destructor
	~Cube();

	// Gameloop Methods
	void Draw();
	void Update();

	// Setters
	void SetPosition(float x, float y, float z);
	void SetMesh(Mesh* mesh);
	void SetTexture(Texture2D* texture);
	void SetMaterial(Material* material);

	// Getters
	Vector3* GetPosition();
	Mesh* GetMesh();
	Material* GetMaterial();
	Texture2D* GetTexture();
};


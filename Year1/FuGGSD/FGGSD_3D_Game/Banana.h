#pragma once
#include "Headers_Structures.h"
#include "Texture2D.h"

class Banana
{
private:
	// Variables
	Vector3* _position;
	OBJMesh* _mesh;
	Texture2D* _texture;
	Material* _material;
	float _rotation;

public:
	// Constructors
	Banana();
	Banana(Mesh* mesh, float x, float y, float z);
	Banana(OBJMesh* mesh, Material* material, float x, float y, float z);

	// Destructors
	~Banana();

	// Gameloop Methods
	void Draw();
	void Update();

	// Setters
	void SetPosition(float x, float y, float z);
	void SetMaterial(Material* material);
	void SetTexture(Texture2D* texture);
	void SetMesh(OBJMesh* mesh);

	// Getters
	Vector3* GetPosition();
	Material* GetMaterial();
	Texture2D* GetTexture();
	OBJMesh* GetMesh();
};


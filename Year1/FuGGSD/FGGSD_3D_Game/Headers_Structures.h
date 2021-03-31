#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"

#include <vector>
#include <sstream>

using namespace std;

//Positional Structures
	struct Vector2{
		float x, y;
	};
	struct Vector3
	{
		float x, y, z;
	};
	struct Vector4{
		GLfloat x;
		GLfloat y;
		GLfloat z;
		GLfloat w;
	};

//File I/O Element Structures
	struct Colour{
		GLfloat r, g, b;
	};
	struct Vertex
	{
		GLfloat x;
		GLfloat y;
		GLfloat z;
	};
	struct TextureCoord{
		GLfloat u;
		GLfloat v;
	};

//3D Structures
	struct Camera
	{
		Vector3 eye;
		Vector3 centre;
		Vector3 up;
	};
	struct Mesh{
		Vertex* vertices;
		Vector3* normals;
		Colour* colours;
		TextureCoord* texCoords;
		GLushort* Indices;	

		int vertexCount;
		int normalCount;
		int colourCount;
		int texCoordsCount;
		int indexCount;
	};
	struct OBJMesh{
		vector<string> MeshNames;
		vector<vector<GLushort>> MeshIndices;
		vector<Vertex> Vertices;
		vector<Vector3> Normals;
		vector<TextureCoord> TexCoords;
	};
	struct Lighting
	{
		Vector4 ambient;
		Vector4 diffuse;
		Vector4 specular;
	};
	struct Material
	{
		Vector4 ambient;
		Vector4 diffuse;
		Vector4 specular;
		GLfloat shininess;
	};

#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"

#include "Headers_Structures.h"

class Texture2D
{
private:
	// Variables
	GLuint _ID;
	int _width;
	int _height;

public:
	// Constructor
	Texture2D();

	// Destructor
	~Texture2D();
	
	// Texture File Loading Methods
	bool LoadRAW(char* path, int width, int height);
	int LoadTGA(const char* textureFile);

	// Getters
	GLuint GetID() const;
	int GetWidth() const;
	int GetHeight() const;
};


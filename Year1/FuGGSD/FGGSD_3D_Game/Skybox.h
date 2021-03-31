#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "GL\freeglut.h"
#include "Headers_Structures.h"
#include "Texture2D.h"

class Skybox
{
private:
	//Textures
	Texture2D* _sbTexture;
public:
	//Constructor
	Skybox();

	//Destructor
	~Skybox();

	//Load Textures
	void LoadTextures();

	//Draws Skybox
	void DrawSkybox(float x, float y, float z, float width, float height, float length);
};
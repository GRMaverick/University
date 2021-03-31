#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include <string>

namespace String{
	//Sets 2D Projection
	void SetOrthographicProjection();
	//Renders Strings
	void RenderBitmapString(float x, float y, float z, void* font, char* string);
	//Restores 3D View
	void RestorePerspectiveProjection();
	//Exterior function call for String Rendering
	void RenderText(float x, float y, float z, void* font, char* text);
}



#include "String.h"

namespace String{
	//Sets 2D Projection
	void String::SetOrthographicProjection(){
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0, 1500, 0, 800);
			glScalef(1, -1, 1);
			glTranslatef(0, -800, 0);
			glMatrixMode(GL_MODELVIEW);
	}
	//Renders Strings
	void String::RenderBitmapString(float x, float y, float z, void* font, char* string){
			char *c;
			glRasterPos3f(x, y, z);
			for (c = string; *c != '\0'; c++) {
				glutBitmapCharacter(font, *c);
			}
	}
	//Restores 3D View
	void String::RestorePerspectiveProjection(){
			glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
	//Exterior function call for String Rendering
	void String::RenderText(float x, float y, float z, void* font, char* text){
		String::SetOrthographicProjection();
		glPushMatrix();
			glLoadIdentity();
			glDisable(GL_TEXTURE);
			glDisable(GL_LIGHTING);
			glColor3f(255.0f, 255.0f, 255.0f);
			String::RenderBitmapString(x, y, z, font, text);
			glEnable(GL_LIGHTING);
			glEnable(GL_TEXTURE);
		glPopMatrix();
		String::RestorePerspectiveProjection();
	}
}
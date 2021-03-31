#include "Skybox.h"

//Constructor
Skybox::Skybox()
{
	_sbTexture = new Texture2D[6];
	LoadTextures();
}

//Destructor
Skybox::~Skybox()
{
	for (int i = 0; i < 6; i++)
		delete &_sbTexture[i];
}

//Load Textures
void Skybox::LoadTextures(){
	_sbTexture[0].LoadRAW("Textures/Skybox/SkyboxFront.raw", 1024, 1024);
	_sbTexture[1].LoadRAW("Textures/Skybox/SkyboxBack.raw", 1024, 1024);
	_sbTexture[2].LoadRAW("Textures/Skybox/SkyboxLeft.raw", 1024, 1024);
	_sbTexture[3].LoadRAW("Textures/Skybox/SkyboxRight.raw", 1024, 1024);
	_sbTexture[4].LoadRAW("Textures/Skybox/SkyboxUp.raw", 1024, 1024);
	_sbTexture[5].LoadRAW("Textures/Skybox/SkyboxDown.raw", 1024, 1024);
}

//Draw Skybox
void Skybox::DrawSkybox(float x, float y, float z, float width, float height, float length)
{
	x = x - width / 2;
	y = y - height / 2;
	z = z - length / 2;

	glBindTexture(GL_TEXTURE_2D, _sbTexture[0].GetID());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x + width, y, z + length);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, _sbTexture[1].GetID());
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x, y, z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, _sbTexture[2].GetID());
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, y, z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, _sbTexture[3].GetID());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x + width, y + height, z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, _sbTexture[4].GetID());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x + width, y + height, z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x, y + height, z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, _sbTexture[5].GetID());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x + width, y, z);
	glEnd();
}
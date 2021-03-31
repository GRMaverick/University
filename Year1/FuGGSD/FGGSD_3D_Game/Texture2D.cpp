#include <fstream>
#include <iostream>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include <fstream>

#include "GL\freeglut.h"
#include "Texture2D.h"
#include "Headers_Structures.h"

using namespace std;

// Constructor
Texture2D::Texture2D()
{
}

// Destructor
Texture2D::~Texture2D()
{
}

// Texture File Loading Methods
bool Texture2D::LoadRAW(char* path, int width, int height)
{
	// Loads .RAW files
	char* tempTextureData;
	int fileSize;
	ifstream inFile;

	_width = width;
	_height = height;

	inFile.open(path, ios::binary);
	if (!inFile.good())
	{
		cerr << "Can't open texture file" << path << endl;
		return false;
	}

	inFile.seekg(0, ios::end);
	fileSize = (int)inFile.tellg();
	tempTextureData = new char[fileSize];
	inFile.seekg(0, ios::beg);
	inFile.read(tempTextureData, fileSize);
	inFile.close();

	glGenTextures(1, &_ID);
	glBindTexture(GL_TEXTURE_2D, _ID);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);

	delete[] tempTextureData;
	return true;
}
int Texture2D::LoadTGA(const char* textureFile)
{
	//Loads .TGA Files
	char* tempHeaderData = new char[18]; //18 Bytes is TGA Header Size
	char* tempTextureData;
	int fileSize;
	char type, pixelDepth, mode;

	ifstream inFile;

	inFile.open(textureFile, ios::binary);
	if (!inFile.good())
	{
		cerr << "Can't open texture file " << textureFile << endl;
		return -1;
	}

	//18 Bytes is the size of a TGA Header
	inFile.seekg(0, ios::beg); //Seek back to beginning of file
	inFile.read(tempHeaderData, 18); //Read in all the data in one go

	inFile.seekg(0, ios::end); //Seek to end of file
	fileSize = (int)inFile.tellg() - 1; //Get current position in file - The End, this gives us total file size
	tempTextureData = new char[fileSize]; //Create an new aray to store data
	inFile.seekg(18, ios::beg); //Seek back to beginning of file + 18
	inFile.read(tempTextureData, fileSize); //Read in all the data in one go
	inFile.close(); //Close the file

	type = tempHeaderData[2]; //Get TGA Type out of Header - Must be RGB for this to work
	_width = ((unsigned char)tempHeaderData[13] << 8u) + (unsigned char)tempHeaderData[12]; // Find the width (Combines two bytes into a short)
	_height = ((unsigned char)tempHeaderData[15] << 8u) + (unsigned char)tempHeaderData[14]; //Find the height
	pixelDepth = tempHeaderData[16]; // Find the pixel depth (24/32bpp)

	bool flipped = false;
	if ((int)((tempHeaderData[11] << 8) + tempHeaderData[10]) == 0)
		flipped = true;

	//We only support RGB type
	if (type == 2)
	{
		cout << textureFile << " loaded." << endl;

		glGenTextures(1, &_ID); //Get next Texture ID
		glBindTexture(GL_TEXTURE_2D, _ID); //Bind the texture to the ID

		mode = pixelDepth / 8;

		//Note that TGA files are stored as BGR(A) - So we need to specify the format as GL_BGR(A)_EXT
		if (mode == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, tempTextureData);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, tempTextureData);

		delete tempTextureData;
		delete tempHeaderData;
		return _ID;
	}
	return -1;
}

//Getters 
GLuint Texture2D::GetID() const
{
	//Returns Texture ID
	return _ID; 
}
int Texture2D::GetWidth() const
{
	//returns .RAW Width
	return _width; 
}
int Texture2D::GetHeight() const
{ 
	// Returns .RAW Height
	return _height; 
}

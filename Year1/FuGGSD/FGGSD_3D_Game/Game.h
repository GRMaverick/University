#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include <ctime>

#include "Banana.h"
#include "Callbacks.h"
#include "Cube.h"
#include "MeshLoader.h"
#include "Normandy.h"
#include "Skybox.h"
#include "String.h"
#include "SX1.h"
#include "SX3.h"
#include "Headers_Structures.h"

class Game
{
private:
	//Object Declarations
	Cube* _cube[60];
	Normandy* _normandy;
	SX1* _fighter1;
	SX3* _fighter2;
	Banana* _nanas[20];
	Skybox* _skybox;

	//Camera Declaration
	Camera* _cameraTP;
	Camera* _cameraFP;

	//Lighting Declarations
	Lighting* _lightingData;
	Vector4* _lightingPosition;

	//Material Declarations
	Material* _cubeMaterial;
	Material* _bananaMaterial;

	//Mesh Declarations
	Mesh* _cubeMesh;
	OBJMesh* _normandyMesh;
	OBJMesh* _fighterMesh1;
	OBJMesh* _fighterMesh2;
	OBJMesh* _bananaMesh;
	
	//Callback values for user-changes
	int _cameraValue;
	int _shipValue;

	//Ship-steadying booleans
	bool _sBool;
	bool _dBool;
	bool _aBool;
	bool _wBool;

public:
	//Constructor
	Game(int argc, char* argv[]);

	//Destructor
	~Game();

	//Initialisation Methods
	void InitialiseGL(int argc, char* argv[]);
	void InitialiseObjects();
	void InitialiseVariables();
	void InitialiseCamera();
	void InitialiseLighting();
	void InitialiseMaterials();
	void InitialiseMeshes();
	void InitialiseMenu();

	//Draw Methods
	void Draw();
	void DrawString();

	//Update Methods
	void Update();
	void UpdateLighting();
	void UpdateCamera(int value);
	void UpdateShip(int value);

	//Input Methods
	void Keyboard(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void PassiveMotion(int x, int y);
};


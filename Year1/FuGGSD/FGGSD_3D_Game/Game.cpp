#include "Headers_Structures.h"
#include "Game.h"

// Preprocessor commands
#define REFRESH_RATE 16
#define NULL_FLOAT 0.0f

// Constructor
Game::Game(int argc, char* argv[])
{
	//Creates random timing
	srand(time(NULL));
	//Initialises OpenGL/GLUT stuffs
	this->InitialiseGL(argc, argv);
	//Initialise Variables
	this->InitialiseVariables();
	// Object's Mesh Instantiations
	this->InitialiseMeshes();
	// Object's Material Instantiations
	this->InitialiseMaterials();
	//Initialises Objects
	this->InitialiseObjects();
	//Initialises Camera
	this->InitialiseCamera();
	//Initialises Lighting
	this->InitialiseLighting();
	//Starts Gameloop
	glutMainLoop();
}

// Destructor
Game::~Game()
{
	delete _cubeMesh;
	delete _normandyMesh;
	delete _fighterMesh1;
	delete _fighterMesh2;
	delete _bananaMesh;

	delete _cubeMaterial;
	delete _bananaMaterial;

	delete _cameraTP;
	delete _cameraFP;

	delete _lightingData;
	delete _lightingPosition;

	delete _normandy;
	delete _fighter1;
	delete _fighter2;

	delete _cube[0];
	for (int i = 0; i < 60; i++){
		delete _cube[i];
	}

	delete _nanas[0];
	for (int i = 0; i < 20; i++){
		delete _nanas[i];
	}
}

// Initialisation Methods
void Game::InitialiseGL(int argc, char* argv[])
{
	Callbacks::Init(this);
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(1500, 800);
		glutInitWindowPosition(0, 0);
		glutCreateWindow("FGGSD_3D_Game_Assignment_3");

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glutDisplayFunc(Callbacks::Display);
	glutTimerFunc(REFRESH_RATE, Callbacks::Timer, REFRESH_RATE);
	glutKeyboardFunc(Callbacks::Keyboard);
	glutKeyboardUpFunc(Callbacks::KeyboardUp);
	InitialiseMenu();
	
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0, 0, 800, 800);
		gluPerspective(45, 1, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
 
}
void Game::InitialiseObjects()
{
	// Object Instantiations
	_skybox = new Skybox();

	for (int i = 0; i < 60; i++)
		_cube[i] = new Cube(_cubeMesh, _cubeMaterial, (rand() % 40) - 20, (rand() % 60) - 15, (rand() % 400) - 200);
	for (int i = 0; i < 20; i++)
		_nanas[i] = new Banana(_bananaMesh, _bananaMaterial, (rand() % 40) - 20, (rand() % 60) - 15, (rand() % 400) - 200);

	_normandy = new Normandy(_normandyMesh);
	_fighter1 = new SX1(_fighterMesh1);
	_fighter2 = new SX3(_fighterMesh2);
}
void Game::InitialiseVariables(){
	_aBool = false;
	_sBool = false;
	_dBool = false;
	_wBool = false;
	_cameraValue = 1;
	_shipValue = 3;
}
void Game::InitialiseCamera()
{
	//Third Person Camera initialisation
	_cameraTP = new Camera();
	_cameraTP->eye.x = 0.0f;
	_cameraTP->eye.y = 0.0f;
	_cameraTP->eye.z = -200.0f;
	_cameraTP->centre.x = 0.0f;
	_cameraTP->centre.y = 0.0f;
	_cameraTP->centre.z = 0.0f;
	_cameraTP->up.x = 0.0f;
	_cameraTP->up.y = 1.0f;
	_cameraTP->up.z = 0.0f;

	_cameraFP = new Camera();
	_cameraFP->eye.x = _normandy->GetPostion()->x;
	_cameraFP->eye.y = _normandy->GetPostion()->y;
	_cameraFP->eye.z = _normandy->GetPostion()->z;
	_cameraFP->centre.x = 0.0f;
	_cameraFP->centre.y = 0.0f;
	_cameraFP->centre.z = 0.0f;
	_cameraFP->up.x = 0.0f;
	_cameraFP->up.y = 1.0f;
	_cameraFP->up.z = 0.0f;
}
void Game::InitialiseLighting()
{
	//Lighting Position Initialisation
	_lightingPosition = new Vector4();
		_lightingPosition->x = 0.0;
		_lightingPosition->y = 0.0;
		_lightingPosition->z = -175.0;
		_lightingPosition->w = 0.0;

	// Lighting settings initialisation
	_lightingData = new Lighting();
		_lightingData->ambient.x = 3.2f;
		_lightingData->ambient.y = 3.2f;
		_lightingData->ambient.z = 3.2f;
		_lightingData->ambient.w = 1.0f;
		_lightingData->diffuse.x = 0.8f;
		_lightingData->diffuse.y = 0.8f;
		_lightingData->diffuse.z = 0.8f;
		_lightingData->diffuse.w = 1.0f;
		_lightingData->specular.x = 0.2f;
		_lightingData->specular.y = 0.2f;
		_lightingData->specular.z = 0.2f;
		_lightingData->specular.w = 1.0f;
}
void Game::InitialiseMaterials(){

	//Cube Material Initialisation
	_cubeMaterial = new Material();
	_cubeMaterial->ambient.x = 0.8;
	_cubeMaterial->ambient.y = 0.05;
	_cubeMaterial->ambient.z = 0.05;
	_cubeMaterial->ambient.w = 1.0;
	_cubeMaterial->diffuse.x = 0.8;
	_cubeMaterial->diffuse.y = 0.05;
	_cubeMaterial->diffuse.z = 0.05;
	_cubeMaterial->diffuse.w = 1.0;
	_cubeMaterial->specular.x = 1.0;
	_cubeMaterial->specular.y = 1.0;
	_cubeMaterial->specular.z = 1.0;
	_cubeMaterial->specular.w = 1.0;
	_cubeMaterial->shininess = 100.0f;

	//Banana Material Initialisation
	_bananaMaterial = new Material();
	_bananaMaterial->ambient.x = 0.5;
	_bananaMaterial->ambient.y = 0.1;
	_bananaMaterial->ambient.z = 0.5;
	_bananaMaterial->ambient.w = 0.1;
	_bananaMaterial->diffuse.x = 0.1;
	_bananaMaterial->diffuse.y = 0.5;
	_bananaMaterial->diffuse.z = 0.1;
	_bananaMaterial->diffuse.w = 0.5;
	_bananaMaterial->specular.x = 0.1;
	_bananaMaterial->specular.y = 0.5;
	_bananaMaterial->specular.z = 0.1;
	_bananaMaterial->specular.w = 0.5;
	_bananaMaterial->shininess = 50.0f;
}
void Game::InitialiseMeshes(){

	//Object's Mesh Initialisation
	_cubeMesh = MeshLoader::LoadNormalsMesh("Models/cubethree.txt");
	_normandyMesh = OBJMeshLoader::Load("Models/SR-1.obj");
	_fighterMesh1 = OBJMeshLoader::Load("Models/SX-1.obj");
	_fighterMesh2 = OBJMeshLoader::Load("Models/SX-3.obj");
	_bananaMesh = OBJMeshLoader::Load("Models/banana.obj");
}
void Game::InitialiseMenu(){
	int shipMenu = glutCreateMenu(Callbacks::processMenu);
	glutAddMenuEntry("Normandy SR-1", 3);
	glutAddMenuEntry("SX-1 Fighter", 4);
	glutAddMenuEntry("SX-3 Fighter", 5);

	int cameraMenu = glutCreateMenu(Callbacks::processMenu);
	glutAddMenuEntry("Third-person", 1);
	glutAddMenuEntry("First-person", 2);

	int mainMenu = glutCreateMenu(Callbacks::processMenu);
	glutSetMenu(mainMenu);
	glutAddSubMenu("Cameras", cameraMenu);
	glutAddSubMenu("Ships", shipMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Draw Methods
void Game::Draw()
{
	//Clears scene
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draws skybox
	_skybox->DrawSkybox(0, 0, 0, 400, 400, 400);

	// Draws the Cubes
	for (int i = 0; i < 60; i++)
		_cube[i]->Draw();

	//Draws the Bananas
	for (int i = 0; i < 20; i++)
		_nanas[i]->Draw(); 

	//Checks which ship to draw
	if (_shipValue == 3)
		_normandy->Draw();
	if (_shipValue == 4)
		_fighter1->Draw();
	if (_shipValue == 5)
		_fighter2->Draw();

	//Drawing Text
	this->DrawString();

	//Flushes objects drawn to graphics card
	glFlush();
	
	//Swaps rear buffer and renders it on screen
	glutSwapBuffers();
}
void Game::DrawString(){
	String::RenderText(10, 20, 0, GLUT_BITMAP_HELVETICA_18, "Cube Dodge");
	String::RenderText(10, 50, 0, GLUT_BITMAP_HELVETICA_18, "Controls:");
	String::RenderText(10, 70, 0, GLUT_BITMAP_HELVETICA_18, "A - Left");
	String::RenderText(10, 90, 0, GLUT_BITMAP_HELVETICA_18, "S- Down");
	String::RenderText(10, 110, 0, GLUT_BITMAP_HELVETICA_18, "D - Right");
	String::RenderText(10, 130, 0, GLUT_BITMAP_HELVETICA_18, "W- Up");
	String::RenderText(10, 150, 0, GLUT_BITMAP_HELVETICA_18, "RMB - Menu");
	String::RenderText(10, 700, 0, GLUT_BITMAP_HELVETICA_18, "Access Menu to change:");
	String::RenderText(10, 720, 0, GLUT_BITMAP_HELVETICA_18, "Ships:");
	String::RenderText(10, 740, 0, GLUT_BITMAP_HELVETICA_18, "Cameras");
	String::RenderText(650, 660, 0, GLUT_BITMAP_HELVETICA_18, "DODGE THE CUBES!");
	String::RenderText(630, 700, 0, GLUT_BITMAP_HELVETICA_18, "CATCH PAUL'S BANANAS!");
}

// Update Methods
void Game::Update()
{
	//Resets ID Matrix
	glLoadIdentity();

	//Sets camera for viewing
	if (_cameraValue == 1)
		gluLookAt(_cameraTP->eye.x, _cameraTP->eye.y, _cameraTP->eye.z, _cameraTP->centre.x, _cameraTP->centre.y, _cameraTP->centre.z, _cameraTP->up.x, _cameraTP->up.y, _cameraTP->up.z);
	if (_cameraValue == 2)
		gluLookAt(_cameraFP->eye.x, _cameraFP->eye.y, _cameraFP->eye.z, _cameraFP->centre.x, _cameraFP->centre.y, _cameraFP->centre.z, _cameraFP->up.x, _cameraFP->up.y, _cameraFP->up.z);

	//Updates the Cubes
	for (int i = 0; i < 60; i++)
			_cube[i]->Update();

	//Updates the Bananas
	for (int i = 0; i < 20; i++)
		_nanas[i]->Update();

	if (_shipValue == 3)
		_normandy->Update();
	if (_shipValue == 4)
		_fighter1->Update();
	if (_shipValue == 5)
		_fighter2->Update();

	//Updates the lighting
	this->UpdateLighting();
	
	//Posts updates to screen
	glutPostRedisplay();
}
void Game::UpdateLighting(){
	// Update logic for lighting
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightingData->ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightingData->diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightingData->specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightingPosition->x));
}
void Game::UpdateCamera(int value){
	_cameraValue = value;
}
void Game::UpdateShip(int value){
	_shipValue = value;
}

// Input Method
void Game::Keyboard(unsigned char key, int x, int y)
{

	//Checks for user input and adjusts player position and camera
		if (key == 's'){
			_normandy->UpdateAngle(key);
			_fighter1->UpdateAngle(key);
			_fighter2->UpdateAngle(key);
			_normandy->GetPostion()->y -= 0.5f;
			_fighter1->GetPostion()->y -= 0.5f;
			_fighter2->GetPostion()->y -= 0.5f;
			_cameraTP->eye.y -= 0.5f;
			_cameraTP->centre.y -= 0.5f;
			_cameraFP->eye.y -= 0.5f;
			_cameraFP->centre.y -= 0.5f;
		}
		if (key == 'w'){
			_normandy->UpdateAngle(key);
			_fighter1->UpdateAngle(key);
			_fighter2->UpdateAngle(key);
			_normandy->GetPostion()->y += 0.5f;
			_fighter1->GetPostion()->y += 0.5f;
			_fighter2->GetPostion()->y += 0.5f;
			_cameraTP->eye.y += 0.5f;
			_cameraTP->centre.y += 0.5f;
			_cameraFP->eye.y += 0.5f;
			_cameraFP->centre.y += 0.5f;
		}
		if (key == 'd'){
			_normandy->UpdateAngle(key);
			_fighter1->UpdateAngle(key);
			_fighter2->UpdateAngle(key);
			_normandy->GetPostion()->x -= 0.5f;
			_fighter1->GetPostion()->x -= 0.5f;
			_fighter2->GetPostion()->x -= 0.5f;
			_cameraTP->eye.x -= 0.5f;
			_cameraTP->centre.x -= 0.5f;
			_cameraFP->eye.x -= 0.5f;
			_cameraFP->centre.x -= 0.5f;
		}
		if (key == 'a'){
			_normandy->UpdateAngle(key);
			_fighter1->UpdateAngle(key);
			_fighter2->UpdateAngle(key);
			_normandy->GetPostion()->x += 0.5f;
			_fighter1->GetPostion()->x += 0.5f;
			_fighter2->GetPostion()->x += 0.5f;
			_cameraTP->eye.x += 0.5f;
			_cameraTP->centre.x += 0.5f;
			_cameraFP->eye.x += 0.5f;
			_cameraFP->centre.x += 0.5f;
		}
}
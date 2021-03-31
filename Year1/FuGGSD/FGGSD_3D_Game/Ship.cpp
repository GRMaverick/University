#include "Ship.h"

// Constructors
Ship::Ship()
{
	//Empty constructor for dynamic construction of Ship object
	_mesh = nullptr;
	_texture = nullptr;
	_position = nullptr;

	_rotation = 0.0f;
}
Ship::Ship(OBJMesh* mesh, Material* material, float x, float y, float z){
	//Constructor to enable construction of ship object according to parameters
	_mesh = mesh;
	_texture = new Texture2D();
		_texture->LoadTGA("Textures/VEH_NOR_Diff_Stack_converted.tga");
	_position = new Vector3();
		_position->x = 0.0f;
		_position->y = -5.0f;
		_position->z = -175.0f;
}

// Destructors
Ship::~Ship()
{
	delete _mesh;
	delete _texture;
	delete _position;
}

// Gameloop Methods
void Ship::Draw(){
	//Draws ship
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(_position->x, _position->y, _position->z);
	if(_dBool && _key == 'd')
		glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
	else if(_aBool && _key == 'a')
		glRotatef(15.0f, 0.0f, 0.0f, -1.0f);
	else if(_wBool && _key == 'w')
		glRotatef(15.0f, -1.0f, 0.0f, 0.0f);
	else if(_sBool && _key == 's')
		glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
	else if (!_sBool && !_aBool && !_wBool && !_dBool)
		glRotatef(15.0f, 0.0f, 0.0f, 0.0f);

	glScalef(0.05f, 0.05f, 0.05);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	for (unsigned int i = 0; i < _mesh->MeshIndices.size(); i++)	{
		glVertexPointer(3, GL_FLOAT, 0, &_mesh->Vertices[0]);
		glNormalPointer(GL_FLOAT, 0, &_mesh->Normals[0]);
		glTexCoordPointer(2, GL_FLOAT, 0, &_mesh->TexCoords[0]);
		glDrawElements(GL_TRIANGLES, _mesh->MeshIndices[i].size(), GL_UNSIGNED_SHORT, &_mesh->MeshIndices[i][0]);
	}

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}
void Ship::Update(){
	//Updates ship
}
void Ship::UpdateAngle(char key){
	_key = key;
	if (key == 'a')
		_aBool = true;
	if (key == 's')
		_sBool = true;
	if (key == 'd')
		_dBool = true;
	if (key == 'w')
		_wBool = true;
}

// Getters
OBJMesh* Ship::GetMesh(){
	return _mesh;
}
Vector3* Ship::GetPostion(){
	return _position;
}

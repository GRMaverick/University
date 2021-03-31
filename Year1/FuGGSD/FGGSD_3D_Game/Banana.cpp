#include "Banana.h"

// Constructors
Banana::Banana(){
	//Empty constructor for dynamic construction of banana
	_mesh = nullptr;
	_position = nullptr;
	_texture = nullptr;
	_material = nullptr;
}
Banana::Banana(OBJMesh* mesh, Material* material, float x, float y, float z){
	// Constructor for construction of Banana objects according to parameters
	_mesh = mesh;
	_material = material;
	_texture = new Texture2D();
		_texture->LoadRAW("Textures/banana.raw", 512, 512);
	_position = new Vector3();
		_position->x = x;
		_position->y = y;
		_position->z = z;
}

// Destructor
Banana::~Banana()
{
	delete _mesh;
	delete _position;
	delete _texture;
	delete _material;
}

// Gameloop Methods
void Banana::Draw(){
	//Draws banana
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTranslatef(_position->x, _position->y, _position->z);
		glRotatef(_rotation, 1.0f, 1.0f, 1.0f);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		for (unsigned int i = 0; i < _mesh->MeshIndices.size(); i++)	{
			glVertexPointer(3, GL_FLOAT, 0, &_mesh->Vertices[0]);
			glNormalPointer(GL_FLOAT, 0, &_mesh->Normals[0]);
			glTexCoordPointer(2, GL_FLOAT, 0, &_mesh->TexCoords[0]);
			glDrawElements(GL_TRIANGLES, _mesh->MeshIndices[i].size(), GL_UNSIGNED_SHORT, &_mesh->MeshIndices[i][0]);

			glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->ambient.x));
			glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->diffuse.x));
			glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->specular.x));
			glMaterialfv(GL_FRONT, GL_SHININESS, &(_material->shininess));
		}

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}
void Banana::Update(){
	//Updates banana
	_rotation += 3.0f;
	_position->z -= 0.5f;

	if (_position->z == -200.0f){
		SetPosition((rand() % 40) - 20, (rand() % 60) - 15, (rand() % 400) - 200);
		while (!_position->z < -5.0f){
			SetPosition((rand() % 40) - 20, (rand() % 60) - 15, (rand() % 400) - 200);
		}
	}
}

// Setters
void Banana::SetPosition(float x, float y, float z){
	//Sets position
	_position->x = x;
	_position->y = y;
	_position->z = z;
}
void Banana::SetMaterial(Material* material){
	//Sets material
	_material = material;
}
void Banana::SetTexture(Texture2D* texture){
	//Sets texture
	_texture = texture;
}
void Banana::SetMesh(OBJMesh* mesh){
	//Sets mesh
	_mesh = mesh;
}

// Getters
Vector3* Banana::GetPosition(){
	//Gets position
	return _position;
}
OBJMesh* Banana::GetMesh(){
	return _mesh;
}
Material* Banana::GetMaterial(){
	return _material;
}
Texture2D* Banana::GetTexture(){
	return _texture;
}
#include "Cube.h"

// Constructors
Cube::Cube(){
	//Empty constructor for dynamic construction of Cube objects
	_mesh = nullptr;
	_material = nullptr;
	_texture = nullptr;
	_position = nullptr;
}
Cube::Cube(Mesh* mesh, Material* material, float x, float y, float z)
{
	// Constructor for construction of Cube objects according to parameters
	_mesh = mesh;
	_material = material;
	_texture = new Texture2D();
		_texture->LoadRAW("Textures/stars.raw", 512, 512);
	_position = new Vector3();
		_position->x = x;
		_position->y = y;
		_position->z = z;
	_rotation = 0.0f;
}

// Destructors 
Cube::~Cube()
{
	delete _position;
	delete _mesh;
	delete _material;
	delete _texture;
}

// Gameloop Methods
void Cube::Draw(){
	//Draws Cubes
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTranslatef(_position->x, _position->y, _position->z);
	glRotatef(_rotation, 1.0f, 2.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < _mesh->indexCount; i++)
	{
		glNormal3f(_mesh->normals[_mesh->Indices[i]].x,	_mesh->normals[_mesh->Indices[i]].y,	_mesh->normals[_mesh->Indices[i]].z);
		glTexCoord2f(_mesh->texCoords[_mesh->Indices[i]].u,	_mesh->texCoords[_mesh->Indices[i]].v);
		glVertex3f(_mesh->vertices[_mesh->Indices[i]].x,	 _mesh->vertices[_mesh->Indices[i]].y,	_mesh->vertices[_mesh->Indices[i]].z);

		glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->ambient.x));
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->diffuse.x));
		glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->specular.x));
		glMaterialfv(GL_FRONT, GL_SHININESS, &(_material->shininess));
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, -1);
	glPopMatrix();
}
void Cube::Update(){
	//Updates bananas
	_rotation += 1.0f;
	_position->z -= 0.5f;

	if (_position->z == -200.0f)
		SetPosition((rand() % 40) - 20, (rand() % 60) - 15, (rand() % 400) - 100);
}

// Setters
void Cube::SetPosition(float x, float y, float z){
	//Sets position
	_position->x = x;
	_position->y = y;
	_position->z = z;
}
void Cube::SetMesh(Mesh* mesh){
	//Sets mesh
	_mesh = mesh;
}
void Cube::SetMaterial(Material* material){
	//Sets material
	_material = material;
}
void Cube::SetTexture(Texture2D* texture){
	//Sets Texture
	_texture = texture;
}

// Getters 
Vector3* Cube::GetPosition(){
	//Gets position
	return _position;
}
Mesh* Cube::GetMesh(){
	return _mesh;
}
Material* Cube::GetMaterial(){
	return _material;
}
Texture2D* Cube::GetTexture(){
	return _texture;
}
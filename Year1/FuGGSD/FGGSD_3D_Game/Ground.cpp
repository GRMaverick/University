#include "Ground.h"


Ground::Ground(OBJMesh* mesh) : Level(mesh)
{
	_mesh = mesh;
	_position = new Vector3();
}
Ground::~Ground()
{
	delete _mesh;
	delete _position;
}

void Ground::Draw()
{

}
void Ground::Update()
{

}
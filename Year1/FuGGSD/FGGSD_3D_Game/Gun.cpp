#include "Gun.h"

Gun::Gun(OBJMesh* mesh)  : GameObjects(mesh)
{
	_mesh = mesh;
	_position = new Vector3();
}
Gun::~Gun()
{
	delete _mesh;
	delete _position;
}

void Gun::Draw()
{

}
void Gun::Update()
{

}
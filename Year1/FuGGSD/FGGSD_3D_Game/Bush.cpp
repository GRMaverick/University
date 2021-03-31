#include "Bush.h"

Bush::Bush(OBJMesh* mesh) : Level(mesh)
{
	_mesh = mesh;
	_position = new Vector3();
}
Bush::~Bush()
{
	delete _mesh;
	delete _position;
}

void Bush::Draw()
{

}
void Bush::Update()
{

}

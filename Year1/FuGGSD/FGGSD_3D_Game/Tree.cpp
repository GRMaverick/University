#include "Tree.h"


Tree::Tree(OBJMesh* mesh) : Level(mesh)
{
	_mesh = mesh;
	_position = new Vector3();
}
Tree::~Tree()
{
	delete _mesh;
	delete _position;
}

void Tree::Draw()
{

}
void Tree::Update()
{

}
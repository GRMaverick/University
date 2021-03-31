#include "Projectile.h"

Projectile::Projectile(OBJMesh* mesh) : GameObjects(mesh)
{
	_mesh = mesh;
	_position = new Vector3();
}
Projectile::~Projectile()
{
	delete _mesh;
	delete _position;
}

void Projectile::Draw()
{

}
void Projectile::Update()
{

}
void Projectile::Trajectory()
{

}
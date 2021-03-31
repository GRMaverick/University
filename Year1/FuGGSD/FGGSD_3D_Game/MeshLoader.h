#pragma once
#include "Headers_Structures.h"

namespace MeshLoader {

	// Mesh Loading Method Signature Declarations
	Mesh* LoadNormalsMesh(char* path);
	Mesh* LoadTextureMesh(char* path);
	Mesh* LoadColoursMesh(char* path);
}
namespace OBJMeshLoader{

	// OBJ File Method Signature Declarations
	OBJMesh* Load(char* path);
}

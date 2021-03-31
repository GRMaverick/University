#pragma once
#include "Headers_Structures.h"

class GameObjects
{
public:
	// === Constructors === //
	GameObjects();
	GameObjects(OBJMesh* mesh);

	// === Destructors === //
	~GameObjects();

	// === Game-loop Methods === //
	void virtual Update() = 0;
	void virtual Draw() = 0;
};


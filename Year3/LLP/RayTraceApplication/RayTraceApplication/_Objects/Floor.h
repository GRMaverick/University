#pragma once

#include "Vector3.h"

class MemoryPool;

class Floor
{
public:
	float Mass;
	Vector3 Center;
	Vector3 Extents;

	Floor(void);
	Floor(Vector3 center, Vector3 extents, float mass);
	~Floor(void);
	
	void* operator new(size_t size);
	void operator delete(void* pMemory);

	static MemoryPool* MemoryPool;
private:
};
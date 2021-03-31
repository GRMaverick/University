#pragma once
#include "Vector3.h"

class MemoryPool;

class BoundingSphere
{
public:
	float Radius;
	Vector3 Centre;

	BoundingSphere(void);
	BoundingSphere(Vector3 centre, float radius);

	static void* operator new(size_t size);
	static void operator delete(void* pMemory);

	bool Contains(Vector3& point);
	bool Intersects(BoundingSphere* sphere);

	static MemoryPool* MemoryPool;
};
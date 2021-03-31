#pragma once
#include "Vector3.h"

class MemoryPool;
class BoundingSphere;

class BoundingBox
{
public:
	Vector3 Min;
	Vector3 Max;
	Vector3 Centre;

	BoundingBox(void);
	BoundingBox(Vector3& centre, Vector3& extents);

	static void* operator new(size_t size);
	static void operator delete(void* pMemory);

	bool Contains(Vector3& point);
	bool Contains(BoundingSphere* sphere);

	static MemoryPool* MemoryPool;
};
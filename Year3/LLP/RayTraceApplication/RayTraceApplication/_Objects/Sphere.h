#pragma once

#include "Vector3.h"
#include "MemoryPool.h"

class BoundingSphere;

class Sphere
{
public:
	Vector3 Center;
	Vector3 Velocity;
	Vector3 SurfaceColor;
	Vector3 EmissionColor;

	float Mass;
	float Radius;
	float CoefRest;
	float Reflection;
	float Transparency;
	float RadiusSquared;

	BoundingSphere* BoundingVolume;

	Sphere(const Vector3 &c, const float &r, const Vector3 &sc, const float &refl = 0, const float &transp = 0, const Vector3 &ec = 0, const float& mass = 1.0f, const float& coefRest = 0.5f);
	~Sphere(void);

	void* operator new(size_t size);
	void operator delete(void* pMemory);

	bool Intersect(const Vector3 &rayorig, const Vector3 &raydir, float &t0, float &t1) const;

	static MemoryPool* MemoryPool;
};
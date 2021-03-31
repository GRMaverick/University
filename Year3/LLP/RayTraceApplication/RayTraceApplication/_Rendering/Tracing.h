#pragma once

#include <vector>

#include "Vector3.h"
#include "Sphere.h"

class Tracing
{
public:
	static Vector3 BaselineTrace(const Vector3 &rayorig, const Vector3 &raydir, const std::vector<Sphere> &spheres, const int &depth); 
	static Vector3 Trace(const Vector3 &rayorig, const Vector3 &raydir, const std::vector<Sphere*> &spheres, const int &depth);
	static Vector3 Trace(const Vector3 &rayorig, const Vector3 &raydir, Sphere* spheres[], int sphereCount, const int &depth, int& iteration);
};
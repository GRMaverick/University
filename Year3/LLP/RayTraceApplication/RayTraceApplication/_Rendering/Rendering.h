#pragma once

#include <map>
#include <vector>
#include <thread>

class Sphere;

class Renderer
{
public:
	static void Initialise(void);
	static void Shutdown(void);

	static void BaselineRender(const std::vector<Sphere>& spheres, int iteration);
	static void Render(Sphere* spheres[], int sphereCount, int iteration);

	static void ParallelRender(Sphere* spheres[], int sphereCount, int iteration, int threads);

private:
	static float Angle;
	static float FieldOfView;
	static float AspectRatio;
	static float InverseWidth;
	static float InverseHeight;

	static void RenderThread(int threadID, int start, int end, Vector3* pixel, Sphere* spheres[], int sphereCount, int iteration);
};
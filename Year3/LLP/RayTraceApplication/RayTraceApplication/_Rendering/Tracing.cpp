#include <vector>
#include <algorithm>

#include "Tracing.h"
#include "Defines.h"

#include "BoundingSphere.h"
#include "MethodProfiler.h"

#include "RTAParameters.h"


float Mix(const float &a, const float &b, const float &mix)
{
	return b * mix + a * (1 - mix);
}

Vector3 Tracing::BaselineTrace(const Vector3 &rayorig, const Vector3 &raydir, const std::vector<Sphere> &spheres, const int &depth)
{
	float tnear = INFINITY;
	const Sphere* sphere = NULL;

	// find intersection of this ray with the sphere in the scene
	for (unsigned i = 0; i < spheres.size(); ++i)
	{
		float t0 = INFINITY, t1 = INFINITY;
		if (spheres[i].Intersect(rayorig, raydir, t0, t1))
		{
			if (t0 < 0)
				t0 = t1;

			if (t0 < tnear)
			{
				tnear = t0;
				sphere = &spheres[i];
			}
		}
	}

	// if there's no intersection return black or background color
	if (!sphere)
		return Vector3(2);
	Vector3 surfaceColor = 0; // color of the ray/surfaceof the object intersected by the ray
	Vector3 phit = rayorig + raydir * tnear; // point of intersection
	Vector3 nhit = phit - sphere->Center; // normal at the intersection point
	nhit.Normalise(); // Normalise normal direction
					  // If the normal and the view direction are not opposite to each other
					  // reverse the normal direction. That also means we are inside the sphere so set
					  // the inside bool to true. Finally reverse the sign of IDotN which we want
					  // positive.
	float bias = 1e-4; // add some bias to the point from which we will be tracing
	bool inside = false;

	if (raydir.Dot(nhit) > 0)
		nhit = -nhit, inside = true;

	if ((sphere->Transparency > 0 || sphere->Reflection > 0) && depth < MAX_RAY_DEPTH)
	{
		float facingratio = -raydir.Dot(nhit);

		// change the mix value to tweak the effect
		float fresneleffect = Mix(pow(1 - facingratio, 3), 1, 0.1);

		// compute reflection direction (not need to Normalise because all vectors
		// are already Normalised)
		Vector3 refldir = raydir - nhit * 2 * raydir.Dot(nhit);
		refldir.Normalise();
		Vector3 reflection = BaselineTrace(phit + nhit * bias, refldir, spheres, depth + 1);
		Vector3 refraction = 0;

		// if the sphere is also transparent compute refraction ray (transmission)
		if (sphere->Transparency)
		{
			float ior = 1.1;
			float eta = (inside) ? ior : 1 / ior; // are we inside or outside the surface?
			float cosi = -nhit.Dot(raydir);
			float k = 1 - eta * eta * (1 - cosi * cosi);
			Vector3 refrdir = raydir * eta + nhit * (eta *  cosi - sqrt(k));
			refrdir.Normalise();
			refraction = BaselineTrace(phit - nhit * bias, refrdir, spheres, depth + 1);
		}

		// the result is a mix of reflection and refraction (if the sphere is transparent)
		surfaceColor = (reflection * fresneleffect + refraction * (1 - fresneleffect) * sphere->Transparency) * sphere->SurfaceColor;
	}
	else
	{
		// it's a diffuse object, no need to raytrace any further
		for (unsigned i = 0; i < spheres.size(); ++i)
		{
			if (spheres[i].EmissionColor.x > 0)
			{
				// this is a light
				Vector3 transmission = 1;
				Vector3 lightDirection = spheres[i].Center - phit;
				lightDirection.Normalise();
				for (unsigned j = 0; j < spheres.size(); ++j)
				{
					if (i != j)
					{
						float t0, t1;
						if (spheres[j].Intersect(phit + nhit * bias, lightDirection, t0, t1))
						{
							transmission = 0;
							break;
						}
					}
				}
				surfaceColor += sphere->SurfaceColor * transmission * std::max(float(0), nhit.Dot(lightDirection)) * spheres[i].EmissionColor;
			}
		}
	}

	return surfaceColor + sphere->EmissionColor;
}
Vector3 Tracing::Trace(const Vector3 &rayorig, const Vector3 &raydir, const std::vector<Sphere*> &spheres, const int &depth)
{
	float tnear = INFINITY;
	const Sphere* sphere = NULL;

	// find intersection of this ray with the sphere in the scene
	for (unsigned i = 0; i < spheres.size(); ++i)
	{
		float t0 = INFINITY, t1 = INFINITY;
		if (spheres[i]->Intersect(rayorig, raydir, t0, t1))
		{
			if (t0 < 0)
				t0 = t1;

			if (t0 < tnear)
			{
				tnear = t0;
				sphere = spheres[i];
			}
		}
	}

	// if there's no intersection return black or background color
	if (!sphere)
		return Vector3(2);
	Vector3 surfaceColor = 0; // color of the ray/surfaceof the object intersected by the ray
	Vector3 phit = rayorig + raydir * tnear; // point of intersection
	Vector3 nhit = phit - sphere->Center; // normal at the intersection point
	nhit.Normalise(); // Normalise normal direction
					  // If the normal and the view direction are not opposite to each other
					  // reverse the normal direction. That also means we are inside the sphere so set
					  // the inside bool to true. Finally reverse the sign of IDotN which we want
					  // positive.
	float bias = 1e-4; // add some bias to the point from which we will be tracing
	bool inside = false;

	if (raydir.Dot(nhit) > 0)
		nhit = -nhit, inside = true;

	if ((sphere->Transparency > 0 || sphere->Reflection > 0) && depth < MAX_RAY_DEPTH)
	{
		float facingratio = -raydir.Dot(nhit);

		// change the mix value to tweak the effect
		float fresneleffect = Mix(pow(1 - facingratio, 3), 1, 0.1);

		// compute reflection direction (not need to Normalise because all vectors
		// are already Normalised)
		Vector3 refldir = raydir - nhit * 2 * raydir.Dot(nhit);
		refldir.Normalise();
		Vector3 reflection = Trace(phit + nhit * bias, refldir, spheres, depth + 1);
		Vector3 refraction = 0;

		// if the sphere is also transparent compute refraction ray (transmission)
		if (sphere->Transparency)
		{
			float ior = 1.1;
			float eta = (inside) ? ior : 1 / ior; // are we inside or outside the surface?
			float cosi = -nhit.Dot(raydir);
			float k = 1 - eta * eta * (1 - cosi * cosi);
			Vector3 refrdir = raydir * eta + nhit * (eta *  cosi - sqrt(k));
			refrdir.Normalise();
			refraction = Trace(phit - nhit * bias, refrdir, spheres, depth + 1);
		}

		// the result is a mix of reflection and refraction (if the sphere is transparent)
		surfaceColor = (reflection * fresneleffect + refraction * (1 - fresneleffect) * sphere->Transparency) * sphere->SurfaceColor;
	}
	else
	{
		// it's a diffuse object, no need to raytrace any further
		for (unsigned i = 0; i < spheres.size(); ++i)
		{
			if (spheres[i]->EmissionColor.x > 0)
			{
				// this is a light
				Vector3 transmission = 1;
				Vector3 lightDirection = spheres[i]->Center - phit;
				lightDirection.Normalise();
				for (unsigned j = 0; j < spheres.size(); ++j)
				{
					if (i != j)
					{
						float t0, t1;
						if (spheres[j]->Intersect(phit + nhit * bias, lightDirection, t0, t1))
						{
							transmission = 0;
							break;
						}
					}
				}
				surfaceColor += sphere->SurfaceColor * transmission * std::max(float(0), nhit.Dot(lightDirection)) * spheres[i]->EmissionColor;
			}
		}
	}

	return surfaceColor + sphere->EmissionColor;
}
Vector3 Tracing::Trace(const Vector3 &rayorig, const Vector3 &raydir, Sphere* spheres[], int sphereCount, const int &depth, int& iteration)
{
	const Sphere* sphere = NULL;
	Vector3 surfaceColor = 0; // color of the ray/surfaceof the object intersected by the ray

	if (RTAParameters::MethodProfiling)
		MethodProfiler::StartTracking(std::string(__FUNCTION__), std::string("Trace_" + std::to_string(depth)), iteration);

	{
		float tnear = INFINITY;

		// find intersection of this ray with the sphere in the scene

		for (unsigned i = 0; i < sphereCount; ++i)
		{
			float t0 = INFINITY;
			float t1 = INFINITY;
			if (spheres[i]->Intersect(rayorig, raydir, t0, t1))
			{
				if (t0 < 0)
					t0 = t1;

				if (t0 < tnear)
				{
					tnear = t0;
					sphere = spheres[i];
				}
			}
		}

		// if there's no intersection return black or background color
		if (!sphere)
			return Vector3(2);

		Vector3 phit = rayorig + raydir * tnear; // point of intersection
		Vector3 nhit = phit - sphere->Center; // normal at the intersection point
		nhit.Normalise(); // Normalise normal direction
						  // If the normal and the view direction are not opposite to each other
						  // reverse the normal direction. That also means we are inside the sphere so set
						  // the inside bool to true. Finally reverse the sign of IDotN which we want
						  // positive.
		float bias = 1e-4; // add some bias to the point from which we will be tracing
		bool inside = false;

		if (raydir.Dot(nhit) > 0)
			nhit = -nhit, inside = true;

		if ((sphere->Transparency > 0 || sphere->Reflection > 0) && depth < MAX_RAY_DEPTH)
		{
			float facingratio = -raydir.Dot(nhit);

			// change the mix value to tweak the effect
			float fresneleffect = Mix(pow(1 - facingratio, 3), 1, 0.1);

			// compute reflection direction (not need to Normalise because all vectors
			// are already Normalised)
			Vector3 refldir = raydir - nhit * 2 * raydir.Dot(nhit);
			refldir.Normalise();
			Vector3 reflection = Trace(phit + nhit * bias, refldir, spheres, sphereCount, depth + 1, iteration);
			Vector3 refraction = 0;

			// if the sphere is also transparent compute refraction ray (transmission)
			if (sphere->Transparency)
			{
				float ior = 1.1;
				float eta = (inside) ? ior : 1 / ior; // are we inside or outside the surface?
				float cosi = -nhit.Dot(raydir);
				float k = 1 - eta * eta * (1 - cosi * cosi);
				Vector3 refrdir = raydir * eta + nhit * (eta *  cosi - sqrt(k));
				refrdir.Normalise();
				refraction = Trace(phit - nhit * bias, refrdir, spheres, sphereCount, depth + 1, iteration);
			}

			// the result is a mix of reflection and refraction (if the sphere is transparent)
			surfaceColor = (reflection * fresneleffect + refraction * (1 - fresneleffect) * sphere->Transparency) * sphere->SurfaceColor;
		}
		else
		{
			// it's a diffuse object, no need to raytrace any further
			for (unsigned i = 0; i < sphereCount; ++i)
			{
				if (spheres[i]->EmissionColor.x > 0)
				{
					// this is a light
					Vector3 transmission = 1;
					Vector3 lightDirection = spheres[i]->Center - phit;
					lightDirection.Normalise();
					for (unsigned j = 0; j < sphereCount; ++j)
					{
						if (i != j)
						{
							float t0, t1;
							if (spheres[i]->Intersect(phit + nhit * bias, lightDirection, t0, t1))
							{
								transmission = 0;
								break;
							}
						}
					}
					surfaceColor += sphere->SurfaceColor * transmission * std::max(float(0), nhit.Dot(lightDirection)) * spheres[i]->EmissionColor;
				}
			}
		}
	}

	if (RTAParameters::MethodProfiling)
		MethodProfiler::EndTracking(std::string(__FUNCTION__), std::string("Trace_" + std::to_string(depth)));

	return surfaceColor + sphere->EmissionColor;
}
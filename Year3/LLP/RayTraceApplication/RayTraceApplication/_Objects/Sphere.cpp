#include <assert.h>

#include "Sphere.h"
#include "BoundingSphere.h"
#include "AllocationHeader.h"
#include "MemoryPoolManager.h"

MemoryPool* Sphere::MemoryPool = nullptr;

Sphere::Sphere(const Vector3& center, const float& radius, const Vector3& surfaceColor, const float& reflection, const float& transparency, const Vector3& emissionColor, const float& mass, const float& coefRest)
{
	Mass = mass;
	Center = center;
	Radius = radius;
	CoefRest = coefRest;
	Reflection = reflection;
	SurfaceColor = surfaceColor;
	Transparency = transparency;
	EmissionColor = emissionColor;
	RadiusSquared = Radius * Radius;

	//BoundingVolume = new BoundingSphere(Center, Radius + 1.0f);

	Velocity = Vector3(0);
}
Sphere::~Sphere(void)
{
	//if(BoundingVolume) delete BoundingVolume;
}

void* Sphere::operator new(size_t size)
{
	if (!MemoryPool)
		MemoryPool = MemoryPoolManager::Instance()->GetMemoryPool("Sphere", 100, size + sizeof(AllocationHeader) + sizeof(int));

	char* pMeme = (char*)MemoryPool->Allocate();
	AllocationHeader* pHeader = (AllocationHeader*)pMeme;

	pHeader->Signature = SIGNATURE_START;
	pHeader->Size = size;

	void* pStartMemeBlock = pMeme + sizeof(AllocationHeader);

	int* pEndMarker = (int*)((char*)pStartMemeBlock + size);
	*pEndMarker = SIGNATURE_END;

	return pStartMemeBlock;
}
void Sphere::operator delete(void* pMemory)
{
	AllocationHeader* pHeader = (AllocationHeader*)((char*)pMemory - sizeof(AllocationHeader));

	assert(pHeader->Signature == SIGNATURE_START);

	int* pEndMarker = (int*)((char*)pMemory + pHeader->Size);

	assert(*pEndMarker == SIGNATURE_END);

	MemoryPool->Free(pHeader);
}

bool Sphere::Intersect(const Vector3& rayOrigin, const Vector3& rayDirection, float& t0, float& t1) const
{
	Vector3 l = Center - rayOrigin;

	float tca = l.Dot(rayDirection);
	if (tca < 0)
		return false;

	float d2 = l.Dot(l) - tca * tca;
	if (d2 > RadiusSquared)
		return false;

	float thc = sqrt(RadiusSquared - d2);

	t0 = tca - thc;
	t1 = tca + thc;

	return true;
}
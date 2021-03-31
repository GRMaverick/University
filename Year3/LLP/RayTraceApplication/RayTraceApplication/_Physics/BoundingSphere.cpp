#include <assert.h>

#include "BoundingSphere.h"

#include "AllocationHeader.h"
#include "MemoryPool.h"
#include "MemoryPoolManager.h"

MemoryPool* BoundingSphere::MemoryPool = nullptr;

BoundingSphere::BoundingSphere(void)
{
	Radius = 0.0f;
	Centre = Vector3(0.0f);
}
BoundingSphere::BoundingSphere(Vector3 centre, float radius)
{
	Radius = radius;
	Centre = centre;
}

void* BoundingSphere::operator new(size_t size)
{
	if (!MemoryPool)
		MemoryPool = MemoryPoolManager::Instance()->GetMemoryPool("Bounding Sphere", 100, size + sizeof(AllocationHeader) + sizeof(int));

	char* pMeme = (char*)MemoryPool->Allocate();
	AllocationHeader* pHeader = (AllocationHeader*)pMeme;

	pHeader->Signature = SIGNATURE_START;
	pHeader->Size = size;

	void* pStartMemeBlock = pMeme + sizeof(AllocationHeader);

	int* pEndMarker = (int*)((char*)pStartMemeBlock + size);
	*pEndMarker = SIGNATURE_END;

	return pStartMemeBlock;
}
void BoundingSphere::operator delete(void* pMemory)
{
	AllocationHeader* pHeader = (AllocationHeader*)((char*)pMemory - sizeof(AllocationHeader));

	assert(pHeader->Signature == SIGNATURE_START);

	int* pEndMarker = (int*)((char*)pMemory + pHeader->Size);

	assert(*pEndMarker == SIGNATURE_END);

	MemoryPool->Free(pHeader);
}

bool BoundingSphere::Contains(Vector3& point)
{
	return ((point - Centre).Length() < Radius);
}
bool BoundingSphere::Intersects(BoundingSphere* sphere)
{
	return ((Centre + sphere->Centre).Length() < (Radius + sphere->Radius));
}
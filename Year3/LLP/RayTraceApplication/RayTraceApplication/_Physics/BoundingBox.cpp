#include <assert.h>

#include "BoundingBox.h"
#include "BoundingSphere.h"

#include "AllocationHeader.h"
#include "MemoryPool.h"
#include "MemoryPoolManager.h"

MemoryPool* BoundingBox::MemoryPool = nullptr;

BoundingBox::BoundingBox(void)
{
	Min = Vector3(0.0f);
	Max = Vector3(0.0f);
	Centre = Vector3(0.0f);
}
BoundingBox::BoundingBox(Vector3& centre, Vector3& extents)
{
	Centre = centre;
	Min = Centre - (extents / 2);
	Max = Centre + (extents / 2);
}

void* BoundingBox::operator new(size_t size)
{
	if (!MemoryPool)
		MemoryPool = MemoryPoolManager::Instance()->GetMemoryPool("Bounding Box", 100, size + sizeof(AllocationHeader) + sizeof(int));

	char* pMeme = (char*)MemoryPool->Allocate();
	AllocationHeader* pHeader = (AllocationHeader*)pMeme;

	pHeader->Signature = SIGNATURE_START;
	pHeader->Size = size;

	void* pStartMemeBlock = pMeme + sizeof(AllocationHeader);

	int* pEndMarker = (int*)((char*)pStartMemeBlock + size);
	*pEndMarker = SIGNATURE_END;

	return pStartMemeBlock;
}
void BoundingBox::operator delete(void* pMemory)
{
	AllocationHeader* pHeader = (AllocationHeader*)((char*)pMemory - sizeof(AllocationHeader));

	assert(pHeader->Signature == SIGNATURE_START);

	int* pEndMarker = (int*)((char*)pMemory + pHeader->Size);

	assert(*pEndMarker == SIGNATURE_END);

	MemoryPool->Free(pHeader);
}

bool BoundingBox::Contains(Vector3& point) 
{
	bool result;
	result &= (point.x > Min.x && point.x < Max.x);
	result &= (point.y > Min.y && point.y < Max.y);
	result &= (point.z > Min.z && point.z < Max.z);
	return result;
}
bool BoundingBox::Contains(BoundingSphere* sphere)
{
	bool result = true;
	result &= ((sphere->Centre.x + sphere->Radius) >= Min.x) && ((sphere->Centre.x - sphere->Radius) <= Max.x);
	result &= ((sphere->Centre.y + sphere->Radius) >= Min.y) && ((sphere->Centre.y - sphere->Radius) <= Max.y);
	result &= ((sphere->Centre.z + sphere->Radius) >= Min.z) && ((sphere->Centre.z - sphere->Radius) <= Max.z);
	return result;
}
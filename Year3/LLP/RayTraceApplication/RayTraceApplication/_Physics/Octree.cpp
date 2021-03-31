#include <assert.h>

#include "Octree.h"

#include "AllocationHeader.h"
#include "MemoryPool.h"
#include "MemoryPoolManager.h"

//
// IF THERE ARE COLLISION PROBLEMS
// CREATE SPHERE CENTRE + RADIUS IS
// WITHIN THE BOUNDING VOLUMES OF THE OCTREE
//

bool						Octree::m_TreeBuilt = false;
bool						Octree::m_TreeReady = false;
MemoryPool*		Octree::MemoryPool = nullptr;

Octree::Octree(void)
{
	m_Region = new BoundingBox(Vector3(0.0f), Vector3(0.0f));

	m_Parent = nullptr;
	m_Spheres.clear();

	m_TreeBuilt = false;
	m_TreeReady = false;

	m_CurrentLife = -1;
	m_MaxLifespan = 8;
	m_ActiveNodeMask = 0x00;

	for (int i = 0; i < 8; i++)
	{
		m_Children[i] = nullptr;
	}
}
Octree::Octree(BoundingBox* bBox, std::vector<Sphere*> spheres)
{
	m_Region = bBox;

	m_Parent = nullptr;
	m_Spheres = spheres;

	m_TreeBuilt = false;
	m_TreeReady = false;

	m_CurrentLife = -1;
	m_MaxLifespan = 8;
	m_ActiveNodeMask = 0x00;

	for (int i = 0; i < 8; i++)
	{
		m_Children[i] = nullptr;
	}
}
Octree::~Octree(void)
{
	if (m_Children[0]) delete	m_Children[0];
	if (m_Children[1]) delete	m_Children[1];
	if (m_Children[2]) delete	m_Children[2];
	if (m_Children[3]) delete	m_Children[3];
	if (m_Children[4]) delete	m_Children[4];
	if (m_Children[5]) delete	m_Children[5];
	if (m_Children[6]) delete	m_Children[6];
	if (m_Children[7]) delete	m_Children[7];

	if (m_Parent)		m_Parent = nullptr;
	if (m_Region)		delete	m_Region;
}

void* Octree::operator new(size_t size)
{
	if (!MemoryPool)
		MemoryPool = MemoryPoolManager::Instance()->GetMemoryPool("Octree", 100, sizeof(Octree) + sizeof(AllocationHeader) + sizeof(int));

	char* pMeme = (char*)MemoryPool->Allocate();
	AllocationHeader* pHeader = (AllocationHeader*)pMeme;

	pHeader->Signature = SIGNATURE_START;
	pHeader->Size = size;

	void* pStartMemeBlock = pMeme + sizeof(AllocationHeader);

	int* pEndMarker = (int*)((char*)pStartMemeBlock + size);
	*pEndMarker = SIGNATURE_END;

	return pStartMemeBlock;
}
void Octree::operator delete(void* pMemory)
{
	AllocationHeader* pHeader = (AllocationHeader*)((char*)pMemory - sizeof(AllocationHeader));

	assert(pHeader->Signature == SIGNATURE_START);

	int* pEndMarker = (int*)((char*)pMemory + pHeader->Size);

	assert(*pEndMarker == SIGNATURE_END);

	MemoryPool->Free(pHeader);
}

void Octree::SetParent(Octree* octree)
{
	m_Parent = octree;
}

void Octree::BuildTree(void)
{
	if (m_Spheres.size() <= 1)
	{
		return;
	}

	Vector3 extents = m_Region->Max - m_Region->Min;

	if (extents == Vector3(0.0))
	{
		//FindEnclosingCube();
		extents = m_Region->Max - m_Region->Min;
	}

	if (extents.x <= MINIMUM_NODE_SIZE && extents.y <= MINIMUM_NODE_SIZE &&extents.z <= MINIMUM_NODE_SIZE)
	{
		return;
	}

	Vector3 halfExtents = extents / 2.0f;
	Vector3 quarterExtents = extents / 4.0f;

	Vector3 centre = m_Region->Min + halfExtents;

	BoundingBox* octants[8];
	octants[0] = new BoundingBox(Vector3(centre.x + quarterExtents.x, centre.y + quarterExtents.y, centre.z - quarterExtents.z), halfExtents);
	octants[1] = new BoundingBox(Vector3(centre.x + quarterExtents.x, centre.y - quarterExtents.y, centre.z - quarterExtents.z), halfExtents);
	octants[2] = new BoundingBox(Vector3(centre.x - quarterExtents.x, centre.y - quarterExtents.y, centre.z - quarterExtents.z), halfExtents);
	octants[3] = new BoundingBox(Vector3(centre.x - quarterExtents.x, centre.y + quarterExtents.y, centre.z - quarterExtents.z), halfExtents);
	octants[4] = new BoundingBox(Vector3(centre.x + quarterExtents.x, centre.y + quarterExtents.y, centre.z + quarterExtents.z), halfExtents);
	octants[5] = new BoundingBox(Vector3(centre.x + quarterExtents.x, centre.y - quarterExtents.y, centre.z + quarterExtents.z), halfExtents);
	octants[6] = new BoundingBox(Vector3(centre.x - quarterExtents.x, centre.y - quarterExtents.y, centre.z + quarterExtents.z), halfExtents);
	octants[7] = new BoundingBox(Vector3(centre.x - quarterExtents.x, centre.y + quarterExtents.y, centre.z + quarterExtents.z), halfExtents);

	std::vector<Sphere*> delist;
	std::vector<std::vector<Sphere*>> octList = std::vector<std::vector<Sphere*>>(8);

	for (Sphere* sph : m_Spheres)
	{
		if (sph->Radius != 0.0f)
		{
			for (int octant = 0; octant < 8; octant++)
			{
				if (octants[octant]->Contains(sph->BoundingVolume))
				{
					octList[octant].push_back(sph);
					delist.push_back(sph);
					break;
				}
			}
		}
	}

	for (auto iterA = delist.begin(); iterA != delist.end(); iterA++)
	{
		for (auto iterB = m_Spheres.begin(); iterB != m_Spheres.end(); iterB++)
		{
			if (*iterA == *iterB)
			{
				m_Spheres.erase(iterB);
				break;
			}
		}
	}

	for (int a = 0; a < 8; a++)
	{
		if (octList[a].size() != 0)
		{
			m_Children[a] = CreateNode(octants[a], octList[a]);
			m_ActiveNodeMask |= (short)(1 << a);
			m_Children[a]->BuildTree();
		}
		else
		{
			delete octants[a];
		}
	}

	m_TreeBuilt = true;
	m_TreeReady = true;
}
Octree* Octree::CreateNode(BoundingBox* region, Sphere* sphere)
{
	std::vector<Sphere*> objList;
	objList.push_back(sphere);

	Octree* ret = new Octree(region, objList);
	ret->SetParent(this);
	return ret;
}
Octree* Octree::CreateNode(BoundingBox* region, std::vector<Sphere*> spheres)
{
	if (spheres.size() == 0)
		return nullptr;

	Octree* ret = new Octree(region, spheres);
	ret->SetParent(this);

	return ret;
}

void Octree::Update(void)
{
	if (m_TreeBuilt)
	{
		if (m_Spheres.size() == 0)
		{
			if (!m_HasChildren)
			{
				if (m_CurrentLife == -1)
				{
					m_CurrentLife = m_MaxLifespan;
				}
				else if(m_CurrentLife > 0)
				{
					m_CurrentLife--;
				}
			}
		}
		else
		{
			if (m_CurrentLife != -1)
			{
				if (m_MaxLifespan <= 64)
				{
					m_MaxLifespan *= 2;
				}
				m_CurrentLife = -1;
			}
		}

		std::vector<Sphere*> movedObjects;
	}
}
void Octree::UpdateTree(void)
{
	if (!m_TreeBuilt)
	{
		while (m_PendingInsertion.size() != 0)
		{
			m_Spheres.push_back(m_PendingInsertion.front());
			m_PendingInsertion.erase(m_PendingInsertion.begin());
		}

		BuildTree();
	}
	else
	{
		while (m_PendingInsertion.size() != 0)
		{
			Insert(m_PendingInsertion.front());
			m_PendingInsertion.erase(m_PendingInsertion.begin());
		}
	}

	m_TreeReady = true;
}

void Octree::Insert(Sphere* sphere)
{
	if (m_Spheres.size() <= 1 && m_ActiveNodeMask == 0)
	{
		m_Spheres.push_back(sphere);
		return;
	}

	Vector3 dimensions = m_Region->Max - m_Region->Min;
	if (dimensions.x <= MINIMUM_NODE_SIZE && dimensions.y <= MINIMUM_NODE_SIZE && dimensions.z <= MINIMUM_NODE_SIZE)
	{
		m_Spheres.push_back(sphere);
		return;
	}
	Vector3 half = dimensions / 2.0f;
	Vector3 center = m_Region->Min + half;

	BoundingBox* childOctant[8];
	childOctant[0] = (m_Children[0] != nullptr) ? m_Children[0]->m_Region : new BoundingBox(m_Region->Min, center);
	childOctant[1] = (m_Children[1] != nullptr) ? m_Children[1]->m_Region : new BoundingBox(Vector3(center.x, m_Region->Min.y, m_Region->Min.z), Vector3(m_Region->Max.x, center.y, center.z));
	childOctant[2] = (m_Children[2] != nullptr) ? m_Children[2]->m_Region : new BoundingBox(Vector3(center.x, m_Region->Min.y, center.z), Vector3(m_Region->Max.x, center.y, m_Region->Max.z));
	childOctant[3] = (m_Children[3] != nullptr) ? m_Children[3]->m_Region : new BoundingBox(Vector3(m_Region->Min.x, m_Region->Min.y, center.z), Vector3(center.x, center.y, m_Region->Max.z));
	childOctant[4] = (m_Children[4] != nullptr) ? m_Children[4]->m_Region : new BoundingBox(Vector3(m_Region->Min.x, center.y, m_Region->Min.z), Vector3(center.x, m_Region->Max.y, center.z));
	childOctant[5] = (m_Children[5] != nullptr) ? m_Children[5]->m_Region : new BoundingBox(Vector3(center.x, center.y, m_Region->Min.z), Vector3(m_Region->Max.x, m_Region->Max.y, center.z));
	childOctant[6] = (m_Children[6] != nullptr) ? m_Children[6]->m_Region : new BoundingBox(center, m_Region->Max);
	childOctant[7] = (m_Children[7] != nullptr) ? m_Children[7]->m_Region : new BoundingBox(Vector3(m_Region->Min.x, center.y, center.z), Vector3(center.x, m_Region->Max.y, m_Region->Max.z));

	 if (sphere->Radius != 0 && m_Region->Contains(sphere->Center))
	{
		bool found = false;
		for (int a = 0; a < 8; a++)
		{
			if (childOctant[a]->Contains(sphere->Center))
			{
				if (m_Children[a] != nullptr)
					m_Children[a]->Insert(sphere);
				else
				{
					m_Children[a] = CreateNode(childOctant[a], sphere);
					m_ActiveNodeMask |= (unsigned short)(1 << a);
				}
				found = true;
			}
		}
		if (!found) m_Spheres.push_back(sphere);
	}
	else
	{
		BuildTree();
	}
}
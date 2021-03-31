#pragma once

#include <vector>

#include "Defines.h"
#include "Sphere.h"
#include "BoundingBox.h"


#define MINIMUM_NODE_SIZE 2

class Octree
{
public:
	static MemoryPool*			MemoryPool;

	Octree(void);
	Octree(BoundingBox* bBox, std::vector<Sphere*> spheres);
	~Octree(void);

	static void* operator new(size_t size);
	static void operator delete(void* pMemory);

	void Update(void);
	void UpdateTree(void);

	void SetParent(Octree* octree);

private:
	Octree*							m_Parent;
	Octree*							m_Children[8];

	BoundingBox*					m_Region;

	int										m_CurrentLife;
	int										m_MaxLifespan;
	unsigned short					m_ActiveNodeMask;

	std::vector<Sphere*>		m_Spheres;
	std::vector<Sphere*>		m_PendingInsertion;

	bool									m_HasChildren;
	static bool						m_TreeBuilt;
	static bool						m_TreeReady;
	
	void									BuildTree(void);
	void									Insert(Sphere* sphere);

	Octree* CreateNode(BoundingBox* region, Sphere* sphere);
	Octree* CreateNode(BoundingBox* region, std::vector<Sphere*> spheres);
};
#pragma once

#include <vector>

#include "Defines.h"
#include "BaseApplication.h"

class Octree;
class Sphere;

class TestApp : public BaseApplication
{
public:
	TestApp(void);
	virtual ~TestApp(void);

	virtual void Initialise(void) override;
	virtual void Run(void) override;
protected:
private:
	Octree*		m_Octree;
	Sphere*		m_SpheresArray[MAX_SPHERES];

	virtual void	Update(float deltaTime);
	virtual void	Render(int frame);
};

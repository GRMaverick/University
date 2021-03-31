#pragma once

#pragma once

#include <vector>

#include "Defines.h"
#include "BaseApplication.h"

class Floor;
class Sphere;

class SequentialPhysicsApp : public BaseApplication
{
public:
	SequentialPhysicsApp(void);
	virtual ~SequentialPhysicsApp(void);

	virtual void Initialise(void) override;
	virtual void Run(void) override;
protected:
private:
	Floor*			m_Floor;
	Sphere*		m_SpheresArray[MAX_SPHERES];

	virtual void	Update(float deltaTime);
	virtual void	Render(int frame);
};

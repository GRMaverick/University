#pragma once

#include <vector>

#include "Defines.h"
#include "BaseApplication.h"

class Floor;
class Sphere;

class BackendApplication : public BaseApplication
{
public:
	BackendApplication(bool preview);
	virtual ~BackendApplication(void);

	virtual void Initialise(bool preview) override;
	virtual void Run(void) override;
protected:
private:
	bool				m_Preview;
	Floor*			m_Floor;
	Sphere*		m_SpheresArray[MAX_SPHERES];

	virtual void	Update(float deltaTime);
	virtual void	Render(int frame);
};
#pragma once

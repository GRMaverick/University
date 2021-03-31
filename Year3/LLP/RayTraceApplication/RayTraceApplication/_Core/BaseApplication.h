#pragma once

class BaseApplication
{
public:
	virtual ~BaseApplication(void) { }
	virtual void Initialise(bool preview) = 0;
	virtual void Run(void) = 0;
protected:
private:
};
#pragma once

class BaseApplication;

class AppManager
{
public:
	~AppManager(void);
	static AppManager* Instance(void);
	BaseApplication* GetApplication(int application);

private:
	static AppManager* m_Instance;

	AppManager(void);
};
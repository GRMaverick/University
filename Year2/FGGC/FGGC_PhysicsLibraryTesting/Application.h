#pragma once

#include "Base.h"
#include "DDSTextureLoader.h"
#include "resource.h"
#include "Camera.h"
#include "OBJLoader.h"

#include <vector>

#include "GameObject.h"
#include "CollisionManager.h"

using namespace DirectX;

class Application : public Base
{
private:
	ID3D11ShaderResourceView * _pTextureRV = nullptr;
	ID3D11ShaderResourceView*	 _pNormandyTexture = nullptr;
	ID3D11ShaderResourceView * _pGroundTextureRV = nullptr;

	Light basicLight;

	GameObject* _normandy;
	vector<GameObject *> _gameObjects;

	Camera * _camera;
	float _cameraOrbitRadius = 7.0f;
	float _cameraOrbitRadiusMin = 2.0f;
	float _cameraOrbitRadiusMax = 50.0f;
	float _cameraOrbitAngleXZ = -90.0f;
	float _cameraSpeed = 2.0f;

private:
	void Cleanup();
public:
	Application();
	~Application();

	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);
	HRESULT InitialiseCamera(void);
	HRESULT InitialiseSceneObjects(void);

	bool HandleKeyboard(MSG msg);

	void Update(float deltaTime);
	void Draw();
};


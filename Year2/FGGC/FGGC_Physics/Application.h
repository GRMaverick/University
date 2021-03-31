#pragma once
#include <stdio.h>
#include <vector>
#include <ostream>
#include <windows.h>
#include <d3d11_1.h>
#include <directxmath.h>
#include <d3dcompiler.h>
#include <directxcolors.h>
#include <DirectXCollision.h>

#include "resource.h"
#include "Structure.h"

#include "Camera.h"
#include "Aircraft.h"
#include "GameObject.h"
#include "DDSTextureLoader.h"

using namespace std;
using namespace DirectX;


class Application
{
private:
	HINSTANCE							 _hInst;
	HWND									 _hWnd;
	D3D_DRIVER_TYPE				 _driverType;
	D3D_FEATURE_LEVEL			_featureLevel;
	ID3D11Device*					_pd3dDevice;
	ID3D11DeviceContext*		_pImmediateContext;
	IDXGISwapChain*				_pSwapChain;
	ID3D11RenderTargetView* _pRenderTargetView;
	ID3D11VertexShader*			_pVertexShader;
	ID3D11PixelShader*			_pPixelShader;
	ID3D11InputLayout*			_pVertexLayout;

	ID3D11Buffer*						_pVertexBuffer;
	ID3D11Buffer*						_pIndexBuffer;

	ID3D11Buffer*						_pPlaneVertexBuffer;
	ID3D11Buffer*						_pPlaneIndexBuffer;

	ID3D11Buffer*						_pAircraftVertex;
	ID3D11Buffer*						_pAircraftIndex;

	ID3D11Buffer*						_pConstantBuffer;

	ID3D11DepthStencilView*	_depthStencilView = nullptr;
	ID3D11Texture2D*				_depthStencilBuffer = nullptr;

	ID3D11ShaderResourceView * _pTextureRV = nullptr;
	ID3D11ShaderResourceView * _pWheelTexture = nullptr;
	ID3D11ShaderResourceView * _pGroundTextureRV = nullptr;
	ID3D11ShaderResourceView * _pAircraftTextureRV = nullptr;
	ID3D11ShaderResourceView*  _pSidewinderTex = nullptr;
	ID3D11ShaderResourceView*	 _pMissleTexture = nullptr;
	ID3D11ShaderResourceView*	_pHumveeTexture = nullptr;

	ID3D11SamplerState * _pSamplerLinear = nullptr;

	Light basicLight;

	vector<GameObject*>		_gameObjects;
	vector<XMFLOAT3>			_AIPath;
	vector<Aircraft*>				_aircraft;
	vector<GameObject*>		_projectiles;

	Camera * _camera, *_camera2, *_camera3, *_activeCam;


	float _cameraOrbitRadius = 7.0f;
	float _cameraOrbitRadiusMin = 2.0f;
	float _cameraOrbitRadiusMax = 50.0f;
	float _cameraOrbitAngleXZ = -90.0f;
	float _cameraSpeed = 2.0f;

	UINT _WindowHeight;
	UINT _WindowWidth;

	// Render dimensions - Change here to alter screen resolution
	UINT _renderHeight = 1080;
	UINT _renderWidth = 1920;

	ID3D11DepthStencilState* DSLessEqual;
	ID3D11RasterizerState* RSCullNone;

	ID3D11RasterizerState* CCWcullMode;
	ID3D11RasterizerState* CWcullMode;

	// **************** UPDATE VARIABLES **************** //	
	float															_newTime;
	float															_oldTime;
	float															_deltaTime;
	float															_totalTime;
	float															_frameCounter;
	// ************************************************************//

	bool _check;
	bool reload = false;
	float reloadTimer = 0.0f;
	XMFLOAT3 _weight;


private:
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	HRESULT InitDevice();
	void Cleanup();
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	HRESULT InitShadersAndInputLayout();
	HRESULT InitVertexBuffer();
	HRESULT InitIndexBuffer();

	void InitialiseCameras();
	void InitialiseFloor();
	void InitialiseCubes();
	void InitialiseWheels();
	void InitialisePath();
	void InitialiseAircraft();
	void InitialiseProjectiles();

	void UpdateDeltaTime();
	void UpdateCameras();
	void UpdateGameObjects();
	void CheckCollisions();

public:
	Application();
	~Application();

	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);

	bool HandleKeyboard(MSG msg);
	void InputCommands();

	void Update();

	bool CollisionCheck(ParticleModel* object1, ParticleModel* object2);
	void GameLoopDelay(float frameStartTime);

	void Draw();

};


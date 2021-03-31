#include "Application.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

Application::Application()
{
	_pKeyState = 0;
	_cameraState = 1;
	_rotationUD = 0.0f;
	_rotationLR = 0.0f;
	_rotationYaw = 0.0f;

	_hInst = nullptr;
	_hWnd = nullptr;
	_driverType = D3D_DRIVER_TYPE_NULL;
	_featureLevel = D3D_FEATURE_LEVEL_11_0;
	_pd3dDevice = nullptr;
	_pImmediateContext = nullptr;
	_pSwapChain = nullptr;
	_pRenderTargetView = nullptr;
	_pVertexShader = nullptr;
	_pPixelShader = nullptr;
	_pVertexLayout = nullptr;
	_pVertexBuffer = nullptr;
	_pIndexBuffer = nullptr;
	_pConstantBuffer = nullptr;
	_pTextureRV = nullptr;
	_pSamplerLinear = nullptr;
}
Application::~Application()
{
	Cleanup();
}

HRESULT Application::Initialise(HINSTANCE hInstance, int nCmdShow)
{
	HRESULT result;

	if (FAILED(InitWindow(hInstance, nCmdShow)))
	{
		return E_FAIL;
	}

	RECT rc;
	GetClientRect(_hWnd, &rc);
	_WindowWidth = rc.right - rc.left;
	_WindowHeight = rc.bottom - rc.top;

	if (FAILED(InitDevice()))
	{
		Cleanup();

		return E_FAIL;
	}

	// Initialize the world matrix
	XMStoreFloat4x4(&_world, XMMatrixIdentity());
	XMStoreFloat4x4(&_world1, XMMatrixIdentity());
	XMStoreFloat4x4(&_world3, XMMatrixIdentity());
	XMStoreFloat4x4(&_world4, XMMatrixIdentity());
	XMStoreFloat4x4(&_world5, XMMatrixIdentity());
	XMStoreFloat4x4(&_planeWorld, XMMatrixIdentity());

	// Create the sample state
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	_pd3dDevice->CreateSamplerState(&sampDesc, &_pSamplerLinear);
	CreateDDSTextureFromFile(_pd3dDevice, L"Textures/Crate_COLOR.dds", nullptr, &_pTextureRV);
	CreateDDSTextureFromFile(_pd3dDevice, L"Textures/CFAPlaneTexture.dds", nullptr, &_pPlaneTexRV);
	CreateDDSTextureFromFile(_pd3dDevice, L"Textures/grass.dds", nullptr, &_pTerrainTexture);
	CreateDDSTextureFromFile(_pd3dDevice, L"Textures/F35PlaneTexture.dds", nullptr, &_pTreeTexture);
	CreateDDSTextureFromFile(_pd3dDevice, L"Textures/ground2.dds", nullptr, &_pRunwayTexture);
	CreateDDSTextureFromFile(_pd3dDevice, L"Textures/Tower.dds", nullptr, &_pTowerTexture);
	CreateDDSTextureFromFile(_pd3dDevice, L"Textures/DuskSky.dds", nullptr, &_pSkySphereTexture);

	_pPlaneMesh = OBJLoader::Load("Objects/CFA44.obj", _pd3dDevice);
	_pCityMesh = OBJLoader::Load("Objects/F-35_Lightning_II.obj", _pd3dDevice);
	_pTowerMesh = OBJLoader::Load("Objects/tower.obj", _pd3dDevice, true);
	_pSkySphereMesh = OBJLoader::Load("Objects/sphere.obj", _pd3dDevice);

	_planeObject = new Aircraft(); _planeObject->SetPosition(0.0f, -48.9f, 500.0f);
	_pTerrain = new Terrain();
	_pRunway = new Runway();
	_pPlane2 = new GameObject();
	_pTower = new GameObject();
	_pSkySphere = new GameObject();

	_planeObject->Initialise(_pPlaneMesh, _pPlaneTexRV);
	_pTerrain->Initialise(_pd3dDevice, _pTerrainTexture, 1024.0f, 1024.0f, 1024, 1024);
	_pPlane2->Initialise(_pCityMesh);
	_pTower->Initialise(_pTowerMesh);
	_pRunway->Initialise(_pd3dDevice, _pRunwayTexture, 65.0, 300.0f, 65, 300);
	_pSkySphere->Initialise(_pSkySphereMesh);

	XMFLOAT4 eye = XMFLOAT4(_planeObject->GetPosition().x, _planeObject->GetPosition().y + 3.0f, _planeObject->GetPosition().z - 15.0f, 0.0f);
	XMFLOAT4 eye2 = XMFLOAT4(_planeObject->GetPosition().x - 2, _planeObject->GetPosition().y, _planeObject->GetPosition().z, 0.0f);
	XMFLOAT4 at = XMFLOAT4(_planeObject->GetPosition().x, _planeObject->GetPosition().y, _planeObject->GetPosition().z, 0.0f);
	XMFLOAT4 up = { 0.0f, 1.0f, 0.0f, 0.0f };

	FLOAT nearPlane = 0.01f;
	FLOAT farPlane = 2048.0f;

	_camera1 = new Camera(eye, at, up, _WindowWidth, _WindowHeight, nearPlane, farPlane);
	_camera2 = new Camera(eye2, at, up, _WindowWidth, _WindowHeight, nearPlane, farPlane);
	_camera3 = new Camera(eye, at, up, _WindowWidth, _WindowHeight, nearPlane, farPlane);
	_camera4 = new Camera(eye, at, up, _WindowWidth, _WindowHeight, nearPlane, farPlane);

	// Initialize the lighting variables
	// Light direction from surface (XYZ)
	lightDirection = XMFLOAT3(0.25f, 0.5f, -1.0f);
	// Lighting material properties (RGBA)
	diffuseMaterial = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	// Light colour (RGBA)
	diffuseLight = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	// Ambient 
	ambientMaterial = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	// Ambient
	ambientLight = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	// Specular
	specularPower = 5.0f;
	// Specular
	specularMaterial = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	// Specular
	specularLight = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	// Specular
	XMStoreFloat3(&eyePosW, XMLoadFloat4(&GetCamera()->GetEye()));

	return S_OK;
}
HRESULT Application::InitShadersAndInputLayout()
{
	HRESULT hr;

	// Compile the vertex shader
	ID3DBlob* pVSBlob = nullptr;
	hr = CompileShaderFromFile(L"DX11 Framework.fx", "VS", "vs_4_0", &pVSBlob);

	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the vertex shader
	hr = _pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &_pVertexShader);

	if (FAILED(hr))
	{
		pVSBlob->Release();
		return hr;
	}

	// Compile the pixel shader
	ID3DBlob* pPSBlob = nullptr;
	hr = CompileShaderFromFile(L"DX11 Framework.fx", "PS", "ps_4_0", &pPSBlob);

	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the pixel shader
	hr = _pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &_pPixelShader);
	pPSBlob->Release();

	if (FAILED(hr))
		return hr;

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	hr = _pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(), &_pVertexLayout);
	pVSBlob->Release();

	if (FAILED(hr))
		return hr;

	// Set the input layout
	_pImmediateContext->IASetInputLayout(_pVertexLayout);

	return hr;
}
HRESULT Application::InitVertexBuffer()
{
	HRESULT hr;

	// Create vertex buffer
	SimpleVertex vertices[] =
	{
		//front quad
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },

		//back quad
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) }
	};

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex)* 8;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitDataCube;
	ZeroMemory(&InitDataCube, sizeof(InitDataCube));
	InitDataCube.pSysMem = vertices;
	hr = _pd3dDevice->CreateBuffer(&bd, &InitDataCube, &_pVertexBuffer);

	if (FAILED(hr))
		return hr;

	return S_OK;
}
HRESULT Application::InitIndexBuffer()
{
	HRESULT hr;

	// Create index buffer
	WORD indices[] =
	{
		0, 1, 2,    // side 1
		2, 1, 3,
		4, 0, 6,    // side 2
		6, 0, 2,
		1, 5, 3,
		3, 5, 7,
		5, 4, 7,
		7, 4, 6,
		4, 5, 0,
		0, 5, 1,
		2, 3, 6,
		6, 3, 7,
	};

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD)* 36;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitDataCube;
	ZeroMemory(&InitDataCube, sizeof(InitDataCube));
	InitDataCube.pSysMem = indices;
	hr = _pd3dDevice->CreateBuffer(&bd, &InitDataCube, &_pIndexBuffer);

	if (FAILED(hr))
		return hr;

	return S_OK;
}
HRESULT Application::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"TutorialWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	// Create window
	_hInst = hInstance;
	RECT rc = { 0, 0, 1800, 1020 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	_hWnd = CreateWindow(L"TutorialWindowClass", L"DX11 Framework", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		nullptr);
	if (!_hWnd)
		return E_FAIL;

	ShowWindow(_hWnd, nCmdShow);

	if (!InitDirectInput(hInstance))
	{
		MessageBox(0, L"Direct Input Initialization - Failed",
			L"Error", MB_OK);
		return 0;
	}
	return S_OK;
}
HRESULT Application::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	#if defined(DEBUG) || defined(_DEBUG)
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
	#endif

	ID3DBlob* pErrorBlob;
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, ppBlobOut, &pErrorBlob);

	if (FAILED(hr))
	{
		if (pErrorBlob != nullptr)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());

		if (pErrorBlob) pErrorBlob->Release();

		return hr;
	}

	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}
HRESULT Application::InitDevice()
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};

	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = _WindowWidth;
	sd.BufferDesc.Height = _WindowHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = _hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(nullptr, _driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &_pSwapChain, &_pd3dDevice, &_featureLevel, &_pImmediateContext);
		if (SUCCEEDED(hr))
			break;
	}

	if (FAILED(hr))
		return hr;

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	if (FAILED(hr))
		return hr;

	hr = _pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &_pRenderTargetView);
	pBackBuffer->Release();

	if (FAILED(hr))
		return hr;

	// Setup Depth Stencil Thing
	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = _WindowWidth;
	depthStencilDesc.Height = _WindowHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	_pd3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, &_depthStencilBuffer);
	_pd3dDevice->CreateDepthStencilView(_depthStencilBuffer, nullptr, &_depthStencilView);

	_pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView, _depthStencilView);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)_WindowWidth;
	vp.Height = (FLOAT)_WindowHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	_pImmediateContext->RSSetViewports(1, &vp);

	InitShadersAndInputLayout();

	InitVertexBuffer();

	InitIndexBuffer();

	// Set primitive topology
	_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Create the constant buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = _pd3dDevice->CreateBuffer(&bd, nullptr, &_pConstantBuffer);

	// Initialize Rasterizer
	D3D11_RASTERIZER_DESC _wfdesc;
	ZeroMemory(&_wfdesc, sizeof(_wfdesc));
	_wfdesc.FillMode = D3D11_FILL_WIREFRAME;
	_wfdesc.CullMode = D3D11_CULL_NONE;
	hr = _pd3dDevice->CreateRasterizerState(&_wfdesc, &_wireFrame);

	D3D11_RASTERIZER_DESC solidShapeDesc;
	ZeroMemory(&solidShapeDesc, sizeof(D3D11_RASTERIZER_DESC));
	solidShapeDesc.FillMode = D3D11_FILL_SOLID;
	solidShapeDesc.CullMode = D3D11_CULL_NONE;
	hr = _pd3dDevice->CreateRasterizerState(&solidShapeDesc, &_solidShape);

	if (FAILED(hr))
		return hr;

	return S_OK;
}

bool Application::InitDirectInput(HINSTANCE hInstance)
{
	bool hr;

	hr = DirectInput8Create(hInstance,	DIRECTINPUT_VERSION,	IID_IDirectInput8, (void**)&_DirectInput, NULL);
	hr = _DirectInput->CreateDevice(GUID_SysKeyboard, &_DIKeyboard, NULL);
	hr = _DirectInput->CreateDevice(GUID_SysMouse, &_DIMouse,	NULL);
	hr = _DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
	hr = _DIKeyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	hr = _DIMouse->SetDataFormat(&c_dfDIMouse);
	hr = _DIMouse->SetCooperativeLevel(_hWnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);

	return true;
}

void Application::Cleanup()
{
	if (_pImmediateContext) _pImmediateContext->ClearState();

	if (_pConstantBuffer) _pConstantBuffer->Release();
	if (_pVertexBuffer) _pVertexBuffer->Release();
	if (_pIndexBuffer) _pIndexBuffer->Release();
	if (_pVertexLayout) _pVertexLayout->Release();
	if (_pVertexShader) _pVertexShader->Release();
	if (_pPixelShader) _pPixelShader->Release();
	if (_pRenderTargetView) _pRenderTargetView->Release();
	if (_pSwapChain) _pSwapChain->Release();
	if (_pImmediateContext) _pImmediateContext->Release();
	if (_pd3dDevice) _pd3dDevice->Release();

	if (_wireFrame) _wireFrame->Release();

	if (_depthStencilView) _depthStencilView->Release();
	if (_depthStencilBuffer) _depthStencilBuffer->Release();

	delete _pTerrain;
	delete _pRunway;
	delete _planeObject;
	delete _pPlane2;
	//delete _pFog;
}
void Application::Update()
{
	// Update our time
	static float t = 0.0f;

	if (_driverType == D3D_DRIVER_TYPE_REFERENCE)
	{
		t += (float)XM_PI * 0.0125f;
	}
	else
	{
		static DWORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();

		if (dwTimeStart == 0)
			dwTimeStart = dwTimeCur;

		t = (dwTimeCur - dwTimeStart) / 1000.0f;
	}
	
	_newTime = timeGetTime();
	_deltaTime = (float)(_newTime - _oldTime) / 1000;
	_oldTime = _newTime;

	if (_deltaTime > 0.016f) _deltaTime = 0.016f;
	if (_deltaTime < 0.001f) _deltaTime = 0.001f;

	_totalTime += _deltaTime;

	//
	// Animate the cube
	//
	XMStoreFloat4x4(&_world, XMMatrixRotationY(2* t));
	XMStoreFloat4x4(&_world1, XMMatrixRotationZ(t)*XMMatrixTranslation(10.0f, 0.0f, 0.0f)*XMMatrixScaling(0.5f, 0.5f, 0.5f)*XMMatrixRotationY(t));
	XMStoreFloat4x4(&_world2, XMMatrixTranslation(10, 0, 0)* XMMatrixScaling(0.25, 0.25, 0.25)*XMMatrixRotationZ(t * 3)*XMMatrixTranslation(5, 0, 0) * XMMatrixRotationY(t)); 

	XMStoreFloat4x4(&_world3, XMMatrixTranslation(0.0f, -50.0f, 0.0f));
	XMStoreFloat4x4(&_world4, XMMatrixRotationX(-(XM_PI / 2)) * XMMatrixRotationY(XM_PI / 4) * XMMatrixTranslation(30.0f, -49.5f, 495.0f));
	XMStoreFloat4x4(&_world5, XMMatrixTranslation(0.0f, -49.9f, 435.0f));
	XMStoreFloat4x4(&_world6, XMMatrixTranslation(30.0f, -49.9f, 475.0f));

	DetectInput(_deltaTime);

	_planeObject->Update(t);
	_planeObject->SetRotation(_rotationUD, _rotationYaw, _rotationLR);

	_pPlane2->Update(_deltaTime);
	_pTower->Update(_deltaTime);
	_pSkySphere->SetScale(1024.0f, 1024.0f, 1024.0f);  _pSkySphere->Update(_deltaTime);
	_pSkySphere->SetRotation(0.0f, t * 0.05f, -XM_PI / 2);

	UpdateCamState();
	UpdateCamera();
	GetCamera()->CalculateViewProjection();
}
void Application::Draw()
{

	//
	// Clear the back buffer
	//
	float ClearColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f }; // red,green,blue,alpha
	_pImmediateContext->ClearRenderTargetView(_pRenderTargetView, ClearColor);
	_pImmediateContext->PSSetSamplers(0, 1, &_pSamplerLinear);
	_pImmediateContext->PSSetShaderResources(0, 1, &_pTextureRV);
	_pImmediateContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	

	XMMATRIX world = XMLoadFloat4x4(&_world);
	XMMATRIX view;
	XMMATRIX projection;

	if (_cameraState == 1)
	{
		view = XMLoadFloat4x4(&_camera1->GetView());
		projection = XMLoadFloat4x4(&_camera1->GetProjection());
	}
	if (_cameraState == 2)
	{
		view = XMLoadFloat4x4(&_camera2->GetView());
		projection = XMLoadFloat4x4(&_camera2->GetProjection());
	}
	if (_cameraState == 3)
	{
		view = XMLoadFloat4x4(&_camera3->GetView());
		projection = XMLoadFloat4x4(&_camera3->GetProjection());
	}

	//
	// Update variables
	//
	ConstantBuffer cb;
	cb.mWorld = XMMatrixTranspose(world);
	cb.mView = XMMatrixTranspose(view);
	cb.mProjection = XMMatrixTranspose(projection);
	cb.DiffuseMtrl = diffuseMaterial;
	cb.DiffuseLight = diffuseLight;
	cb.AmbientMtrl = ambientMaterial;
	cb.AmbientLight = ambientLight;
	cb.LightVecW = lightDirection;
	cb.SpecularPower = specularPower;
	cb.SpecularMtrl = specularMaterial;
	cb.SpecularLight = specularLight;
	cb.EyePosW = eyePosW;

	if (Keyboard() == 1)
		_pImmediateContext->RSSetState(_wireFrame);
	if (Keyboard() == 0)
		_pImmediateContext->RSSetState(_solidShape);

	_pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);

	//
	// Renders a triangle
	//
	_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;

	_pImmediateContext->IASetVertexBuffers(0, 1, &_pVertexBuffer, &stride, &offset);
	_pImmediateContext->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	_pImmediateContext->VSSetShader(_pVertexShader, nullptr, 0);
	_pImmediateContext->VSSetConstantBuffers(0, 1, &_pConstantBuffer);
	_pImmediateContext->PSSetShader(_pPixelShader, nullptr, 0);
	_pImmediateContext->PSSetConstantBuffers(0, 1, &_pConstantBuffer);
	_pImmediateContext->DrawIndexed(36, 0, 0);

	cb.mWorld = XMMatrixTranspose(XMLoadFloat4x4(&_world1));
	_pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);
	_pImmediateContext->DrawIndexed(36, 0, 0);

	cb.mWorld = XMMatrixTranspose(XMLoadFloat4x4(&_world2));
	_pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);
	_pImmediateContext->DrawIndexed(36, 0, 0);

	cb.mWorld = XMMatrixTranspose(XMLoadFloat4x4(&_planeObject->GetWorld()));
	_pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);
	_planeObject->Draw(_pd3dDevice, _pImmediateContext);

	cb.mWorld = XMMatrixTranspose(XMLoadFloat4x4(&_world3));
	_pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);
	_pTerrain->Draw(_pd3dDevice, _pImmediateContext);

	cb.mWorld = XMMatrixTranspose(XMLoadFloat4x4(&_world4));
	_pImmediateContext->PSSetShaderResources(0, 1, &_pTreeTexture);
	_pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);
	_pPlane2->Draw(_pd3dDevice, _pImmediateContext);

	cb.mWorld = XMMatrixTranspose(XMLoadFloat4x4(&_world5));
	_pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);
	_pRunway->Draw(_pd3dDevice, _pImmediateContext);

	cb.mWorld = XMMatrixTranspose(XMLoadFloat4x4(&_world6));
	_pImmediateContext->PSSetShaderResources(0, 1, &_pTowerTexture);
	_pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);
	_pTower->Draw(_pd3dDevice, _pImmediateContext);

	cb.mWorld = XMMatrixTranspose(XMLoadFloat4x4(&_pSkySphere->GetWorld()));
	_pImmediateContext->PSSetShaderResources(0, 1, &_pSkySphereTexture);
	_pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);
	_pSkySphere->Draw(_pd3dDevice, _pImmediateContext);

	//
	// Present our back buffer to our front buffer
	//[
	_pSwapChain->Present(0, 0);
}

int Application::Keyboard()
{
	if ((GetKeyState(VK_CONTROL) && 0x8000) && _pKeyState == 1)
		return 0;
	if ((GetKeyState(VK_CONTROL) && 0x8000) && _pKeyState == 0)
		return 1;
}

Camera* Application::GetCamera()
{
	if (_cameraState == 1)
		return _camera1;
	if (_cameraState == 2)
		return _camera2;
	if (_cameraState == 3)
		return _camera3;
	if (_cameraState == 4)
		return _camera4;
}
void Application::UpdateCamState()
{
	if ((GetKeyState(VK_NUMPAD1) && 0x8000))
		_cameraState = 1;
	if ((GetKeyState(VK_NUMPAD2) && 0x8000))
		_cameraState = 2;
	if ((GetKeyState(VK_NUMPAD3) && 0x8000))
		_cameraState = 3;
	if ((GetKeyState(VK_NUMPAD4) && 0x8000))
		_cameraState = 4;
}
void Application::UpdateCamera()
{
	XMFLOAT4 uAt1, uAt2, uAt4;
	XMFLOAT4 uEye1, uEye2, uEye3, uEye4;

	uAt1 = XMFLOAT4(_planeObject->GetPosition().x, _planeObject->GetPosition().y, _planeObject->GetPosition().z, 0.0f);
	uAt2 = XMFLOAT4(0.0f, 0.0f, _planeObject->GetPosition().z - 1, 0.0f);
	uAt4 = XMFLOAT4(_planeObject->GetPosition().x, _planeObject->GetPosition().y, _planeObject->GetPosition().z, 0.0f);

	uEye1 = XMFLOAT4(_planeObject->GetPosition().x, _planeObject->GetPosition().y + 6.0f, _planeObject->GetPosition().z + 15.0f, 0.0f);
	uEye2 = XMFLOAT4(_planeObject->GetPosition().x - 3.0f, _planeObject->GetPosition().y, _planeObject->GetPosition().z, 0.0f);
	uEye3 = XMFLOAT4(0.0f, -49.5f, 0.0f, 0.0f);
	uEye4 = XMFLOAT4(_planeObject->GetPosition().x, _planeObject->GetPosition().y + 5.0f, _planeObject->GetPosition().z, 0.0f);

	_camera1->SetAt(uAt1);
	_camera2->SetAt(uAt2);
	_camera3->SetAt(uAt1);
	_camera4->SetAt(uAt4);

	_camera1->SetEye(uEye1);
	_camera2->SetEye(uEye2);
	_camera3->SetEye(uEye3);
	_camera4->SetEye(uEye4);
}
void Application::DetectInput(float elapsedTime)
{
	DIMOUSESTATE mouseCurrState;

	BYTE keyboardState[256];

	float rollRotation = 0.0f;

	_DIKeyboard->Acquire();
	_DIMouse->Acquire();

	_DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseCurrState);

	_DIKeyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);

	if (keyboardState[DIK_ESCAPE] & 0x80)
		PostMessage(_hWnd, WM_DESTROY, 0, 0);

	if (keyboardState[DIK_E] & 0x80)
	{
		_planeObject->SetThrust(_planeObject->GetThrust() - 0.0025);
	}
	if (keyboardState[DIK_Q] & 0x80)
	{
		_planeObject->SetThrust(_planeObject->GetThrust() + 0.0025);
	}
	if (keyboardState[DIK_A] & 0x80)
	{
		_rotationLR += XM_PI / 2 * elapsedTime;
		if (_rotationLR > 1.0f)
			_rotationLR = 1.0f;
		_rotationYaw += 1.0f * elapsedTime;
		//_planeObject->SetPosition((_planeObject->GetPosition().x - 2.5) * cos(0.1f) - (_planeObject->GetPosition().z - 2.5) * sin(0.1f), _planeObject->GetPosition().y, (_planeObject->GetPosition().z - 2.5 * cos(0.1f) + (_planeObject->GetPosition().x - 2.5) * sin(0.1f)));
	}
	if (keyboardState[DIK_D] & 0x80)
	{
		_rotationLR -= XM_PI / 2 * elapsedTime;
		if (_rotationLR < -1.0f)
			_rotationLR = -1.0f;
		_rotationYaw -= 1.0f * elapsedTime;
		//_planeObject->SetPosition((_planeObject->GetPosition().x - 0.5) * cos(0.1f) + (_planeObject->GetPosition().z - 0.5) * sin(0.1f), _planeObject->GetPosition().y, (_planeObject->GetPosition().z - 0.5) * cos(0.1f) - (_planeObject->GetPosition().x - 0.5) * sin(0.1f));
	}
	if (keyboardState[DIK_W] & 0x80)
	{
		_rotationUD -= (XM_PI) / 2 * elapsedTime;
		if (_rotationUD < -1.0f)
			_rotationUD = -1.0f;
	}
	if (keyboardState[DIK_S] & 0x80)
	{
		_rotationUD += (XM_PI) / 2 * elapsedTime;		
		if (_rotationUD > 1.0f)
			_rotationUD = 1.0f;
	}

	_mouseLastState = mouseCurrState;
	return;
}

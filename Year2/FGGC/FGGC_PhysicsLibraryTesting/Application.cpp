#include "Application.h"


bool Application::HandleKeyboard(MSG msg)
{
	XMFLOAT3 cameraPosition = _camera->GetPosition();

	switch (msg.wParam)
	{
	case VK_UP:
		_cameraOrbitRadius = max(_cameraOrbitRadiusMin, _cameraOrbitRadius - (_cameraSpeed * 0.2f));
		return true;
		break;

	case VK_DOWN:
		_cameraOrbitRadius = min(_cameraOrbitRadiusMax, _cameraOrbitRadius + (_cameraSpeed * 0.2f));
		return true;
		break;

	case VK_RIGHT:
		_cameraOrbitAngleXZ -= _cameraSpeed;
		return true;
		break;

	case VK_LEFT:
		_cameraOrbitAngleXZ += _cameraSpeed;
		return true;
		break;
	}

	return false;
}

Application::Application() : Base()
{
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

	DSLessEqual = nullptr;
	RSCullNone = nullptr;

	_oldTime = 0.0f;
	_newTime = 0.0f;
	_deltaTime = 0.0f;
	_totalTime = 0.0f;

	CollisionManager::GetInstance();
}
Application::~Application()
{
	Cleanup();
}

HRESULT Application::Initialise(HINSTANCE hInstance, int nCmdShow)
{
	HRESULT bResult = S_OK;

	bResult &= Base::Initialise(hInstance, nCmdShow);
	if (FAILED(bResult)) return E_FAIL;	
	bResult &= InitialiseCamera();
	if (FAILED(bResult)) return E_FAIL;
	bResult &= InitialiseSceneObjects();
	if (FAILED(bResult)) return E_FAIL;

	return bResult;
}
HRESULT Application::InitialiseCamera(void)
{
	// Setup Camera
	XMFLOAT3 eye = XMFLOAT3(0.0f, 5.0f, -50.0f);
	XMFLOAT3 at = XMFLOAT3(0.0f, 2.0f, 0.0f);
	XMFLOAT3 up = XMFLOAT3(0.0f, 1.0f, 0.0f);

	_camera = new Camera(eye, at, up, (float)_renderWidth, (float)_renderHeight, 0.01f, 200.0f);

	return S_OK;
}
HRESULT Application::InitialiseSceneObjects(void)
{
	CreateDDSTextureFromFile(_pd3dDevice, L"Resources\\stone.dds", nullptr, &_pTextureRV);
	CreateDDSTextureFromFile(_pd3dDevice, L"Resources\\floor.dds", nullptr, &_pGroundTextureRV);
	CreateDDSTextureFromFile(_pd3dDevice, L"Resources\\Normandy.dds", nullptr, &_pNormandyTexture);
	
	// Setup the scene's light
	basicLight.AmbientLight = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	basicLight.DiffuseLight = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	basicLight.SpecularLight = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	basicLight.SpecularPower = 20.0f;
	basicLight.LightVecW = XMFLOAT3(0.0f, 1.0f, -1.0f);

	Geometry cubeGeometry;
	cubeGeometry.IndexBuffer = _pIndexBuffer;
	cubeGeometry.VertexBuffer = _pVertexBuffer;
	cubeGeometry.IndexCount = 36;
	cubeGeometry.VBOffset = 0;
	cubeGeometry.VBStride = sizeof(SimpleVertex);

	Geometry planeGeometry;
	planeGeometry.IndexBuffer = _pPlaneIndexBuffer;
	planeGeometry.VertexBuffer = _pPlaneVertexBuffer;
	planeGeometry.IndexCount = 6;
	planeGeometry.VBOffset = 0;
	planeGeometry.VBStride = sizeof(SimpleVertex);

	Material shinyMaterial;
	shinyMaterial.ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	shinyMaterial.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	shinyMaterial.specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	shinyMaterial.specularPower = 10.0f;

	Material noSpecMaterial;
	noSpecMaterial.ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	noSpecMaterial.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	noSpecMaterial.specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	noSpecMaterial.specularPower = 0.0f;

	Appearance * floorAppearance = new Appearance(planeGeometry, noSpecMaterial);
	floorAppearance->SetTextureRV(_pGroundTextureRV);

	Appearance * crateAppearance = new Appearance(cubeGeometry, shinyMaterial);
	crateAppearance->SetTextureRV(_pTextureRV);

	Transform * floorTransform = new Transform();
	floorTransform->SetPosition(0.0f, 0.0f, 0.0f);
	floorTransform->SetScale(15.0f, 15.0f, 15.0f);
	floorTransform->SetRotation(XMConvertToRadians(90.0f), 0.0f, 0.0f);

	RigidBody * particleModel = new RigidBody(floorTransform, 1.0f);
	particleModel->SetScenery(true);
	particleModel->SetRestituition(0.8f);
	particleModel->SetExtents(Vector3(100.0f, 0.0f, 100.0f));
	particleModel->SetRadius(10.0f);

	GameObject * gameObject = new GameObject("Floor", floorAppearance, floorTransform, particleModel);

	_gameObjects.push_back(gameObject);

	for (auto i = 0; i < 5; i++)
	{
		Transform * cubeTransform = new Transform();
		cubeTransform->SetScale(1.0f, 1.0f, 1.0f);
		cubeTransform->SetPosition(0.0f, 18.0f + (i * 3.0f), 10.0f);

		RigidBody * particleModel = new RigidBody(cubeTransform, (i + 1.0f) * 2.0f);
		particleModel->SetExtents(Vector3(1.0f, 1.0f, 1.0f));
		particleModel->SetRestituition(0.5f);
		particleModel->SetScenery(false);
		particleModel->SetRadius(1.0f);

		gameObject = new GameObject("Cube " + i, crateAppearance, cubeTransform, particleModel);

		_gameObjects.push_back(gameObject);
	}

	#pragma region NORMANDY
		// =====  Normandy Setup
		/*Geometry normandyGeometry = OBJLoader::Load("Normandy.obj", _pd3dDevice);

		Material normandyMaterial;
		normandyMaterial.ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
		normandyMaterial.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		normandyMaterial.specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		normandyMaterial.specularPower = 10.0f;

		Appearance * normandyAppearance = new Appearance(normandyGeometry, normandyMaterial);
		normandyAppearance->SetTextureRV(_pNormandyTexture);

		Transform * normandyTransform = new Transform();
		normandyTransform->SetPosition(0.0f, 30.0f, -10.0f);
		normandyTransform->SetScale(0.05f, 0.05f, 0.05f);
		normandyTransform->SetRotation(0.0, XMConvertToRadians(120.0f), 0.0f);

		Particle * normandyParticle = new Particle(normandyTransform, 1.0f);
		normandyParticle->SetBBox(Vector3(0.5f, 0.5f, 0.5f));
		normandyParticle->SetScenery(false);
		normandyParticle->SetRestituition(0.4f);

		_normandy = new GameObject("Normandy", normandyAppearance, normandyTransform, normandyParticle);

		_gameObjects.push_back(_normandy);*/
		// ================
	#pragma endregion

	return S_OK;
}

void Application::Cleanup()
{
    if (_pImmediateContext) _pImmediateContext->ClearState();
	if (_pSamplerLinear) _pSamplerLinear->Release();

	if (_pTextureRV) _pTextureRV->Release();

	if (_pGroundTextureRV) _pGroundTextureRV->Release();

    if (_pConstantBuffer) _pConstantBuffer->Release();

    if (_pVertexBuffer) _pVertexBuffer->Release();
    if (_pIndexBuffer) _pIndexBuffer->Release();
	if (_pPlaneVertexBuffer) _pPlaneVertexBuffer->Release();
	if (_pPlaneIndexBuffer) _pPlaneIndexBuffer->Release();

    if (_pVertexLayout) _pVertexLayout->Release();
    if (_pVertexShader) _pVertexShader->Release();
    if (_pPixelShader) _pPixelShader->Release();
    if (_pRenderTargetView) _pRenderTargetView->Release();
    if (_pSwapChain) _pSwapChain->Release();
    if (_pImmediateContext) _pImmediateContext->Release();
    if (_pd3dDevice) _pd3dDevice->Release();
	if (_depthStencilView) _depthStencilView->Release();
	if (_depthStencilBuffer) _depthStencilBuffer->Release();

	if (DSLessEqual) DSLessEqual->Release();
	if (RSCullNone) RSCullNone->Release();

	if (CCWcullMode) CCWcullMode->Release();
	if (CWcullMode) CWcullMode->Release();

	if (_camera)
	{
		delete _camera;
		_camera = nullptr;
	}

	//delete _normandy;
	//_normandy = nullptr;

	for (auto gameObject : _gameObjects)
	{
		if (gameObject)
		{
			delete gameObject;
			gameObject = nullptr;
		}
	}

	Base::Cleanup();
}
void Application::Update(float deltaTime)
{
	_newTime = GetTickCount();
	_deltaTime = (float)(_newTime - _oldTime) / 1000;
	_oldTime = _newTime;

	if (_deltaTime > 0.016f) _deltaTime = 0.016f;
	if (_deltaTime < 0.001f) _deltaTime = 0.001f;

	_totalTime += _deltaTime;
	
	// Update camera
	//float angleAroundZ = XMConvertToRadians(_cameraOrbitAngleXZ);
	//float x = _cameraOrbitRadius * cos(angleAroundZ);
	//float z = _cameraOrbitRadius * sin(angleAroundZ);

	//XMFLOAT3 cameraPos = _camera->GetPosition();
	//cameraPos.x = x;
	//cameraPos.z = z;

	//_camera->SetPosition(cameraPos);
	_camera->Update();

	// Move GameObjects
	for (auto gameObject : _gameObjects) 
	{
		gameObject->GetRigidBody().AddForce(Vector3(0.0f, GRAVITY * gameObject->GetRigidBody().GetMass(), 0.0f));
		gameObject->Update(_deltaTime);
	}

	for (int i = 1; i < _gameObjects.size(); i++)
	{
		if (CollisionManager::GetInstance().AABBCollisionCheck(_gameObjects[i]->GetRigidBody(), _gameObjects[0]->GetRigidBody()))
		{
			CollisionManager::GetInstance().ResolveInterpenetration(_gameObjects[i]->GetRigidBody(), _gameObjects[0]->GetRigidBody());
			CollisionManager::GetInstance().ResolveCollision(_gameObjects[i]->GetRigidBody(), _gameObjects[0]->GetRigidBody());
		}

		for (int j = i; j < _gameObjects.size(); j++)
		{
			if (i != j)
			{
				//if (CollisionManager::GetInstance().AABBCollisionCheck(_gameObjects[i]->GetParticleModel(), _gameObjects[j]->GetParticleModel()))
				//{
				//	CollisionManager::GetInstance().ResolveInterpenetration(_gameObjects[i]->GetParticleModel(), _gameObjects[j]->GetParticleModel());
				//	CollisionManager::GetInstance().ResolveCollision(_gameObjects[i]->GetParticleModel(), _gameObjects[j]->GetParticleModel());
				//}

				if (CollisionManager::GetInstance().RigidBodyCollision(_gameObjects[i]->GetRigidBody(), _gameObjects[j]->GetRigidBody()))
				{
					//CollisionManager::GetInstance().ResolveInterpenetration(_gameObjects[i]->GetRigidBody(), _gameObjects[j]->GetRigidBody());
					//CollisionManager::GetInstance().ResolveCollision(_gameObjects[i]->GetRigidBody(), _gameObjects[j]->GetRigidBody());
				}
			}
			else
				continue;
		}
	}
}

void Application::Draw()
{
    //
    // Clear buffers
    //

	float ClearColor[4] = { 0.4f, 0.4f, 0.5f, 1.0f }; // red,green,blue,alpha
    _pImmediateContext->ClearRenderTargetView(_pRenderTargetView, ClearColor);
	_pImmediateContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    //
    // Setup buffers and render scene
    //

	_pImmediateContext->IASetInputLayout(_pVertexLayout);

	_pImmediateContext->VSSetShader(_pVertexShader, nullptr, 0);
	_pImmediateContext->PSSetShader(_pPixelShader, nullptr, 0);

	_pImmediateContext->VSSetConstantBuffers(0, 1, &_pConstantBuffer);
	_pImmediateContext->PSSetConstantBuffers(0, 1, &_pConstantBuffer);
	_pImmediateContext->PSSetSamplers(0, 1, &_pSamplerLinear);

    ConstantBuffer cb;

	XMFLOAT4X4 viewAsFloats = _camera->GetView();
	XMFLOAT4X4 projectionAsFloats = _camera->GetProjection();

	XMMATRIX view = XMLoadFloat4x4(&viewAsFloats);
	XMMATRIX projection = XMLoadFloat4x4(&projectionAsFloats);

	cb.View = XMMatrixTranspose(view);
	cb.Projection = XMMatrixTranspose(projection);
	
	cb.light = basicLight;
	cb.EyePosW = _camera->GetPosition();

	// Render all scene objects
	for (auto gameObject : _gameObjects)
	{
		// Get render material
		Appearance * appearance = gameObject->GetAppearance();
		Material material = appearance->GetMaterial();

		// Copy material to shader
		cb.surface.AmbientMtrl = material.ambient;
		cb.surface.DiffuseMtrl = material.diffuse;
		cb.surface.SpecularMtrl = material.specular;

		// Set world matrix
		cb.World = XMMatrixTranspose(gameObject->GetTransform()->GetWorldMatrix());

		// Set texture
		if (appearance->HasTexture())
		{
			ID3D11ShaderResourceView * textureRV = appearance->GetTextureRV();
			_pImmediateContext->PSSetShaderResources(0, 1, &textureRV);
			cb.HasTexture = 1.0f;
		}
		else
		{
			cb.HasTexture = 0.0f;
		}

		// Update constant buffer
		_pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);

		// Draw object
	//	if(gameObject->GetType() != "Normandy")
			gameObject->Draw(_pImmediateContext);
	}

    //
    // Present our back buffer to our front buffer
    //
    _pSwapChain->Present(0, 0);
}
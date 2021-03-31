#pragma once
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>

#include "resource.h"

class Base
{
protected:
	Base();
	 ~Base();

	 void Cleanup();

	HRESULT Initialise(HINSTANCE _instance, int _cmdShow);
	HRESULT InitDevice();
private:
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	HRESULT InitShadersAndInputLayout();

	// Shouldn't need if reading in
	HRESULT InitVertexBuffer();
	HRESULT InitIndexBuffer();
	// 

	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

protected:
	HINSTANCE               _hInst;
	HWND                    _hWnd;
	D3D_DRIVER_TYPE         _driverType;
	D3D_FEATURE_LEVEL       _featureLevel;
	ID3D11Device*           _pd3dDevice;
	ID3D11DeviceContext*    _pImmediateContext;
	IDXGISwapChain*         _pSwapChain;
	ID3D11RenderTargetView* _pRenderTargetView;
	ID3D11VertexShader*     _pVertexShader;
	ID3D11PixelShader*      _pPixelShader;
	ID3D11InputLayout*      _pVertexLayout;

	ID3D11SamplerState * _pSamplerLinear = nullptr;
	ID3D11DepthStencilView* _depthStencilView = nullptr;
	ID3D11Texture2D* _depthStencilBuffer = nullptr;

	ID3D11DepthStencilState* DSLessEqual;
	ID3D11RasterizerState* RSCullNone;

	ID3D11RasterizerState* CCWcullMode;
	ID3D11RasterizerState* CWcullMode;

	ID3D11Buffer*           _pConstantBuffer;

	// Shouldn't need if reading in
	ID3D11Buffer*           _pVertexBuffer;
	ID3D11Buffer*           _pIndexBuffer;
	
	ID3D11Buffer*           _pPlaneVertexBuffer;
	ID3D11Buffer*           _pPlaneIndexBuffer;
	//

	UINT _WindowHeight;
	UINT _WindowWidth;
	UINT _renderHeight = 1080;
	UINT _renderWidth = 1920;

	float _oldTime;
	float _newTime;
	float _deltaTime;
	float _totalTime;

private:


};
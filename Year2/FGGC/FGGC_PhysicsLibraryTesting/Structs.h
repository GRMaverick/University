 #pragma once
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <fstream>				
#include <vector>	
#include <map>	
#include <string>
#include <random>

using namespace std;
using namespace DirectX;

struct SurfaceInfo
{
	XMFLOAT4 AmbientMtrl;
	XMFLOAT4 DiffuseMtrl;
	XMFLOAT4 SpecularMtrl;
};
struct Light
{
	XMFLOAT4 AmbientLight;
	XMFLOAT4 DiffuseLight;
	XMFLOAT4 SpecularLight;

	float SpecularPower;
	XMFLOAT3 LightVecW;
};
struct ConstantBuffer
{
	XMMATRIX World;
	XMMATRIX View;
	XMMATRIX Projection;

	SurfaceInfo surface;

	Light light;

	XMFLOAT3 EyePosW;
	float HasTexture;
};

struct SimpleVertex
{
	XMFLOAT3 PosL;
	XMFLOAT3 NormL;
	XMFLOAT2 Tex;

	bool operator<(const SimpleVertex other) const
	{
		return memcmp((void*)this, (void*)&other, sizeof(SimpleVertex)) > 0;
	};
};
struct Geometry {
	ID3D11Buffer * VertexBuffer;
	ID3D11Buffer * IndexBuffer;
	UINT VBStride;
	UINT VBOffset;
	UINT IndexCount;
};
//struct ConstantBuffer
//{
//	XMMATRIX												mWorld;
//	XMMATRIX												mView;
//	XMMATRIX												mProjection;
//	XMFLOAT4												DiffuseMtrl;
//	XMFLOAT4												DiffuseLight;
//	XMFLOAT4												AmbientMtrl;
//	XMFLOAT4												AmbientLight;
//	XMFLOAT4												SpecularMtrl;
//	XMFLOAT4												SpecularLight;
//	XMFLOAT3												EyePosW;
//	float															SpecularPower;
//	XMFLOAT3												LightVecW;
//};
struct FogConstantBuffer
{
	float fogStart;
	float fogEnd;
	float padding1;
	float padding2;
};

//
// Height Mapping
//TexCoor
struct VertexType
{
	XMFLOAT3 position;
	XMFLOAT4 color;
};
struct HeightMapType
{
	float x, y, z;
};
#pragma once

#include <vector>
#include <list>
#include <Windows.h>
#include <d3d11_1.h>
#include <DirectXCollision.h>
#include <DirectXMath.h>

using namespace std;
using namespace DirectX;

struct Geometry
{
	ID3D11Buffer * vertexBuffer;
	ID3D11Buffer * indexBuffer;
	int numberOfIndices;

	UINT vertexBufferStride;
	UINT vertexBufferOffset;
};
struct Material
{
	XMFLOAT4 diffuse;
	XMFLOAT4 ambient;
	XMFLOAT4 specular;
	float specularPower;
};
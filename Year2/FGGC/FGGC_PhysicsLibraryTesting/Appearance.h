#pragma once
#pragma comment(lib, "DPhysX.lib")

#include <directxmath.h>
#include <d3d11_1.h>
#include "Structs.h"
#include "DPhysX Framework\Particle.h"
//#include "DPhysX Framework\Transform.h"

using namespace DirectX;

struct Material
{
	XMFLOAT4 diffuse;
	XMFLOAT4 ambient;
	XMFLOAT4 specular;
	float specularPower;
};

class Appearance
{
public:
	Appearance(Geometry geometry, Material material);
	~Appearance();

	Geometry GetGeometryData() const { return _geometry; }

	Material GetMaterial() const { return _material; }

	void SetTextureRV(ID3D11ShaderResourceView * textureRV) { _textureRV = textureRV; }
	ID3D11ShaderResourceView * GetTextureRV() const { return _textureRV; }
	bool HasTexture() const { return _textureRV ? true : false; }

	void Draw(ID3D11DeviceContext * pImmediateContext);

private:
	Geometry _geometry;
	Material _material;

	ID3D11ShaderResourceView * _textureRV;
};


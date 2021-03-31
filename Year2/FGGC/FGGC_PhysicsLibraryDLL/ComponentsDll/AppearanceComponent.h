#pragma once

#ifdef COMPONENTSDLL_EXPORTS
#define COMPONENTSDLL_API __declspec(dllexport)
#else
#define COMPONENTSDLL_API __declspec(dllimport)
#endif

#define Texture ID3D11ShaderResourceView

#include "Commons.h"


class Appearance
{
public:
	COMPONENTSDLL_API Appearance();
	COMPONENTSDLL_API Appearance(Geometry geometry, Material material);
	COMPONENTSDLL_API ~Appearance();

	COMPONENTSDLL_API void Draw(ID3D11DeviceContext * pImmediateContext);

	COMPONENTSDLL_API inline bool HasTexture() const { return mTextureRV ? true : false; }
	COMPONENTSDLL_API inline void SetTextureRV(ID3D11ShaderResourceView * textureRV) { mTextureRV = textureRV; }

	COMPONENTSDLL_API inline Material GetMaterial() const { return mMaterial; }
	COMPONENTSDLL_API inline Geometry GetGeometryData() const { return mGeometry; }
	COMPONENTSDLL_API inline ID3D11ShaderResourceView * GetTextureRV() const { return mTextureRV; }

private:
	Geometry mGeometry;
	Material mMaterial;

	ID3D11ShaderResourceView * mTextureRV;
};
#include "stdafx.h"
#include "AppearanceComponent.h"
#include <stdexcept>

Appearance::Appearance()
{

}
Appearance::Appearance(Geometry geometry, Material material)
{
	mGeometry = geometry;
	mMaterial = material;
	mTextureRV = nullptr;
}
Appearance::~Appearance()
{
}

void Appearance::Draw(ID3D11DeviceContext * pImmediateContext)
{
	// NOTE: We are assuming that the constant buffers and all other draw setup has already taken place

	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &mGeometry.vertexBuffer, &mGeometry.vertexBufferStride, &mGeometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(mGeometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(mGeometry.numberOfIndices, 0, 0);
}
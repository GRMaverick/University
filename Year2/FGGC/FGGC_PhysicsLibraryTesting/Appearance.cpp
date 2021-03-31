#include "Appearance.h"


Appearance::Appearance(Geometry geometry, Material material) : _geometry(geometry), _material(material)
{
	_textureRV = nullptr;
}


Appearance::~Appearance()
{
}

void Appearance::Draw(ID3D11DeviceContext * pImmediateContext)
{
	// NOTE: We are assuming that the constant buffers and all other draw setup has already taken place

	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &_geometry.VertexBuffer, &_geometry.VBStride, &_geometry.VBOffset);
	pImmediateContext->IASetIndexBuffer(_geometry.IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(_geometry.IndexCount, 0, 0);
}
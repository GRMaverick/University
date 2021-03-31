#include "pch.h"
#include "RenderComponent.h"

RenderComponent::RenderComponent(void)
{
	m_Texture = nullptr;
	m_VShader = nullptr;
	m_PShader = nullptr;
}
RenderComponent::RenderComponent(Geometry geometry, Material material)
{
	m_Texture = nullptr;
	m_Material = material;
}
RenderComponent::~RenderComponent()
{
	if (m_Texture)			m_Texture->Release();
	if (m_VShader)		m_VShader->Release();
	if (m_PShader)		m_PShader->Release();
}

void RenderComponent::Render(ID3D11DeviceContext * pImmediateContext)
{
	for (Geometry geo : m_Geometries)
	{
		pImmediateContext->IASetPrimitiveTopology(geo.Topology);
		pImmediateContext->IASetVertexBuffers(0, 1, &geo.VertexBuffer, &geo.VBStride, &geo.VBOffset);
		pImmediateContext->IASetIndexBuffer(geo.IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
		pImmediateContext->DrawIndexed(geo.IndexCount, 0, 0);
	}
}

RenderComponent* RenderComponent::SetMaterial(Material material)
{
	m_Material = material;
	return this;
}

RenderComponent* RenderComponent::SetGeometry(std::vector<Geometry> geometries)
{
	m_Geometries = geometries;
	return this;
}
RenderComponent* RenderComponent::AddGeometry(Geometry geometry)
{
	m_Geometries.push_back(geometry);
	return this;
}
RenderComponent* RenderComponent::SetTexture(ID3D11ShaderResourceView * texture)
{
	m_Texture = texture;
	return this;
}
RenderComponent* RenderComponent::SetVertexShader(ID3D11VertexShader* shader)
{
	m_VShader = shader;
	return this;
}
RenderComponent* RenderComponent::SetPixelShader(ID3D11PixelShader* shader)
{
	m_PShader = shader;
	return this;
}

Material RenderComponent::GetMaterial(void)
{
	return m_Material;
}
std::vector<Geometry> RenderComponent::GetGeometries(void)
{
	return m_Geometries;
}	
ID3D11ShaderResourceView* RenderComponent::GetTexture(void)
{
	return m_Texture;
}
ID3D11VertexShader* RenderComponent::GetVertexShader(void)
{
	return m_VShader;
}
ID3D11PixelShader* RenderComponent::GetPixelShader(void)
{
	return m_PShader;
}
bool RenderComponent::HasTexture(void)
{
	return m_Texture ? true : false;
}
#pragma once

#include <directxmath.h>
#include <d3d11_1.h>

#include <vector>

#include "Structs.h"
#include "IComponent.h"

using namespace DirectX;

class RenderComponent : public IComponent
{
public:
	RenderComponent(void);
	RenderComponent(Geometry geometry, Material material);
	~RenderComponent();

	void SetOwnerName(const std::string& name) { IComponent::SetOwnerName(name); }
	std::string GetOwnerName(void) { return IComponent::GetOwnerName(); }

	void Render(ID3D11DeviceContext* pImmediateContext);

	RenderComponent* SetMaterial(Material material);
	RenderComponent* AddGeometry(Geometry geometry);
	RenderComponent* SetPixelShader(ID3D11PixelShader* shader);
	RenderComponent* SetVertexShader(ID3D11VertexShader* shader);
	RenderComponent* SetTexture(ID3D11ShaderResourceView* texture);
	RenderComponent* SetGeometry(std::vector<Geometry> geometries);

	Material GetMaterial(void);
	ID3D11PixelShader* GetPixelShader(void);
	ID3D11VertexShader* GetVertexShader(void);
	std::vector<Geometry> GetGeometries(void);
	ID3D11ShaderResourceView* GetTexture(void);

	bool HasTexture(void);

private:
	Material										m_Material;
	std::vector<Geometry>				m_Geometries;
	ID3D11ShaderResourceView*	m_Texture;
	ID3D11VertexShader*					m_VShader;
	ID3D11PixelShader*					m_PShader;
};	


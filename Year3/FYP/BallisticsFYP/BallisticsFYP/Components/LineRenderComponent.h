#pragma once

#include <d3d11_1.h>
#include <DirectXColors.h>

#include <Vector3.h>

#include "Structs.h"
#include "IComponent.h"
#include "..\Common\DirectXHelper.h"
#include "..\Common\DeviceResources.h"

using namespace DirectX;

struct ColourVertex
{
	XMFLOAT3 Position;
	XMFLOAT4 Colour;

	ColourVertex(void)
	{
		Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		Colour = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	ColourVertex(XMFLOAT3 position, XMFLOAT4 colour)
	{
		Position = position;
		Colour = colour;
	}
};

struct RenderLine
{
	Mathematics::Structures::Vector3 Start = Mathematics::Structures::Vector3(0.0f, 0.0f, 0.0f);
	Mathematics::Structures::Vector3 End = Mathematics::Structures::Vector3(0.0f, 0.0f, 0.0f);

	RenderLine(void)
	{
		Start = Mathematics::Structures::Vector3(0.0f, 0.0f, 0.0f);
		End = Mathematics::Structures::Vector3(0.0f, 0.0f, 0.0f);
	}
	RenderLine(Mathematics::Structures::Vector3 start, Mathematics::Structures::Vector3 end)
	{
		Start = start;
		End = end;
	}
};

class LineRenderComponent : public IComponent
{
public:
	LineRenderComponent(void) { }
	LineRenderComponent(const std::string& name) { m_LineName = name; }
	~LineRenderComponent(void) { }

	void SetOwnerName(const std::string& name) { IComponent::SetOwnerName(name); }
	std::string GetOwnerName(void) { return IComponent::GetOwnerName(); }
	

	LineRenderComponent* AddLine(RenderLine line)
	{
		m_Lines.push_back(line);
		return this;
	}
	LineRenderComponent* AddLine(Mathematics::Structures::Vector3 start, Mathematics::Structures::Vector3 end)
	{
		RenderLine line(start, end);
		m_Lines.push_back(line);

		return this; 
	}
	LineRenderComponent* SetLineColour(XMVECTOR colour) { m_Colour = colour; return this; }

	std::string GetLineName(void) { return m_LineName; }
	static ID3D11InputLayout* GetInputLayout(void) { return m_pInputLayout; }
	static ID3D11PixelShader* GetPixelShader(void) { return m_pPixelShader.Get(); }
	static ID3D11VertexShader* GetVertexShader(void) { return m_pVertexShader.Get(); }

	void RemoveLines(void) 
	{
		m_Lines.clear();
	}
	
	static void InitialiseShader(const std::shared_ptr<DX::DeviceResources>& deviceResources)
	{
		auto loadVSTask = DX::ReadDataAsync(L"LineVertexShader.cso");
		auto loadPSTask = DX::ReadDataAsync(L"LinePixelShader.cso");

		auto createVSTask = loadVSTask.then([&](const std::vector<byte>& fileData)
		{
			DX::ThrowIfFailed(deviceResources->GetD3DDevice()->CreateVertexShader(&fileData[0], fileData.size(), nullptr, &m_pVertexShader));

			static const D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			DX::ThrowIfFailed(deviceResources->GetD3DDevice()->CreateInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), &fileData[0], fileData.size(), &m_pInputLayout));
		});

		auto createPSTask = loadPSTask.then([&](const std::vector<byte>& fileData)
		{ 
			ID3D11PixelShader* pPixelShader;
			DX::ThrowIfFailed(deviceResources->GetD3DDevice()->CreatePixelShader(&fileData[0], fileData.size(), nullptr, &m_pPixelShader));
		});
	}
	void InitialiseBuffers(ID3D11Device* pDevice, int maxSize)
	{
		m_MaxLineCount = maxSize;

		std::vector<ColourVertex> vertices;
		for (int i = 0; i < maxSize; ++i)
		{
			vertices.push_back(ColourVertex());
		}

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(ColourVertex) * m_MaxLineCount;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = &vertices[0];
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;

		DX::ThrowIfFailed(pDevice->CreateBuffer(&bd, &InitData, &m_Geometry.VertexBuffer));

		m_Geometry.VBOffset = 0;
		m_Geometry.VBStride = sizeof(ColourVertex);
		m_Geometry.Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
	}
	void UpdateResources(ID3D11DeviceContext* pImmediateContext)
	{
		if ((m_Lines.size() * 2) < m_MaxLineCount-1)
		{
			D3D11_MAPPED_SUBRESOURCE mappedResource;
			ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

			XMFLOAT4 colour;
			XMStoreFloat4(&colour, m_Colour);

			std::vector<ColourVertex> vertices;
			for (int i = 0; i < m_Lines.size(); ++i)
			{
				vertices.push_back(ColourVertex(XMFLOAT3(m_Lines[i].Start.x, m_Lines[i].Start.y, m_Lines[i].Start.z), colour));
				vertices.push_back(ColourVertex(XMFLOAT3(m_Lines[i].End.x, m_Lines[i].End.y, m_Lines[i].End.z), colour));
			}

			if (vertices.size() > 0)
			{
				pImmediateContext->Map(m_Geometry.VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
				memcpy(mappedResource.pData, &vertices[0], sizeof(ColourVertex) * vertices.size());
				pImmediateContext->Unmap(m_Geometry.VertexBuffer, 0);
			}
		}
	}
	void Render(ID3D11DeviceContext* pImmediateContext)
	{
		pImmediateContext->IASetPrimitiveTopology(m_Geometry.Topology);
		pImmediateContext->IASetVertexBuffers(0, 1, &m_Geometry.VertexBuffer, &m_Geometry.VBStride, &m_Geometry.VBOffset);
		pImmediateContext->Draw(m_Lines.size() * 2, 0);
	}

private:
	int m_MaxLineCount;
	XMVECTOR m_Colour;
	Geometry m_Geometry;
	std::string m_LineName;
	std::vector<RenderLine> m_Lines;

	static ID3D11InputLayout* m_pInputLayout;
	static Microsoft::WRL::ComPtr<ID3D11PixelShader>		m_pPixelShader;
	static Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_pVertexShader;
};
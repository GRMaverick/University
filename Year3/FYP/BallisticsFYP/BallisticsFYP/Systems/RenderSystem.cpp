///
/// Render System.cpp
/// Ryan Buxton – Ballistics FYP
///

#include "pch.h"
#include <iostream>
#include "IMediator.h"

#include "..\Common\DirectXHelper.h"

#include "IEntity.h"
#include "Structs.h"
#include "RenderSystem.h"
#include "DelegateFactory.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "LineRenderComponent.h"
#include "StaticCameraComponent.h"

#include "ActiveCameraMessage.h"
#include "RequestActiveCamera.h"

#include "TimerManager.h"
#include "EntityManager.h"
#include "ComponentManager.h"

RenderSystem::RenderSystem(void)
{
	m_pInputLayout = nullptr;
	m_pSamplerState = nullptr;
	m_pConstantBuffer = nullptr;
}
RenderSystem::~RenderSystem(void)
{
	m_pInputLayout.Reset();
	m_pSamplerState.Reset();
	m_pConstantBuffer.Reset();
}

void RenderSystem::Initialise(const std::shared_ptr<DX::DeviceResources>& pResources)
{
	m_pDeviceResources = pResources;
	
	auto loadVSTask = DX::ReadDataAsync(L"BasicVertexShader.cso");
	auto loadPSTask = DX::ReadDataAsync(L"BasicPixelShader.cso");

	auto createVSTask = loadVSTask.then([this](const std::vector<byte>& fileData) 
	{
		DX::ThrowIfFailed(m_pDeviceResources->GetD3DDevice()->CreateVertexShader(&fileData[0], fileData.size(), nullptr, &m_pVertexShader));

		static const D3D11_INPUT_ELEMENT_DESC vertexDesc[] = 
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		DX::ThrowIfFailed(m_pDeviceResources->GetD3DDevice()->CreateInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), &fileData[0], fileData.size(), &m_pInputLayout));
	});

	auto createPSTask = loadPSTask.then([this](const std::vector<byte>& fileData) 
	{
		DX::ThrowIfFailed(m_pDeviceResources->GetD3DDevice()->CreatePixelShader(	&fileData[0], fileData.size(), nullptr, &m_pPixelShader));
	});

	CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
	DX::ThrowIfFailed(m_pDeviceResources->GetD3DDevice()->CreateBuffer(&constantBufferDesc, nullptr, &m_pConstantBuffer));

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	m_pDeviceResources->GetD3DDevice()->CreateSamplerState(&sampDesc, &m_pSamplerState);
}

void RenderSystem::RegisterMediator(std::shared_ptr<IMediator> pMediator)
{
	m_pMediator = pMediator;
	m_pMediator->RegisterReceiveCallback(DELEGATE(&RenderSystem::Receive, this));
}

void RenderSystem::Receive(IMessage* pMessage)
{
	ActiveCameraMessage* cameraMessage = dynamic_cast<ActiveCameraMessage*>(pMessage);
	if (cameraMessage != nullptr)
	{
		m_pActiveCamera = dynamic_cast<ICameraComponent*>(ComponentsManager->GetComponent(cameraMessage->GetActiveCamera(), "Camera"));
	}
}
void RenderSystem::Update(DX::StepTimer const& timer)
{
	std::string trackingFrame = std::string("Frame" + std::to_string(timer.GetFrameCount()));
	TimerManager::Instance()->GetTimer("RenderTimer")->StartTracking(trackingFrame, timer.GetFrameCount());
	{
		RequestActiveCamera* pActiveCamMessage = new RequestActiveCamera();
		m_pMediator->Send(pActiveCamMessage);
		delete pActiveCamMessage;

		D3D11_VIEWPORT viewport = m_pDeviceResources->GetScreenViewport();
		m_pDeviceResources->GetD3DDeviceContext()->RSSetViewports(1, &viewport);
		m_pDeviceResources->GetD3DDeviceContext()->ClearRenderTargetView(m_pDeviceResources->GetBackBufferRenderTargetView(), Colors::CornflowerBlue);
		m_pDeviceResources->GetD3DDeviceContext()->ClearDepthStencilView(m_pDeviceResources->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		//m_pDeviceResources->GetD3DDeviceContext()->IASetInputLayout(m_pInputLayout.Get());

		Light basicLight;
		basicLight.AmbientLight = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		basicLight.DiffuseLight = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		basicLight.SpecularLight = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
		basicLight.SpecularPower = 20.0f;
		basicLight.LightVecW = XMFLOAT3(0.0f, 1.0f, -3.0f);

		m_pDeviceResources->GetD3DDeviceContext()->VSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
		m_pDeviceResources->GetD3DDeviceContext()->PSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
		m_pDeviceResources->GetD3DDeviceContext()->PSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());

		ID3D11RenderTargetView *const targets[1] = { m_pDeviceResources->GetBackBufferRenderTargetView() };
		m_pDeviceResources->GetD3DDeviceContext()->OMSetRenderTargets(1, targets, m_pDeviceResources->GetDepthStencilView());

		ConstantBuffer cb;
		cb.light = basicLight;

		XMMATRIX view = m_pActiveCamera->GetView();
		XMMATRIX projection = m_pActiveCamera->GetProjection();

		cb.View = XMMatrixTranspose(view);
		cb.Projection = XMMatrixTranspose(projection);

		XMFLOAT3 camPosition;
		XMStoreFloat3(&camPosition, m_pActiveCamera->GetPosition());
		cb.EyePosW = camPosition;

		for (std::string entity : EntitiesManager->GetEntities())
		{
			RenderComponent* pRenderer = nullptr;
			TransformComponent* pTransform = nullptr;
			std::vector<LineRenderComponent*> pLineRenders;

			for (IComponent* pComponent : ComponentsManager->GetAllComponentsForEntity(entity))
			{
				if (RenderComponent* pTempComponent = dynamic_cast<RenderComponent*>(pComponent))
				{
					pRenderer = pTempComponent;
				}
				if (TransformComponent* pTempComponent = dynamic_cast<TransformComponent*>(pComponent))
				{
					pTransform = pTempComponent;
				}
				if (LineRenderComponent* pTempComponent = dynamic_cast<LineRenderComponent*>(pComponent))
				{
					pLineRenders.push_back(pTempComponent);
				}
			}

			for each(LineRenderComponent* pLineRender in pLineRenders)
			{
				pLineRender->UpdateResources(m_pDeviceResources->GetD3DDeviceContext());

				m_pDeviceResources->GetD3DDeviceContext()->IASetInputLayout(pLineRender->GetInputLayout());

				m_pDeviceResources->GetD3DDeviceContext()->VSSetShader(pLineRender->GetVertexShader(), nullptr, 0);
				m_pDeviceResources->GetD3DDeviceContext()->PSSetShader(pLineRender->GetPixelShader(), nullptr, 0);

				TransformComponent transform = TransformComponent();
				transform.SetScale(Vector3(1.0f));
				transform.SetPosition(Vector3(0.0f));
				transform.SetRotation(Vector3(0.0f));
				transform.Update();

				cb.World = transform.GetWorldMatrix();
				m_pDeviceResources->GetD3DDeviceContext()->UpdateSubresource(m_pConstantBuffer.Get(), 0, nullptr, &cb, 0, 0);

				pLineRender->Render(m_pDeviceResources->GetD3DDeviceContext());
			}

			if (pRenderer && pTransform)
			{
				pTransform->Update();

				m_pDeviceResources->GetD3DDeviceContext()->IASetInputLayout(m_pInputLayout.Get());
				if (pRenderer->GetVertexShader() != nullptr && pRenderer->GetPixelShader() != nullptr)
				{
					m_pDeviceResources->GetD3DDeviceContext()->VSSetShader(pRenderer->GetVertexShader(), nullptr, 0);
					m_pDeviceResources->GetD3DDeviceContext()->PSSetShader(pRenderer->GetPixelShader(), nullptr, 0);
				}
				else
				{
					m_pDeviceResources->GetD3DDeviceContext()->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
					m_pDeviceResources->GetD3DDeviceContext()->PSSetShader(m_pPixelShader.Get(), nullptr, 0);
				}

				cb.surface.AmbientMtrl = pRenderer->GetMaterial().ambient;
				cb.surface.DiffuseMtrl = pRenderer->GetMaterial().diffuse;
				cb.surface.SpecularMtrl = pRenderer->GetMaterial().specular;

				cb.World = XMMatrixTranspose(pTransform->GetWorldMatrix());

				if (pRenderer->HasTexture())
				{
					ID3D11ShaderResourceView * textureRV = pRenderer->GetTexture();
					m_pDeviceResources->GetD3DDeviceContext()->PSSetShaderResources(0, 1, &textureRV);
					cb.HasTexture = 1.0f;
				}
				else
				{
					cb.HasTexture = 0.0f;
				}

				m_pDeviceResources->GetD3DDeviceContext()->UpdateSubresource(m_pConstantBuffer.Get(), 0, nullptr, &cb, 0, 0);

				pRenderer->Render(m_pDeviceResources->GetD3DDeviceContext());
			}
		}
	}
	TimerManager::Instance()->GetTimer("RenderTimer")->EndTracking(trackingFrame);
}
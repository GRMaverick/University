#ifndef __RENDER_SYSTEM_H__
#define __RENDER_SYSTEM_H__

///
/// RenderSystem.h
/// Ryan Buxton – Ballistics FYP
///

#include "ISystem.h"
#include "..\Common\DeviceResources.h"

class IMessage;
class IMediator;
class ICameraComponent;

class RenderSystem : public ISystem
{
public:
	RenderSystem(void);
	~RenderSystem(void);

	void Initialise(const std::shared_ptr<DX::DeviceResources>& pResources);

	void Receive(IMessage* pMessage);
	void RegisterMediator(std::shared_ptr<IMediator> pMediator);
	
	void Update(DX::StepTimer const& timer) override;

private:
	std::shared_ptr<IMediator>									m_pMediator;
	ICameraComponent*												m_pActiveCamera;
	std::shared_ptr<DX::DeviceResources>					m_pDeviceResources;

	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pConstantBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>		m_pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>	m_pSamplerState;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>		m_pPixelShader;
};

#endif /// __RENDER_SYSTEM_H__
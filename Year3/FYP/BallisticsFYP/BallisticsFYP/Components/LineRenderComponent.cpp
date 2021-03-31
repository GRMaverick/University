#include "pch.h"
#include "LineRenderComponent.h"

ID3D11InputLayout*		LineRenderComponent::m_pInputLayout = nullptr;
Microsoft::WRL::ComPtr<ID3D11PixelShader>			LineRenderComponent::m_pPixelShader = nullptr;
Microsoft::WRL::ComPtr<ID3D11VertexShader>		LineRenderComponent::m_pVertexShader = nullptr;
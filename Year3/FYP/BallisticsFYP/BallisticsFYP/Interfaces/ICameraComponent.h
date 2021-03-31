#pragma once

#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>

#include "IComponent.h"

using namespace DirectX;

class ICameraComponent : public IComponent
{
public:
	virtual void Update() = 0;

	virtual bool IsActive(void) = 0;
	virtual void SetActive(bool isActive) = 0;

	virtual void Strafe(const float& _amount) = 0;
	virtual void Advance(const float& _amount) = 0;
	virtual void Rotate(const float& _pitch, const float& _yaw) = 0;

	virtual float GetYaw(void) = 0;
	virtual float GetPitch(void) = 0;

	virtual XMVECTOR GetUp(void) = 0;
	virtual XMVECTOR GetLookAt(void) = 0;
	virtual XMVECTOR GetPosition(void) = 0;

	virtual XMMATRIX GetView(void) = 0;
	virtual XMMATRIX GetProjection(void) = 0;

	virtual void Reshape(const float& _windowWidth, const float& _windowHeight, const float& _nearDepth, const float& _farDepth) = 0;
};
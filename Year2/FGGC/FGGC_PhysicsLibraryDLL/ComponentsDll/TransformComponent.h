#pragma once

#ifdef COMPONENTSDLL_EXPORTS
	#define COMPONENTSDLL_API __declspec(dllexport)
#else
	#define COMPONENTSDLL_API __declspec(dllimport)
#endif

#include "Commons.h"

class Transform
{
public:
	COMPONENTSDLL_API Transform();
	COMPONENTSDLL_API ~Transform();

	// Setters and Getters for position/rotation/scale
	COMPONENTSDLL_API void SetPosition(XMFLOAT3 position);
	COMPONENTSDLL_API void SetPosition(float x, float y, float z);

	COMPONENTSDLL_API inline XMFLOAT3 GetPosition() const { return mPosition; }
	COMPONENTSDLL_API inline XMFLOAT3 GetLastPosition() const { return mPreviousPosition; }

	COMPONENTSDLL_API inline void SetScale(XMFLOAT3 scale) { mScale = scale; }
	COMPONENTSDLL_API inline void SetScale(float x, float y, float z) { mScale.x = x; mScale.y = y; mScale.z = z; }

	COMPONENTSDLL_API inline XMFLOAT3 GetScale() const { return mScale; }

	COMPONENTSDLL_API inline void SetRotation(XMFLOAT3 rotation) { mRotation = rotation; }
	COMPONENTSDLL_API inline void SetRotation(float x, float y, float z) { mRotation.x = x; mRotation.y = y; mRotation.z = z; }

	COMPONENTSDLL_API inline XMFLOAT3 GetRotation() const { return mRotation; }

	COMPONENTSDLL_API inline XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&mWorld); }

	COMPONENTSDLL_API inline void SetParent(Transform * parent) { mParent = parent; }

	COMPONENTSDLL_API void Update(float t);

private:
	XMFLOAT3				mPreviousPosition;
	XMFLOAT3				mPosition;
	XMFLOAT3				mRotation;
	XMFLOAT3				mScale;

	XMFLOAT4X4			mWorld;

	Transform *				mParent;
};


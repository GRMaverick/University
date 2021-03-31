#ifndef __DPHYSX_TRANSFORM__
#define __DPHYSX_TRANSFORM__

#ifndef DPHYSX_DLL_EXPORT
#define DPHYSX_DLL __declspec(dllexport)
#else
#define DPHYSX_DLL __declspec(dllimport)
#endif

#include "DPhyXMaths.h"
#include <d3d11.h>
#include <DirectXMath.h>

using namespace std;
using namespace DirectX;

class Transform
{
public:
	DPHYSX_DLL Transform(void);
	DPHYSX_DLL ~Transform(void);

	DPHYSX_DLL void Update(float deltaTime);

	DPHYSX_DLL void SetParent(Transform* transform);
	DPHYSX_DLL void SetWorld(XMFLOAT4X4 world);
	DPHYSX_DLL void SetPosition(Vector3 position);
	DPHYSX_DLL void SetPosition(float x, float y, float z);
	DPHYSX_DLL void SetRotation(Vector3 rotation);
	DPHYSX_DLL void SetRotation(float x, float y, float z);
	DPHYSX_DLL void SetScale(Vector3 scale);
	DPHYSX_DLL void SetScale(float x, float y, float z);
	DPHYSX_DLL void SetLastPosition(Vector3 lPosition);
	DPHYSX_DLL void SetLastPosition(float x, float y, float z);

	DPHYSX_DLL Transform* GetParent(void) const;
	DPHYSX_DLL XMMATRIX GetWorldMatrix(void) const;
	DPHYSX_DLL Vector3 GetPosition(void) const;
	DPHYSX_DLL Vector3 GetRotation(void) const;
	DPHYSX_DLL Vector3 GetScale(void) const;
	DPHYSX_DLL Vector3 GetLastPosition(void) const;


private:
	Vector3 mPreviousPosition;
	Vector3 mPosition;
	Vector3 mRotation;
	Vector3 mScale;

	XMFLOAT4X4 mWorld;

	Transform* mParent;
};
#endif
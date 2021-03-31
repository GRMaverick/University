#pragma once

#include "Commons.h"
#include "ParticleComponent.h"

struct SimpleVertex
{
	bool operator<(const SimpleVertex other) const
	{
		return memcmp((void*)this, (void*)&other, sizeof(SimpleVertex)) > 0;
	}

	XMFLOAT3 PosL;
	XMFLOAT3 NormL;
	XMFLOAT2 Tex;
};
struct SurfaceInfo
{
	XMFLOAT4 AmbientMtrl;
	XMFLOAT4 DiffuseMtrl;
	XMFLOAT4 SpecularMtrl;
};
struct Light
{
	XMFLOAT4 AmbientLight;
	XMFLOAT4 DiffuseLight;
	XMFLOAT4 SpecularLight;

	float SpecularPower;
	XMFLOAT3 LightVecW;
};
struct ConstantBuffer
{
	XMMATRIX World;
	XMMATRIX View;
	XMMATRIX Projection;

	SurfaceInfo surface;

	Light light;

	XMFLOAT3 EyePosW;
	float HasTexture;
};

enum DECELERATION
{
	DECELERATION_FAST = 1,
	DECELERATION_NORMAL = 2,
	DECELERATION_SLOW = 3
};
enum STEERING_BEHAVIOUR
{
	STEERING_NONE,
	STEERING_SEEK,
	STEERING_FLEE,
	STEERING_ARRIVE,
	STEERING_EVADE,
	STEERING_PURSUIT,
	STEERING_WANDER,
	STEERING_PATHFOLLOWING,
	STEERING_OFFSET_PURSUIT
};

inline float FindAngle(XMFLOAT3 one, XMFLOAT3 two)
{
	//return acos((one.x*two.x + one.y*two.y + one.z*two.z) / Magnitude(one) * Magnitude(two));
}
inline float Magnitude(XMFLOAT3 vector)
{
	return sqrt((vector.x*vector.x) + (vector.y*vector.y) + (vector.z*vector.z));
}

inline XMFLOAT3 Normalise(XMFLOAT3 vector)
{
	XMFLOAT3 normalised = XMFLOAT3();
	float magnitude = sqrt((vector.x*vector.x) + (vector.y*vector.y) + (vector.z*vector.z));

	normalised.x = vector.x / magnitude;
	normalised.y = vector.y / magnitude;
	normalised.z = vector.z / magnitude;

	return normalised;
}
inline XMFLOAT3 Negate(XMFLOAT3 vector)
{
	XMFLOAT3 negated;

	negated.x = -vector.x;
	negated.y = -vector.y;
	negated.z = -vector.z;

	return negated;
}
inline XMFLOAT3 Cross(XMFLOAT3 one, XMFLOAT3 two)
{
	return XMFLOAT3(one.y*two.z - one.z*two.y, one.z*two.x - one.x*two.z, one.x*two.y - one.y*two.x);
}

inline XMFLOAT3 operator+(XMFLOAT3 vector, XMFLOAT3 vector2)
{
	return XMFLOAT3(vector.x + vector.x, vector.y + vector.y, vector.z + vector.z);
}
inline XMFLOAT3 operator-(XMFLOAT3 vector, XMFLOAT3 vector2)
{
	return XMFLOAT3(vector.x - vector2.x, vector.y - vector2.y, vector.z - vector2.z);
}
inline XMFLOAT3 operator*(XMFLOAT3 vector, float scaler)
{
	return XMFLOAT3(vector.x*scaler, vector.y*scaler, vector.z*scaler);
}
inline XMFLOAT3 operator/(XMFLOAT3 vector, float scaler)
{
	return XMFLOAT3(vector.x / scaler, vector.y / scaler, vector.z / scaler);
}

inline bool operator==(XMFLOAT3 vector, XMFLOAT3 vector2)
{
	return (vector.x == vector2.x && vector.y == vector2.y && vector.z == vector.z);
}

inline void Interpenetration(ParticleModel* one, ParticleModel* two)
{
	if (one->GetVelocity().y < 1.0f)
	{
		const float k_slop = 0.01f; // Penetration allowance
		const float percent = 0.2f; // Penetration percentage to correct
		XMFLOAT3 correction = (XMFLOAT3(0.0f, -1.0f, 0.0) * (max(one->GetPenetration() - k_slop, 0.0f) / one->GetMass() + two->GetMass() * percent));
		one->GetTransform()->SetPosition(one->GetTransform()->GetPosition() - (correction * one->GetMass()));
		//two->GetTransform()->SetPosition(two->GetTransform()->GetPosition() - (correction * two->GetMass()));
	}
}
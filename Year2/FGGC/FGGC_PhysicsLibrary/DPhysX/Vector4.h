#ifndef __DPHYSX_VECTOR_4__
#define __DPHYSX_VECTOR_4__

#ifndef DPHYSX_DLL_EXPORT
#define DPHYSX_DLL __declspec(dllexport)
#else
#define DPHYSX_DLL __declspec(dllimport)
#endif

class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

	DPHYSX_DLL Vector4(void);
	DPHYSX_DLL Vector4(float x, float y, float z, float w);
	DPHYSX_DLL ~Vector4(void);
};

#endif
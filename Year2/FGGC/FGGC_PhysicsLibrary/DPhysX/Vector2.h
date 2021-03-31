#ifndef __DPHYSX_VECTOR_2__
#define __DPHYSX_VECTOR_2__

#ifndef DPHYSX_DLL_EXPORT
#define DPHYSX_DLL __declspec(dllexport)
#else
#define DPHYSX_DLL __declspec(dllimport)
#endif

class Vector2
{
public:
	float x;
	float y;

	DPHYSX_DLL Vector2(void);
	DPHYSX_DLL Vector2(float x, float y);
	DPHYSX_DLL ~Vector2();
};

#endif

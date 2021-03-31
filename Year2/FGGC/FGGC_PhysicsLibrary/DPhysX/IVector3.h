#ifndef __DPHYSX_IVECTOR_3__
#define __DPHYSX_IVECTOR_3__

#ifndef DPHYSX_DLL_EXPORT
#define DPHYSX_DLL __declspec(dllexport)
#else
#define DPHYSX_DLL __declspec(dllimport)
#endif

class IVector3
{
public:
	//Vector3();
	//virtual ~Vector3();

	DPHYSX_DLL virtual Vector3 operator=(Vector3& vector);

	DPHYSX_DLL virtual bool operator==(Vector3& vector);
	DPHYSX_DLL virtual bool operator!=(Vector3& vector);

	DPHYSX_DLL virtual Vector3 operator+(Vector3& vector);
	DPHYSX_DLL virtual Vector3 operator-(Vector3& vector);
	DPHYSX_DLL virtual Vector3 operator*(float scalar);
	DPHYSX_DLL virtual Vector3 operator/(float scalar);

	DPHYSX_DLL virtual Vector3 operator+=(Vector3& vector);
	DPHYSX_DLL virtual Vector3 operator-=(Vector3& vector);
	DPHYSX_DLL virtual Vector3 operator*=(float scalar);
	DPHYSX_DLL virtual Vector3 operator/=(float scalar);

	DPHYSX_DLL virtual Vector3 operator^(Vector3& vector);
	DPHYSX_DLL virtual float operator*(Vector3& vector);

	DPHYSX_DLL virtual void Negate(void) = 0;
	DPHYSX_DLL virtual void Normalise(void) = 0;
	DPHYSX_DLL virtual float Magnitude(void) = 0;
};
#endif

#include "Vector4.h"

#define DPHYSX_DLL_EXPORT

DPHYSX_DLL Vector4::Vector4(void) 
{ 
	this->x = 0.0f; this->y = 0.0f; this->z = 0.0f; this->w = 0.0f; 
}
DPHYSX_DLL Vector4::Vector4(float x, float y, float z, float w) 
{ 
	this->x = x; this->y = y; this->z = z; this->w = w; 
}
DPHYSX_DLL Vector4::~Vector4(void) 
{ 
}
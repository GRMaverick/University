#include "Vector2.h"

#define DPHYSX_DLL_EXPORT

DPHYSX_DLL Vector2::Vector2(void)
{
	this->x = 0.0f;
	this->y = 0.0f;
}
DPHYSX_DLL Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}
DPHYSX_DLL Vector2::~Vector2(void)
{
}
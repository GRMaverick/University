#pragma once

#include "Structs.h"

class CollisionComponent;

typedef struct {
	int status;
	unsigned char type, pixelDepth;
	short int width, height;
	unsigned char *imageData;
}tgaInfo;

namespace GeometryGenerator
{
	void CalculateVectors(SimpleVertex* _vertices, WORD* _indices, int _vertexCount);
	void CalculateTangentBinormal(TempVertex _vertex1, TempVertex _vertex2, TempVertex _vertex3, XMFLOAT3& _tangent, XMFLOAT3& _binormal);
	void CalculateNormal(XMFLOAT3 _tangent, XMFLOAT3 _binormal, XMFLOAT3& normal);

	Geometry BuildGrid(ID3D11Device* _device, int _width, int _height, int _vertexCountX, int _vertexCountZ);
	Geometry BuildQuad(ID3D11Device* _device, int _width, int _height);
	Geometry BuildCube(ID3D11Device* _device, int _width, int _height, int _depth, bool _calculateNormal = false);

	CollisionComponent* ReadCollisionVertices(const char* objectFile);
}

namespace FileLoader
{
	void TGALoadHeader(FILE* _file, tgaInfo* _info);
	void TGALoadImageData(FILE* _file, tgaInfo* _info);
}
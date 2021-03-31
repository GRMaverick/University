#include "pch.h"
#include "GeometryGenerator.h"
#include "Debugging.h"
#include <DirectXMath.h>

#include "CollisionComponent.h"

namespace FileLoader
{
	void TGALoadHeader(FILE* _file, tgaInfo* _info)
	{
		unsigned char cGarbage;
		short int iGarbage;

		fread(&cGarbage, sizeof(unsigned char), 1, _file);
		fread(&cGarbage, sizeof(unsigned char), 1, _file);

		// type must be 2 or 3
		fread(&_info->type, sizeof(unsigned char), 1, _file);

		fread(&iGarbage, sizeof(short int), 1, _file);
		fread(&iGarbage, sizeof(short int), 1, _file);
		fread(&cGarbage, sizeof(unsigned char), 1, _file);
		fread(&iGarbage, sizeof(short int), 1, _file);
		fread(&iGarbage, sizeof(short int), 1, _file);

		fread(&_info->width, sizeof(short int), 1, _file);
		fread(&_info->height, sizeof(short int), 1, _file);
		fread(&_info->pixelDepth, sizeof(unsigned char), 1, _file);

		fread(&cGarbage, sizeof(unsigned char), 1, _file);
	}
	void TGALoadImageData(FILE* _file, tgaInfo* _info)
	{
		int mode, total, i;
		unsigned char aux;

		mode = _info->pixelDepth / 8;
		total = _info->height * _info->width * mode;

		fread(_info->imageData, sizeof(unsigned char), total, _file);

		if (mode >= 3)
		{
			for (i = 0; i < total; i += mode)
			{
				aux = _info->imageData[i];
				_info->imageData[i] = _info->imageData[i + 2];
				_info->imageData[i + 2] = aux;
			}
		}
	}
}

namespace GeometryGenerator
{
	std::vector<float> LoadHeightMapRAW(int _width, int _height, const char* _heightmap)
	{
		std::vector<float> heightmap(_width * _height);
		std::vector<unsigned char> in(_width * _height);

		std::ifstream inFile;
		inFile.open(_heightmap, std::ios_base::binary);

		if (inFile)
		{
			inFile.read((char*)&in[0], (std::streamsize)in.size());
			inFile.close();
		}
		else
		{
			DebugString("Heightmap loading - FAILED.");
		}

		for (UINT i = 0; i < _height * _width; ++i)
		{
			heightmap[i] = (in[i] / 255.0f) * 2.0f;
		}

		return heightmap;
	}
	tgaInfo* LoadHeightMapTGA(int _width, int _height, const char* _heightmap)
	{
		FILE* file;
		tgaInfo* info;
		int mode, total;

		info = new tgaInfo();
		if (!info)
		{
			return(NULL);
		}

		fopen_s(&file, _heightmap, "rb");
		if (!file)
		{
			DebugString("TGA File FAILED");
		}

		FileLoader::TGALoadHeader(file, info);

		if (ferror(file))
		{
			info->status = 1;
			fclose(file);
			return(info);
		}

		if (info->type == 1)
		{
			info->status = 2;
			fclose(file);
			return(info);
		}

		if ((info->type != 2) && (info->type != 3))
		{
			info->status = 3;
			fclose(file);
			return(info);
		}

		mode = info->pixelDepth / 8;
		total = info->height * info->width * mode;
		info->imageData = (unsigned char *)malloc(sizeof(unsigned char) * total);

		if (info->imageData == NULL)
		{
			info->status = 4;
			fclose(file);
			return(info);
		}

		if (ferror(file))
		{
			info->status = 5;
			fclose(file);
			return(info);
		}

		FileLoader::TGALoadImageData(file, info);

		fclose(file);
		info->status = 0;
		return(info);
	}

	void CalculateVectors(SimpleVertex* _vertices, WORD* _indices, int _vertexCount)
	{
		int faceCount, i, index;
		TempVertex vertex1, vertex2, vertex3;
		XMFLOAT3 tangent, binormal, normal = XMFLOAT3(0.0f, 0.0f, 0.0f);

		// Calculate the number of faces in the model.
		faceCount = _vertexCount / 3;

		// Initialize the index to the model data.
		index = 0;

		// Go through all the faces and calculate the the tangent, binormal, and normal vectors.
		for (i = 0; i < faceCount; i++)
		{
			// Get the three vertices for this face from the model.
			vertex1.x = _vertices[index].PosL.x;
			vertex1.y = _vertices[index].PosL.y;
			vertex1.z = _vertices[index].PosL.z;
			vertex1.u = _vertices[index].Tex.x;
			vertex1.v = _vertices[index].Tex.y;
			vertex1.nx = _vertices[index].NormL.x;
			vertex1.ny = _vertices[index].NormL.y;
			vertex1.nz = _vertices[index].NormL.z;
			index++;

			vertex2.x = _vertices[index].PosL.x;
			vertex2.y = _vertices[index].PosL.y;
			vertex2.z = _vertices[index].PosL.z;
			vertex2.u = _vertices[index].Tex.x;
			vertex2.v = _vertices[index].Tex.y;
			vertex2.nx = _vertices[index].NormL.x;
			vertex2.ny = _vertices[index].NormL.y;
			vertex2.nz = _vertices[index].NormL.z;
			index++;

			vertex3.x = _vertices[index].PosL.x;
			vertex3.y = _vertices[index].PosL.y;
			vertex3.z = _vertices[index].PosL.z;
			vertex3.u = _vertices[index].Tex.x;
			vertex3.v = _vertices[index].Tex.y;
			vertex3.nx = _vertices[index].NormL.x;
			vertex3.ny = _vertices[index].NormL.y;
			vertex3.nz = _vertices[index].NormL.z;
			index++;

			// Calculate the tangent and binormal of that face.
			CalculateTangentBinormal(vertex1, vertex2, vertex3, tangent, binormal);

			// Calculate the new normal using the tangent and binormal.
			CalculateNormal(tangent, binormal, normal);

			// Store the normal, tangent, and binormal for this face back in the model structure.
			_vertices[index - 1].NormL.x = normal.x;
			_vertices[index - 1].NormL.y = normal.y;
			_vertices[index - 1].NormL.z = normal.z;
			_vertices[index - 1].Tangent.x = tangent.x;
			_vertices[index - 1].Tangent.y = tangent.y;
			_vertices[index - 1].Tangent.z = tangent.z;
			_vertices[index - 1].Bitangent.x = binormal.x;
			_vertices[index - 1].Bitangent.y = binormal.y;
			_vertices[index - 1].Bitangent.z = binormal.z;

			_vertices[index - 2].NormL.x = normal.x;
			_vertices[index - 2].NormL.y = normal.y;
			_vertices[index - 2].NormL.z = normal.z;
			_vertices[index - 2].Tangent.x = tangent.x;
			_vertices[index - 2].Tangent.y = tangent.y;
			_vertices[index - 2].Tangent.z = tangent.z;
			_vertices[index - 2].Bitangent.x = binormal.x;
			_vertices[index - 2].Bitangent.y = binormal.y;
			_vertices[index - 2].Bitangent.z = binormal.z;

			_vertices[index - 3].NormL.x = normal.x;
			_vertices[index - 3].NormL.y = normal.y;
			_vertices[index - 3].NormL.z = normal.z;
			_vertices[index - 3].Tangent.x = tangent.x;
			_vertices[index - 3].Tangent.y = tangent.y;
			_vertices[index - 3].Tangent.z = tangent.z;
			_vertices[index - 3].Bitangent.x = binormal.x;
			_vertices[index - 3].Bitangent.y = binormal.y;
			_vertices[index - 3].Bitangent.z = binormal.z;
		}
	}
	void CalculateTangentBinormal(TempVertex _vertex1, TempVertex _vertex2, TempVertex _vertex3, XMFLOAT3& _tangent, XMFLOAT3& _binormal)
	{
		float vector1[3], vector2[3];
		float tuVector[2], tvVector[2];
		float den;
		float length;

		// Calculate the two vectors for this face.
		vector1[0] = _vertex2.x - _vertex1.x;
		vector1[1] = _vertex2.y - _vertex1.y;
		vector1[2] = _vertex2.z - _vertex1.z;

		vector2[0] = _vertex3.x - _vertex1.x;
		vector2[1] = _vertex3.y - _vertex1.y;
		vector2[2] = _vertex3.z - _vertex1.z;

		// Calculate the tu and tv texture space vectors.
		tuVector[0] = _vertex2.u - _vertex1.u;
		tvVector[0] = _vertex2.v - _vertex1.v;

		tuVector[1] = _vertex3.u - _vertex1.u;
		tvVector[1] = _vertex3.v - _vertex1.v;

		// Calculate the denominator of the tangent/binormal equation.
		den = 1.0f / (tuVector[0] * tvVector[1] - tuVector[1] * tvVector[0]);

		// Calculate the cross products and multiply by the coefficient to get the tangent and binormal.
		_tangent.x = (tvVector[1] * vector1[0] - tvVector[0] * vector2[0]) * den;
		_tangent.y = (tvVector[1] * vector1[1] - tvVector[0] * vector2[1]) * den;
		_tangent.z = (tvVector[1] * vector1[2] - tvVector[0] * vector2[2]) * den;

		_binormal.x = (tuVector[0] * vector2[0] - tuVector[1] * vector1[0]) * den;
		_binormal.y = (tuVector[0] * vector2[1] - tuVector[1] * vector1[1]) * den;
		_binormal.z = (tuVector[0] * vector2[2] - tuVector[1] * vector1[2]) * den;

		// Calculate the length of this normal.
		length = sqrt((_tangent.x * _tangent.x) + (_tangent.y * _tangent.y) + (_tangent.z * _tangent.z));

		// Normalize the normal and then store it
		_tangent.x = _tangent.x / length;
		_tangent.y = _tangent.y / length;
		_tangent.z = _tangent.z / length;

		// Calculate the length of this normal.
		length = sqrt((_binormal.x * _binormal.x) + (_binormal.y * _binormal.y) + (_binormal.z * _binormal.z));

		// Normalize the normal and then store it
		_binormal.x = _binormal.x / length;
		_binormal.y = _binormal.y / length;
		_binormal.z = _binormal.z / length;
	}
	void CalculateNormal(XMFLOAT3 _tangent, XMFLOAT3 _binormal, XMFLOAT3& normal)
	{
		float length;

		// Calculate the cross product of the tangent and binormal which will give the normal vector.
		normal.x = (_tangent.y * _binormal.z) - (_tangent.z * _binormal.y);
		normal.y = (_tangent.z * _binormal.x) - (_tangent.x * _binormal.z);
		normal.z = (_tangent.x * _binormal.y) - (_tangent.y * _binormal.x);

		// Calculate the length of the normal.
		length = sqrt((normal.x * normal.x) + (normal.y * normal.y) + (normal.z * normal.z));

		// Normalize the normal.
		normal.x = normal.x / length;
		normal.y = normal.y / length;
		normal.z = normal.z / length;
	}

	bool IsNear(float v1, float v2)
	{
		return fabs(v1 - v2) == 0.0f;
	}

	// Similar = same position + same UVs + same normal
	bool GetSimilarVertexIndex(XMFLOAT3& in_vertex, XMFLOAT2& in_uv, XMFLOAT3& in_normal, std::vector<XMFLOAT3>& out_vertices, std::vector<XMFLOAT2>& out_uvs,
		std::vector<XMFLOAT3>& out_normals, unsigned short& result)
	{
		int i = 0, j = 0, k = 0;
		std::vector<XMFLOAT3>::iterator itVert = out_vertices.begin();
		for (; itVert != out_vertices.end(); itVert++, i++)
		{
			if (in_vertex.x == out_vertices[i].x && in_vertex.y == out_vertices[i].y && in_vertex.z == out_vertices[i].z)
			{
				std::vector<XMFLOAT3>::iterator itNormal = out_normals.begin();
				for (; itNormal != out_normals.end(); itNormal++, j++)
				{
					if (in_normal.x == out_normals[j].x && in_normal.y == out_normals[j].y && in_normal.z == out_normals[j].z)
					{
						std::vector<XMFLOAT2>::iterator itTex = out_uvs.begin();
						for (; itTex != out_uvs.end(); itTex++, k++)
						{
							if (in_uv.x == out_uvs[k].x && in_uv.y == out_uvs[k].y)
							{
								result = i;
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	void indexVBO_TBN(std::vector<XMFLOAT3>& in_vertices, std::vector<XMFLOAT2>& in_uvs, std::vector<XMFLOAT3>& in_normals, std::vector<XMFLOAT3>& in_tangents, std::vector<XMFLOAT3>& in_bitangents,
		std::vector<unsigned short>& out_indices, std::vector<XMFLOAT3>& out_vertices, std::vector<XMFLOAT2>& out_uvs, std::vector<XMFLOAT3>& out_normals, std::vector<XMFLOAT3>& out_tangents,
		std::vector<XMFLOAT3>& out_bitangents)
	{
		int i = 0;
		// For each input vertex
		for (i = 0; i<in_vertices.size(); i++)
		{
			// Try to find a similar vertex in out_XXXX
			unsigned short index;
			bool found = GetSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i], out_vertices, out_uvs, out_normals, index);
			if (found)
			{
				out_indices.push_back(index);

				out_tangents[index].x += in_tangents[i].x;
				out_tangents[index].y += in_tangents[i].y;
				out_tangents[index].z += in_tangents[i].z;
				out_bitangents[index].x += in_bitangents[i].x;
				out_bitangents[index].y += in_bitangents[i].y;
				out_bitangents[index].z += in_bitangents[i].z;
			}
			else
			{
				out_vertices.push_back(in_vertices[i]);
				out_uvs.push_back(in_uvs[i]);
				out_normals.push_back(in_normals[i]);
				out_tangents.push_back(in_tangents[i]);
				out_bitangents.push_back(in_bitangents[i]);
				out_indices.push_back((unsigned short)out_vertices.size() - 1);
			}
		}
		int x = 0;
	}

	bool FindSimilarVertex(const SimpleVertex& _vertex, std::map<SimpleVertex, unsigned short>& _vertToIndexMap, unsigned short& _index)
	{
		auto it = _vertToIndexMap.find(_vertex);
		if (it == _vertToIndexMap.end())
		{
			return false;
		}
		else
		{
			_index = it->second;
			return true;
		}
	}

	void CreateIndices(const std::vector<XMFLOAT3>& _inVertices, const std::vector<XMFLOAT2>& _inTexCoords, const std::vector<XMFLOAT3>& _inNormals, const std::vector<XMFLOAT3>& _inTangents, const std::vector<XMFLOAT3> _inBitangents,
		std::vector<unsigned short>& _outIndices, std::vector<XMFLOAT3>& _outVertices, std::vector<XMFLOAT2>& _outTexCoords, std::vector<XMFLOAT3>& _outNormals, std::vector<XMFLOAT3>& _outTangents,
		std::vector<XMFLOAT3>& _outBitangents)
	{
		//Mapping from an already-existing SimpleVertex to its corresponding index
		std::map<SimpleVertex, unsigned short> vertToIndexMap;

		std::pair<SimpleVertex, unsigned short> pair;

		int numVertices = _inVertices.size();
		for (int i = 0; i < numVertices; ++i) //For each vertex
		{
			SimpleVertex vertex = { _inVertices[i], _inNormals[i], _inTexCoords[i], _inTangents[i], _inBitangents[i] };

			unsigned short index;
			bool found = FindSimilarVertex(vertex, vertToIndexMap, index); //See if a vertex already exists in the buffer that has the same attributes as this one
			if (found) //if found, re-use it's index for the index buffer
			{
				_outIndices.push_back(index);

				_outTangents[index].x += _inTangents[i].x;
				_outTangents[index].y += _inTangents[i].y;
				_outTangents[index].z += _inTangents[i].z;
				_outBitangents[index].x += _inBitangents[i].x;
				_outBitangents[index].y += _inBitangents[i].y;
				_outBitangents[index].z += _inBitangents[i].z;
			}
			else //if not found, add it to the buffer
			{
				_outVertices.push_back(vertex.PosL);
				_outTexCoords.push_back(vertex.Tex);
				_outNormals.push_back(vertex.NormL);
				_outTangents.push_back(vertex.Tangent);
				_outBitangents.push_back(vertex.Bitangent);

				unsigned short newIndex = (unsigned short)_outVertices.size() - 1;
				_outIndices.push_back(newIndex);

				//Add it to the map
				pair.first = vertex;
				pair.second = newIndex;
				vertToIndexMap.insert(pair);
			}
		}
	}


	Geometry BuildGrid(ID3D11Device* _device, int _width, int _depth, int _vertexCountX, int _vertexCountZ)
	{
		Geometry planeGeometry;

		int rowAmount = _depth;
		int colAmount = _width;
		int indicesNum = -1;

		int terrainGridSize = 6 * rowAmount * colAmount;

		WORD* indicesFlatGrid = new WORD[terrainGridSize];
		for (unsigned int row = 0; row < rowAmount; row++)
		{
			for (unsigned int col = 0; col < colAmount; col++)
			{
				indicesFlatGrid[indicesNum + 1] = ((colAmount + 1)* row) + col;
				indicesFlatGrid[indicesNum + 2] = ((colAmount + 1)* row) + col + 1;
				indicesFlatGrid[indicesNum + 3] = ((colAmount + 1)* row) + col + (colAmount + 1);
				indicesFlatGrid[indicesNum + 4] = ((colAmount + 1)* row) + col + (colAmount + 1);
				indicesFlatGrid[indicesNum + 5] = ((colAmount + 1)* row) + col + 1;
				indicesFlatGrid[indicesNum + 6] = ((colAmount + 1)* row) + col + (colAmount + 2);
				indicesNum += 6;
			}
		}

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(WORD) * terrainGridSize;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = indicesFlatGrid;
		_device->CreateBuffer(&bd, &InitData, &planeGeometry.IndexBuffer);
		int verticesNum = -1;

		int verticesAmount = (rowAmount + 1) * (colAmount + 1);
		int triangleAmount = rowAmount * colAmount * 2;

		float texCoordWidthIncreament = 1 / rowAmount;
		float texCoordHeightincrement = 1 / colAmount;
		float texCoordHeight = 0.0f;
		float texCoordWidth = 0.0f;

		SimpleVertex *verticesFlatGrid;
		verticesFlatGrid = new SimpleVertex[verticesAmount];
		for (int row = 0; row <= rowAmount; row++)
		{
			int y = row;

			for (int col = 0; col <= colAmount; col++)
			{
				float x = col - (colAmount / 2);
				float z = rowAmount - row - (rowAmount / 2);

				verticesFlatGrid[verticesNum + 1] = { XMFLOAT3(x, -2.0f, z), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) };
				verticesNum++;
				texCoordHeight += texCoordHeightincrement;
				texCoordWidth += texCoordWidthIncreament;
			}
		}

		{
			for (unsigned int i = 0; i < verticesAmount; i++)
			{
				unsigned int index0 = indicesFlatGrid[i * 3 + 0];
				unsigned int index1 = indicesFlatGrid[i * 3 + 1];
				unsigned int index2 = indicesFlatGrid[i * 3 + 2];

				XMFLOAT3 vector0, vector1, faceNormal;

				vector0.x = verticesFlatGrid[index1].PosL.x - verticesFlatGrid[index0].PosL.x;
				vector0.y = verticesFlatGrid[index1].PosL.z - verticesFlatGrid[index0].PosL.y;
				vector0.z = verticesFlatGrid[index1].PosL.z - verticesFlatGrid[index0].PosL.z;

				vector1.x = verticesFlatGrid[index2].PosL.x - verticesFlatGrid[index0].PosL.x;
				vector1.y = verticesFlatGrid[index2].PosL.z - verticesFlatGrid[index0].PosL.y;
				vector1.z = verticesFlatGrid[index2].PosL.z - verticesFlatGrid[index0].PosL.z;

				faceNormal.x = vector0.y * vector1.z - vector0.z * vector1.y;
				faceNormal.y = vector0.z * vector1.x - vector0.x * vector1.z;
				faceNormal.z = vector0.x * vector1.y - vector0.y * vector1.x;


				verticesFlatGrid[index0].NormL.x += faceNormal.x;
				verticesFlatGrid[index0].NormL.y += faceNormal.y;
				verticesFlatGrid[index0].NormL.z += faceNormal.z;

				verticesFlatGrid[index1].NormL.x += faceNormal.x;
				verticesFlatGrid[index1].NormL.y += faceNormal.y;
				verticesFlatGrid[index1].NormL.z += faceNormal.z;

				verticesFlatGrid[index2].NormL.x += faceNormal.x;
				verticesFlatGrid[index2].NormL.y += faceNormal.y;
				verticesFlatGrid[index2].NormL.z += faceNormal.z;
			}

			for (unsigned int i = 0; i < verticesAmount; i++)
			{
				float magnitude = sqrt(verticesFlatGrid[i].NormL.x*verticesFlatGrid[i].NormL.x +
					verticesFlatGrid[i].NormL.y*verticesFlatGrid[i].NormL.y +
					verticesFlatGrid[i].NormL.z*verticesFlatGrid[i].NormL.z);

				verticesFlatGrid[i].NormL.x = verticesFlatGrid[i].NormL.x / magnitude;
				verticesFlatGrid[i].NormL.y = verticesFlatGrid[i].NormL.y / magnitude;
				verticesFlatGrid[i].NormL.z = verticesFlatGrid[i].NormL.z / magnitude;
			}
		}

		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(SimpleVertex) * verticesAmount;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = verticesFlatGrid;
		_device->CreateBuffer(&bd, &InitData, &planeGeometry.VertexBuffer);

		planeGeometry.VBOffset = 0;
		planeGeometry.VBStride = sizeof(SimpleVertex);
		planeGeometry.IndexCount = terrainGridSize;
		planeGeometry.Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		delete[] indicesFlatGrid;
		delete[] verticesFlatGrid;

		return planeGeometry;
	}
	Geometry BuildQuad(ID3D11Device* _device, int _width, int _height)
	{
		SimpleVertex planeVertices[] =
		{
			{ XMFLOAT3(-1.0f * _width, -1.0f * _height, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f * _width, 1.0f * _height) },
			{ XMFLOAT3(1.0f * _width, -1.0f * _height, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1.0f * _width, 1.0f * _height) },
			{ XMFLOAT3(1.0f * _width, 1.0f * _height, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1.0f * _width, 0.0f * _height) },
			{ XMFLOAT3(-1.0f * _width, 1.0f  * _height, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f * _width, 0.0f * _height) },
		};

		WORD planeIndices[] =
		{
			0, 3, 1,
			3, 2, 1,
		};

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(SimpleVertex) * 24;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = planeVertices;

		ID3D11Buffer* vertexBuffer;
		_device->CreateBuffer(&bd, &InitData, &vertexBuffer);

		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(WORD) * 6;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = planeIndices;

		ID3D11Buffer* indexBuffer;
		_device->CreateBuffer(&bd, &InitData, &indexBuffer);

		Geometry result;
		result.VertexBuffer = vertexBuffer;
		result.IndexBuffer = indexBuffer;
		result.IndexCount = 6;
		result.VBOffset = 0;
		result.VBStride = sizeof(SimpleVertex);
		result.Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;


		return result;
	}
	Geometry BuildCube(ID3D11Device* _device, int _width, int _height, int _depth, bool _calculateNormal)
	{
		std::vector<XMFLOAT3> verticesVector;
		std::vector<XMFLOAT3> normalsVector;
		std::vector<XMFLOAT2> texcoordsVector;
		std::vector<XMFLOAT3> tangentVector;
		std::vector<XMFLOAT3> bitangentVector;

		std::vector<unsigned short> indicesVector;
		std::vector<XMFLOAT3> indexed_vertices;
		std::vector<XMFLOAT2> indexed_uvs;
		std::vector<XMFLOAT3> indexed_normals;
		std::vector<XMFLOAT3> indexed_tangents;
		std::vector<XMFLOAT3> indexed_bitangents;

		SimpleVertex vertices[] =
		{
			{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
			{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) },
			{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) },
			{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) },

			{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) },
			{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
			{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) },
			{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) },

			{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) },
			{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) },
			{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
			{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) },

			{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) },
			{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) },
			{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) },
			{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) },

			{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },
			{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
			{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
			{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },

			{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
			{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
			{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
			{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
		};

		WORD indices[] =
		{
			3, 1, 0,
			2, 1, 3,
			6, 4, 5,
			7, 4, 6,
			11, 9, 8,
			10, 9, 11,
			14, 12, 13,
			15, 12, 14,
			19, 17, 16,
			18, 17, 19,
			22, 20, 21,
			23, 20, 22
		};

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(SimpleVertex) * 24;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = vertices;

		ID3D11Buffer* vertexBuffer;
		_device->CreateBuffer(&bd, &InitData, &vertexBuffer);

		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(WORD) * 36;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = indices;

		ID3D11Buffer* indexBuffer;
		_device->CreateBuffer(&bd, &InitData, &indexBuffer);

		Geometry result;
		result.VertexBuffer = vertexBuffer;
		result.IndexBuffer = indexBuffer;
		result.IndexCount = 36;
		result.VBOffset = 0;
		result.VBStride = sizeof(SimpleVertex);
		result.Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return result;
	}

	CollisionComponent* ReadCollisionVertices(const char* objectFile)
	{
		std::ifstream ifs(objectFile);
		if (ifs.is_open())
		{
			std::string input;
			CollisionComponent* pComponent = new CollisionComponent();

			while (!ifs.eof())
			{
				ifs >> input;
				if (input.compare("v") == 0)
				{
					Vector3 vertex;

					ifs >> vertex.x;
					ifs >> vertex.y;
					ifs >> vertex.z;

					pComponent->AddVertex(vertex);
				}
			}

			ifs.close();

			return pComponent;
		}
		else
		{
			std::cout << objectFile << ": NOT FOUND, NO COLLISION COMPONENT CREATED!" << std::endl;
			return nullptr;
		}

		return nullptr;
	}
}
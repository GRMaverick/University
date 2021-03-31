#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<sstream>

#include "MeshLoader.h"
#include "Texture2D.h"

using namespace std;

namespace MeshLoader
{
	//Method Signature Declarations
	void LoadNormals(ifstream& inFile, Mesh& mesh);
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadColours(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);
	void LoadTexCoords(ifstream& inFile, Mesh& mesh);

	//Load-by-file Methods
	void LoadNormals(ifstream& inFile, Mesh& mesh)
	{ 
		//Loads Normals from .txt files
		inFile >> mesh.normalCount;
		if (mesh.normalCount > 0)
		{
			mesh.normals = new Vector3[mesh.normalCount];
			for (int i = 0; i < mesh.normalCount; i++)
			{
				inFile >> mesh.normals[i].x;
				inFile >> mesh.normals[i].y;
				inFile >> mesh.normals[i].z;
			}
		}
	}
	void LoadVertices(ifstream& inFile, Mesh& mesh) 
	{
		//Loads Vertices from .txt files
		inFile >> mesh.vertexCount;

		if (mesh.vertexCount > 0)
		{
			mesh.vertices = new Vertex[mesh.vertexCount];
			for (int i = 0; i < mesh.vertexCount; i++)
			{
				inFile >> mesh.vertices[i].x;
				inFile >> mesh.vertices[i].y;
				inFile >> mesh.vertices[i].z;
			}
		}
	}
	void LoadColours(ifstream& inFile, Mesh& mesh)
	{
		//Loads Colours from .txt files
		inFile >> mesh.colourCount;

		if (mesh.colourCount > 0)
		{
			mesh.colours = new Colour[mesh.colourCount];
			for (int i = 0; i < mesh.colourCount; i++)
			{
				inFile >> mesh.colours[i].r;
				inFile >> mesh.colours[i].g;
				inFile >> mesh.colours[i].b;
			}
		}
	}
	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		//Loads Indices from .txt files
		inFile >> mesh.indexCount;
		if (mesh.indexCount > 0)
		{
			mesh.Indices = new GLushort[mesh.indexCount];
			for (int i = 0; i < mesh.indexCount; i++)
			{
				inFile >> mesh.Indices[i];
			}
		}
	}
	void LoadTexCoords(ifstream& inFile, Mesh& mesh)
	{
		//Loads Texture Co-ordinates from .txt files
		inFile >> mesh.texCoordsCount;
		if (mesh.texCoordsCount > 0)
		{
			mesh.texCoords = new TextureCoord[mesh.texCoordsCount];
			for (int i = 0; i < mesh.texCoordsCount; i++)
			{
				inFile >> mesh.texCoords[i].u;
				inFile >> mesh.texCoords[i].v;
			}
		}
	}

	//Mesh Construction Methods
 	Mesh* MeshLoader::LoadNormalsMesh(char* path)
	{
		//Loads Texture-Normal objects from file to mesh
		Mesh* mesh = new Mesh();
		ifstream file;

		file.open(path);

		if (!file.good())
		{
			cerr << path << ": ERROR LOADING FILE!" << endl;
			return nullptr;
		}

		LoadVertices(file, *mesh);
		LoadTexCoords(file, *mesh);
		LoadNormals(file, *mesh);
		LoadIndices(file, *mesh);

		file.close();
		return mesh;
	}
	Mesh* MeshLoader::LoadTextureMesh(char* path)
	{
		//Loads Texture-Colour objects from file to mesh
		Mesh* mesh = new Mesh();
		ifstream file;

		file.open(path);

		if (!file.good())
		{
			cerr << path << ": ERROR LOADING FILE" << endl;
			return nullptr;
		}

		LoadVertices(file, *mesh);
		LoadColours(file, *mesh);
		LoadTexCoords(file, *mesh);
		LoadIndices(file, *mesh);

		file.close();
		return mesh;
	}
	Mesh* MeshLoader::LoadColoursMesh(char* path)
	{
		//Loads coloured objects from file to mesh
		Mesh* mesh = new Mesh();
		ifstream file;

		file.open(path);
		if (!file.good())
		{
			cerr << path << ": ERROR LOADING FILE";
			return nullptr;
		}

		LoadVertices(file, *mesh);
		LoadColours(file, *mesh);
		LoadIndices(file, *mesh);

		file.close();
		return mesh;
	}
}
namespace OBJMeshLoader
{
	//Method Signature Declarations
	void LoadNormals(vector<Vector3>& normals, string& lastLine);
	void LoadVertices(vector<Vertex>& vertices, string& lastLine);
	void LoadIndices(vector<GLushort>& indices, string& lastLine);
	void LoadTexCoords(vector<TextureCoord>& texCoords, string& lastLine);
	void ConvertToMesh(OBJMesh& mesh, vector<Vertex>& vertices, vector<Vector3>& normals, vector<TextureCoord>& texCoords, vector<GLushort>& indices);

	//Load-by-file Methods
	void LoadNormals(vector<Vector3>& normals, string& lastLine)
	{
		//Loads Normals from .OBJ files
		stringstream strstm;
		string tempString;

		Vector3 v;

		strstm.str("");
		strstm.clear();
		strstm << lastLine;

		strstm >> tempString;
		strstm >> v.x;
		strstm >> v.y;
		strstm >> v.z;

		normals.push_back(v);
	}
	void LoadVertices(vector<Vertex>& vertices, string& lastLine)
	{
		//Loads Vertices from .OBJ files
		stringstream strstm;
		string tempString;

		Vertex v;

		strstm.str("");
		strstm.clear();
		strstm << lastLine;

		strstm >> tempString;
		strstm >> v.x;
		strstm >> v.y;
		strstm >> v.z;
		
		vertices.push_back(v);
	}
	void LoadIndices(vector<GLushort>& indices, string& line)
	{
		//Loads Indices from .OBJ files
		stringstream strstm;
		string tempString;
		string faces[3];
		
		strstm.str("");
		strstm.clear();
		strstm << line;

		strstm >> tempString;
		strstm >> faces[0];
		strstm >> faces[1];
		strstm >> faces[2];
		
		for (int i = 0; i < 3; i++)	{
			strstm.str("");
			strstm.clear();
			strstm << faces[i];
			getline(strstm, line, '/');
			indices.push_back(stoi(line) - 1);
			getline(strstm, line, '/');
			indices.push_back(stoi(line) - 1);
			getline(strstm, line, '/');
			indices.push_back(stoi(line) - 1);
		}
	}
	void LoadTexCoords(vector<TextureCoord>& texCoords, string& lastLine)
	{
		//Loads Texture-Co-ordinates from .OBJ files
		stringstream strstm;
		string tempString;

		float tempFloat;
		TextureCoord tc;

		strstm.str("");
		strstm.clear();
		strstm << lastLine;

		strstm >> tempString;
		strstm >> tc.u;
		strstm >> tc.v;
		strstm >> tempFloat; 

		texCoords.push_back(tc);
	}

	void ConvertToMesh(OBJMesh& mesh, vector<Vertex>& vertices, vector<Vector3>& normals, vector<TextureCoord>& texCoords, vector<vector<GLushort>>& indices)	{
		//Converts Normals, Vertices, Indices and Texture-Coordinate vectors into a Mesh
		int indexCount = 0;

		for (unsigned int i = 0; i < indices.size(); i++)	{
			vector<GLushort> currentIndices;

			for (unsigned int j = 0; j < indices[i].size(); j = j+ 3)		{
				currentIndices.push_back(indexCount);
				mesh.Vertices.push_back(vertices[indices[i][j]]);
				mesh.TexCoords.push_back(texCoords[indices[i][j + 1]]);
				mesh.Normals.push_back(normals[indices[i][j + 2]]);
				indexCount++;
			}
			mesh.MeshIndices.push_back(currentIndices);
		}
	}

	//Mesh Construction Methods
	OBJMesh* OBJMeshLoader::Load(char* path)	{
		//Reads OBJ and constructs the mesh
		vector<Vector3> normals;
		vector<Vertex> vertices;
		vector<TextureCoord> texCoords;
		vector<vector<GLushort>> currentIndices;

		string line;
		stringstream strstm;
		string tempString;
		string object;

		OBJMesh* mesh = new OBJMesh();

		ifstream inFile;
		inFile.open(path);

		if (!inFile.good())	{
			cerr << "Can't open texture file" << path << endl;
			return nullptr;
		}

		while (!inFile.eof())	{
			getline(inFile, line);
			if (line.length() > 2)	{
				switch (line.at(0))	{
					case 'v':
						switch (line.at(1))	{
							case ' ':
								LoadVertices(vertices, line);
								break;
							case 'n':
								LoadNormals(normals, line);
								break;
							case 't':
								LoadTexCoords(texCoords, line);
								break;
						}
						break;
					case 'f':
						LoadIndices(currentIndices.back(), line);
						break;
					case '#':
						strstm.str("");
						strstm.clear();
						strstm << line;

						strstm >> tempString;
						strstm >> tempString;

						if (tempString == "object")	{
							strstm >> object;
							mesh->MeshNames.push_back(object);
							vector<GLushort> indices;
							currentIndices.push_back(indices);
						}
						break;
				}
			}
		}

		ConvertToMesh(*mesh, vertices, normals, texCoords, currentIndices);
		return mesh;		
	}
}
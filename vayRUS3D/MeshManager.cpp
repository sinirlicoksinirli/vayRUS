#include"MeshManager.hpp"
#include"vertexStructs.hpp"
#include<vector>

MeshManager* MeshManager::c_Instance = nullptr;
	
MeshManager::MeshManager() {

}
MeshManager* MeshManager::getInstance()
{
	if (c_Instance != nullptr) {
		return c_Instance;
	}
	else {
		c_Instance = new MeshManager();
		return c_Instance;
	}
}

mesh* MeshManager::importMeshFbx(std::string filePath,texture _text)
{
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	FILE* file = fopen(filePath.c_str(), "r");
	if (file == NULL) {
		return nullptr;
	}

	while (1) {
		char lineHeader[128];

		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				//printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return nullptr;
			}
			vertexIndices.push_back(vertexIndex[0]-1);
			vertexIndices.push_back(vertexIndex[1]-1);
			vertexIndices.push_back(vertexIndex[2]-1);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}
	
	Vertex tmpVert[20000];
	vertexArrayObject* _vao = new vertexArrayObject();
	unsigned int totalVertCount = temp_uvs.size() + temp_vertices.size();
	unsigned int toAddVertCount = temp_uvs.size()/temp_vertices.size();
	for (unsigned int b = 0; b < toAddVertCount; b++) {
		for (unsigned int i = 0; i < temp_vertices.size(); i++) {
			glm::vec3 vertex = temp_vertices[i];
			float tmp_i = i;
			glm::vec2 texCor = temp_uvs[i];
			tmpVert[i] = (Vertex(vertex.x, vertex.y, vertex.z, texCor.x, texCor.y));
		}
	}
	

	unsigned int vertCount = temp_vertices.size();
	_vao->createObject(tmpVert[0], vertCount, vertexIndices[0], vertexIndices.size());
	mesh* result = new mesh(_vao,_text);

	return result;
}

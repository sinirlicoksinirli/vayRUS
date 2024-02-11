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
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices,finalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	FILE* file = fopen(filePath.c_str(), "r");
	if (file == NULL) {
		return nullptr;
	}
	std::vector<triangleFace> faces;

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
				return nullptr;
			}
			vertexIndices.push_back(vertexIndex[0] - 1);
			vertexIndices.push_back(vertexIndex[1] - 1);
			vertexIndices.push_back(vertexIndex[2] - 1);
			uvIndices.push_back(uvIndex[0] - 1);
			uvIndices.push_back(uvIndex[1] - 1);
			uvIndices.push_back(uvIndex[2] - 1);
			normalIndices.push_back(normalIndex[0] - 1);
			normalIndices.push_back(normalIndex[1] - 1);
			normalIndices.push_back(normalIndex[2] - 1);
		}
	}
	
	for (unsigned int a = 0; a < vertexIndices.size(); a+=3) {
		triangleFace face;
		face.v0 = Vertex(temp_vertices[vertexIndices[(a)]], temp_uvs[uvIndices[(a)]], temp_normals[normalIndices[(a)]]);
		face.v1 = Vertex(temp_vertices[vertexIndices[(a)+1]], temp_uvs[uvIndices[(a) + 1]], temp_normals[normalIndices[(a) + 1]]);
		face.v2 = Vertex(temp_vertices[vertexIndices[(a)+2]], temp_uvs[uvIndices[(a) + 2]], temp_normals[normalIndices[(a) + 2]]);
		faces.push_back(face);
		finalIndices.push_back((a));
		finalIndices.push_back((a) + 1);
		finalIndices.push_back((a) + 2);
	}

	std::vector<Vertex>tmpVert;

	vertexArrayObject* _vao = new vertexArrayObject();
		for (unsigned int i = 0; i < faces.size(); i++) {
			tmpVert.push_back(faces[i].v0);
			tmpVert.push_back(faces[i].v1);
			tmpVert.push_back(faces[i].v2);
		}

	unsigned int vertCount = temp_vertices.size();
	_vao->createObject(tmpVert[0], tmpVert.size(), finalIndices[0], finalIndices.size());
	mesh* result = new mesh(_vao,_text);

	return result;
}

#ifndef meshManager_hpp
#define meshManager_hpp
#include"mesh.hpp"
class MeshManager {
public:
	static MeshManager* getInstance();
	mesh* importMeshFbx(std::string filePath, texture _text);
private:
	static MeshManager* c_Instance;
	MeshManager();
};


#endif 
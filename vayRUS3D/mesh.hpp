#ifndef mesh_hpp
#define mesh_hpp
#include"vertexArray.hpp"
#include"vertexStructs.hpp"
class mesh {
public:
	void draw();
private:
	vertexArrayManager* p_Vao;
	unsigned int indexCount;
};


#endif 

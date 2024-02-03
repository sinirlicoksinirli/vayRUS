#ifndef vertexStructs_hpp
#define vertexStructs_hpp
#include<glm/vec3.hpp>
#include<glm/vec2.hpp>
struct Vertex {
	glm::vec3 pos;
	glm::vec2 tex;
	Vertex(float x=0.0f, float y = 0.0f, float z = 0.0f, float tX = 0.0f, float tY = 0.0f);
};
typedef unsigned int indexData;

struct triangleFace {
	Vertex v0;
	Vertex v1;
	Vertex v2;
};
struct trianglePolyFace {
	//??
};
#endif 

#ifndef vertexArray_hpp
#define vertexArray_hpp

#include"vertexStructs.hpp"
#include <vector>
class vertexArrayManager {
public:
	vertexArrayManager();
	~vertexArrayManager();
	void createObject(const Vertex& vertices,unsigned int verticesCount, const indexData& indices, unsigned int indicesCount);
	void activateBuffer();
	void deactivateBuffer();
private:
	unsigned int VaoId, VboId, VibId;
	std::vector<unsigned int> t_Attirbs;
};


#endif 

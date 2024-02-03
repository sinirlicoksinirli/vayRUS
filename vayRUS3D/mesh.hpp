#ifndef mesh_hpp
#define mesh_hpp
#include"EngineBase.h"
#include"vertexArray.hpp"
#include"vertexStructs.hpp"
#include<glad/glad.h>
#include <gl/GL.h>
#include<GLFW/glfw3.h>
#include"textureSystem.hpp"
#include"baseVector.h"
#include"shaderSystem.hpp"
#include"player.hpp"
namespace UreTechEngine {
	class Player;
}
class mesh {
public:
	UreTechEngine::Transform3D transform;
	void draw(UreTechEngine::Transform3D _addTrnsfm);
	void applyTexture(texture _text);
	mesh(vertexArrayObject* _p_Vao, texture _text);
private:
	vertexArrayObject* p_Vao;
	TextureManager* textManager;
	ShaderProgram* shaderProg;
	UreTechEngine::Player* PlayerRef = nullptr;
	unsigned int indexCount;
	texture TextureID;
};


#endif 

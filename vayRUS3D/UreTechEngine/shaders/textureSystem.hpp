#ifndef textureSystem_hpp
#define textureSystem_hpp
#include<string>
#include<map>
#include"../UreTechEngine/shaders/shaderSystem.hpp"
#include "../EngineBase.h"
typedef unsigned int texture;

class TextureManager{

public:
	static TextureManager* getInstance();

	unsigned int loadTextureFromFile(std::string fileName);
	void applyTexture( int levelInd, unsigned int textureId);

private:
	ShaderProgram* shaderProg;
	UreTechEngine::UreTechEngineClass* engine;
	TextureManager();
	static TextureManager* c_Instance;
	std::map<std::string, unsigned int> L_TextureMap;
};



#endif
#ifndef textureSystem_hpp
#define textureSystem_hpp
#include<string>
#include<map>
#include"../UreTechEngine/shaders/shaderSystem.hpp"
#include "../EngineBase.h"
#include"../utils/Array.hpp"
typedef unsigned int texture;

namespace UreTechEngine {
	class UreTechEngineClass;
}

class TextureManager{

public:
	static TextureManager* getInstance();

	unsigned int loadTextureFromFile(std::string fileName, bool texAntiAlising = true);
	void applyTexture( int levelInd, unsigned int textureId);
	void applyMultipleTexture(std::vector<texture> a);

private:
	ShaderProgram* shaderProg;
	UreTechEngine::UreTechEngineClass* engine;
	TextureManager();
	static TextureManager* c_Instance;
	std::map<std::string, unsigned int> L_TextureMap;
};



#endif
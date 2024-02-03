#ifndef textureSystem_hpp
#define textureSystem_hpp
#include<string>
#include<map>
typedef unsigned int texture;

class TextureManager{

public:
	static TextureManager* getInstance();

	unsigned int loadTextureFromFile(std::string fileName);
	void applyTexture(unsigned int levelInd, unsigned int textureId);

private:
	TextureManager();
	static TextureManager* c_Instance;
	std::map<std::string, unsigned int> L_TextureMap;
};



#endif
#include"textureSystem.hpp"
#include"../src/stb_image.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/mat4x4.hpp>
#include<glm/gtx/matrix_transform_2d.hpp>
#include "../utils/errOut.h"

TextureManager* TextureManager::c_Instance = nullptr;
TextureManager::TextureManager() {

}

TextureManager* TextureManager::getInstance()
{
	if (c_Instance != nullptr) {
		return c_Instance;
	}
	c_Instance = new TextureManager();

	c_Instance->engine = UreTechEngine::UreTechEngineClass::getEngine();
	c_Instance->shaderProg = c_Instance->engine->getShaderProgram();

	return c_Instance;
}

unsigned int TextureManager::loadTextureFromFile(std::string fileName, bool texAntiAlising)
{
	unsigned int texID = -1;
	if (L_TextureMap.count(fileName) != 0) {
		texID = L_TextureMap[fileName];
	}
	else {
		int t_width, t_height, nrChannels;

		stbi_set_flip_vertically_on_load(1);

		unsigned char* textureAddr = stbi_load(fileName.c_str(), &t_width, &t_height, &nrChannels, 0);

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t_width, t_height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureAddr);

		glGenerateMipmap(GL_TEXTURE_2D);
		if (texAntiAlising) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//pixel art i�in GL_NEAREST
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//pixel art i�in GL_NEAREST
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}

		texID = texture;

		stbi_image_free(textureAddr);
	}
	return texID;
}

void TextureManager::applyTexture(int levelInd, unsigned int textureId)
{
	glActiveTexture(levelInd);
	glBindTexture(GL_TEXTURE_2D, textureId);
	//shaderProg->setTexture(std::string("texture") + std::to_string(levelInd - GL_TEXTURE0), levelInd - GL_TEXTURE0);
}

void TextureManager::applyMultipleTexture(std::vector<texture> a)
{
	for(int i = 0; i < a.size(); i++) {
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D, a[i]);
		//UreTechEngine::EngineERROR::consoleError(std::to_string((GLuint)(texArr->getIndex(i))), UreTechEngine::EngineERROR::INFO_NORMAL);
	}
}



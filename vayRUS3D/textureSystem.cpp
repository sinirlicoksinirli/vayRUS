#include"textureSystem.hpp"
#include "src/stb_image.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/mat4x4.hpp>
#include<glm/gtx/matrix_transform_2d.hpp>

TextureManager* TextureManager::c_Instance = nullptr;
TextureManager::TextureManager() {

}

TextureManager* TextureManager::getInstance()
{
	if (c_Instance != nullptr) {
		return c_Instance;
	}
	c_Instance = new TextureManager();
	return c_Instance;
}

unsigned int TextureManager::loadTextureFromFile(std::string fileName)
{
	unsigned int texID = -1;
	if (L_TextureMap.count(fileName) != 0) {
		texID = L_TextureMap[fileName];
	}
	else {
		int t_width, t_height, nrChannels;

		unsigned char* textureAddr = stbi_load(fileName.c_str(), &t_width, &t_height, &nrChannels, 0);

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t_width, t_height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureAddr);

		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		texID = texture;

		stbi_image_free(textureAddr);
	}
	return texID;
}

void TextureManager::applyTexture(unsigned int levelInd, unsigned int textureId)
{
	glActiveTexture(levelInd);
	glBindTexture(GL_TEXTURE_2D, textureId);
}



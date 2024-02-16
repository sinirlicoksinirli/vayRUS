#include"mesh.hpp"

#include"../UreTechEngine/EngineBase.h"
#include"../UreTechEngine/shaders/vertexArray.hpp"
#include"../UreTechEngine/shaders/vertexStructs.hpp"
#include"../UreTechEngine/shaders/textureSystem.hpp"
#include"../UreTechEngine/utils/baseVector.h"
#include"../utils/errOut.h"


#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>

void mesh::draw(UreTechEngine::Transform3D _addTrnsfm)
{
	if (useMultipleTexture) {
		if (textures.size()==1) {
			textManager->applyTexture(GL_TEXTURE0, (texture)textures.getIndex(0));
		}
		else if (textures.size() == 2) {
			textManager->applyTexture(GL_TEXTURE0, (texture)textures.getIndex(0));
			textManager->applyTexture(GL_TEXTURE1, (texture)textures.getIndex(1));

		}
		else if (textures.size() == 3) {
			textManager->applyTexture(GL_TEXTURE0, (texture)textures.getIndex(0));
			textManager->applyTexture(GL_TEXTURE1, (texture)textures.getIndex(1));
			textManager->applyTexture(GL_TEXTURE2, (texture)textures.getIndex(2));
		}
		else if (textures.size() == 4) {
			textManager->applyTexture(GL_TEXTURE0, (texture)textures.getIndex(0));
			textManager->applyTexture(GL_TEXTURE1, (texture)textures.getIndex(1));
			textManager->applyTexture(GL_TEXTURE2, (texture)textures.getIndex(2));
			textManager->applyTexture(GL_TEXTURE3, (texture)textures.getIndex(3));
		}
		else if (textures.size() == 5) {
			textManager->applyTexture(GL_TEXTURE0, (texture)textures.getIndex(0));
			textManager->applyTexture(GL_TEXTURE1, (texture)textures.getIndex(1));
			textManager->applyTexture(GL_TEXTURE2, (texture)textures.getIndex(2));
			textManager->applyTexture(GL_TEXTURE3, (texture)textures.getIndex(3));
			textManager->applyTexture(GL_TEXTURE4, (texture)textures.getIndex(4));
		}
		else if (textures.size() == 6) {
			textManager->applyTexture(GL_TEXTURE0, (texture)textures.getIndex(0));
			textManager->applyTexture(GL_TEXTURE1, (texture)textures.getIndex(1));
			textManager->applyTexture(GL_TEXTURE2, (texture)textures.getIndex(2));
			textManager->applyTexture(GL_TEXTURE3, (texture)textures.getIndex(3));
			textManager->applyTexture(GL_TEXTURE4, (texture)textures.getIndex(4));
			textManager->applyTexture(GL_TEXTURE5, (texture)textures.getIndex(5));
		}
		else {
			UreTechEngine::EngineERROR::consoleError("(Mesh): too much texture or no texture!", UreTechEngine::EngineERROR::ERROR_FATAL);
		}
	}
	else {
		textManager->applyTexture(GL_TEXTURE0, TextureID);
		shaderProg->setTexture(std::string("texture") + std::to_string(0), 0);

	}

	glm::vec3 TransformTransliton = glm::vec3(transform.Location.fx() + _addTrnsfm.Location.fx(), transform.Location.fy() + _addTrnsfm.Location.fy(), transform.Location.fz() + _addTrnsfm.Location.fz());
	UreTechEngine::Rotation _rot;
	_rot.roll += _addTrnsfm.Rotation.roll;
	_rot.pitch += _addTrnsfm.Rotation.pitch;
	_rot.yaw += _addTrnsfm.Rotation.yaw;
	glm::vec3 TransformRotation = glm::vec3(_rot.fRoll(), _rot.fPitch(), _rot.fYaw());
	glm::mat4 TransformScale = glm::scale(glm::mat4(1), glm::vec3(transform.Scale.fx() * _addTrnsfm.Scale.fx(), transform.Scale.fy() * _addTrnsfm.Scale.fy(), transform.Scale.fz() * _addTrnsfm.Scale.fz()));

	shaderProg->setVec3("uTranslation", TransformTransliton);
	shaderProg->setVec3("uRotation", TransformRotation);
	shaderProg->setMat4("uScale", &TransformScale);
	shaderProg->setBool("litRender", litRender);



	p_Vao->activateBuffer();
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	p_Vao->deactivateBuffer();

}

void mesh::applyTexture(texture _text)
{
	TextureID = _text;
}

void mesh::changeLitRender(bool val)
{
	litRender = val;
	shaderProg->setBool("litRender", litRender);
}

mesh::mesh(vertexArrayObject* _p_Vao, texture _text)
{
	textures.setElemSize(sizeof(texture));
	p_Vao = _p_Vao;
	indexCount = p_Vao->getIndexCount();
	TextureID = _text;
	PlayerRef= UreTechEngine::UreTechEngineClass::getEngine()->getPlayer();
	textManager = TextureManager::getInstance();
	if (textManager == nullptr) {
		UreTechEngine::EngineERROR::consoleError("(Mesh): Failed to use texture system!", UreTechEngine::EngineERROR::ERROR_FATAL);
	}
	shaderProg = UreTechEngine::UreTechEngineClass::getEngine()->getShaderProgram();
}

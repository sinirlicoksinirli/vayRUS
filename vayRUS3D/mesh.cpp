#include"mesh.hpp"
#include"vertexArray.hpp"
#include"vertexStructs.hpp"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include "textureSystem.hpp"

void mesh::draw(UreTechEngine::Transform3D _addTrnsfm)
{

	textManager->applyTexture(GL_TEXTURE0, TextureID);

	//glm::mat4 TransformTransliton = glm::translate(glm::mat4(1), glm::vec3(transform.Location.fx()+ _addTrnsfm.Location.fx(), transform.Location.fy()+ _addTrnsfm.Location.fy(), transform.Location.fz()+ _addTrnsfm.Location.fz()));
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

	p_Vao->activateBuffer();
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	p_Vao->deactivateBuffer();
}

void mesh::applyTexture(texture _text)
{
	TextureID = _text;
}

mesh::mesh(vertexArrayObject* _p_Vao, texture _text)
{
	p_Vao = _p_Vao;
	indexCount = p_Vao->getIndexCount();
	TextureID = _text;
	PlayerRef= UreTechEngine::UreTechEngineClass::getEngine()->getPlayer();
	textManager = TextureManager::getInstance();
	if (textManager == nullptr) {
		while (1);
	}
	shaderProg = UreTechEngine::UreTechEngineClass::getEngine()->getShaderProgram();
}

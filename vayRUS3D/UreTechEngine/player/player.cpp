#include "player.h"
#include"../UreTechEngine/utils/baseVector.h"
#include"../UreTechEngine/shaders/shaderSystem.hpp"
#include"../UreTechEngine/EngineBase.h"

void UreTechEngine::Player::updateCamera()
{
	glm::vec3 camPos(CameraTranform.Location.fx(), CameraTranform.Location.fy(), CameraTranform.Location.fz());
	Rotation camRot = CameraTranform.Rotation;
	
	mtxCamPos = glm::translate(glm::mat4(1),camPos);
	CamRot = glm::vec3(camRot.fRoll(), camRot.fPitch(), camRot.fYaw());//ilk bu çarp
	mtxCam = glm::rotate(glm::mat4(1), glm::radians(-90.0f), glm::vec3(1.0f, 0.0001f, 0.0001f));

	mtxProj = glm::perspective(glm::radians(90.0f), (float(UreTechEngine::UreTechEngineClass::displayWidth) / float(UreTechEngine::UreTechEngineClass::displayHeight)), 1.0f, 1000.0f);

	shaderProg->setMat4("uMtxProj", &this->mtxProj);
	shaderProg->setVec3("uCamRot", this->CamRot);
	shaderProg->setMat4("uMtxCamPos", &this->mtxCamPos);
	shaderProg->setMat4("uMtxCam", &this->mtxCam);
	shaderProg->setVec3("lightPos", glm::vec3(1000.0f, 1000.0f, 1000.0f));
}

UreTechEngine::Player::Player()
{
	engineRef = UreTechEngine::UreTechEngineClass::getEngine();
	shaderProg = engineRef->getShaderProgram();
}

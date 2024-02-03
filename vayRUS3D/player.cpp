#include "player.hpp"
#include"EngineBase.h"
#include"shaderSystem.hpp"

void UreTechEngine::Player::updateCamera()
{
	glm::vec3 camPos(CameraTranform.Location.fx(), CameraTranform.Location.fy(), CameraTranform.Location.fz());
	Rotation camRot = CameraTranform.Rotation;
	camRot.roll -= 0.0f;
	mtxCamPos = glm::translate(glm::mat4(1),camPos);
	CamRot = glm::vec3(camRot.fRoll(), camRot.fPitch(), camRot.fYaw());//ilk bu çarp
	mtxCam = glm::rotate(glm::mat4(1), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	mtxProj = glm::perspective(glm::radians(90.0f), (float(UreTechEngine::UreTechEngineClass::displayWidth) / float(UreTechEngine::UreTechEngineClass::displayHeight)), 0.5f, 100.0f);

	shaderProg->setMat4("uMtxProj", &this->mtxProj);
	shaderProg->setVec3("uCamRot", this->CamRot);
	shaderProg->setMat4("uMtxCamPos", &this->mtxCamPos);
	shaderProg->setMat4("uMtxCam", &this->mtxCam);
}

UreTechEngine::Player::Player()
{
	engineRef = UreTechEngine::UreTechEngineClass::getEngine();
	shaderProg = engineRef->getShaderProgram();
}

#include "player.h"
#include"../UreTechEngine/utils/baseVector.h"
#include"../UreTechEngine/shaders/shaderSystem.hpp"
#include"../UreTechEngine/EngineBase.h"

void UreTechEngine::Player::updateCamera()
{
	glm::vec3 camPos;
	Rotation camRot;
	if (playerPawn != nullptr) {
		camPos = glm::vec3(CameraTranform.Location.fx() + playerPawn->transform.Location.x, CameraTranform.Location.fy() + playerPawn->transform.Location.y, CameraTranform.Location.fz() + playerPawn->transform.Location.z);
		camRot.roll = CameraTranform.Rotation.roll + playerPawn->transform.Rotation.roll;
		camRot.pitch = CameraTranform.Rotation.pitch + playerPawn->transform.Rotation.pitch;
		camRot.yaw = CameraTranform.Rotation.yaw + playerPawn->transform.Rotation.yaw;
	}
	else {
		camPos = glm::vec3(CameraTranform.Location.fx(), CameraTranform.Location.fy(), CameraTranform.Location.fz());
		camRot = CameraTranform.Rotation;
	}
	
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

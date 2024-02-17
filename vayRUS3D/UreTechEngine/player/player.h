#ifndef player_h
#define player_h

#include"../UreTechEngine/utils/baseVector.h"
#include"../UreTechEngine/shaders/shaderSystem.hpp"
#include"../entity/entity.h"

class ShaderProgram;
namespace UreTechEngine {
	class UreTechEngineClass;
	class entity;
	class Player {
	public:
		glm::mat4 mtxCamPos;
		glm::vec3 CamRot;
		glm::mat4 mtxCam;

		glm::mat4 mtxProj;

		ShaderProgram* shaderProg;
		UreTechEngineClass* engineRef=nullptr;

		UreTechEngine::Transform3D CameraTranform;
		entity* playerPawn = nullptr;
		void updateCamera();
		Player();

	private:
	};
}
#endif

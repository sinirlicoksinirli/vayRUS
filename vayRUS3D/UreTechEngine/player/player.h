#ifndef player_h
#define player_h

#include"../UreTechEngine/utils/baseVector.h"
#include"../UreTechEngine/shaders/shaderSystem.hpp"

class ShaderProgram;
namespace UreTechEngine {
	class UreTechEngineClass;
	class Player {
	public:
		glm::mat4 mtxCamPos;
		glm::vec3 CamRot;
		glm::mat4 mtxCam;

		glm::mat4 mtxProj;

		ShaderProgram* shaderProg;
		UreTechEngineClass* engineRef=nullptr;

		UreTechEngine::Transform3D CameraTranform;
		void updateCamera();
		Player();

	private:
	};
}
#endif

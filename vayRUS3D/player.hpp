#ifndef player_hpp
#define player_hpp
#include"baseVector.h"
#include"shaderSystem.hpp"
#include"EngineBase.h"
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

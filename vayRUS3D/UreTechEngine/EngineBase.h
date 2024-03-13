#pragma once
#ifndef enginebase_h
#define enginebase_h

#include"../UreTechEngine/utils/baseVector.h"
#include"../UreTechEngine/player/player.h"
#include"../UreTechEngine/shaders/shaderSystem.hpp"
#include"../UreTechEngine/entity/entity.h"

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include"nlohmann/json.hpp"

class mesh;
namespace UreTechEngine {
	class entity;
	class Player;
	class UreTechEngineClass {
	public:
		static unsigned int displayWidth;
		static unsigned int displayHeight;
		bool isInServer = false;
		bool isServer = true;

		ShaderProgram* mainShaderProgram = nullptr;
		static UreTechEngineClass* c_Instance;
		static UreTechEngineClass* getEngine();
		void setKeyCallBackFunc(GLFWkeyfun func, GLFWmousebuttonfun funcM);
		Player* getPlayer();
		ShaderProgram* getShaderProgram();
		GLFWwindow* getWindow();
		entity* spawnEntity(entity* _toSpawn);
		entity* getEntityWithIndex(unsigned int _index);
		entity* getEntityWithName(std::string _entName);
		bool isThisEntNameAvilable(std::string _entName);
		unsigned int getCountOfEntity();

		void engineTick();

		bool killEntity(entity* _ent);
		bool killEntity(std::string entName);
	private:
		nlohmann::json mapJson;
		Player* defPlayer = nullptr;
		GLFWwindow* window = nullptr;
		unsigned int countOfEntity = 0;
		entity* sceneEntities[1000];
		unsigned int netPlayersCount = 0;
		Player* netPlayers[5];
		UreTechEngineClass();
		~UreTechEngineClass();
	};
}
#endif // !enginebase_h
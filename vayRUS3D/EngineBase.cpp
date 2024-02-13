#include "EngineBase.h"
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"player.hpp"

UreTechEngine::UreTechEngineClass* UreTechEngine::UreTechEngineClass::c_Instance = nullptr;
unsigned int UreTechEngine::UreTechEngineClass::displayWidth = 1000;
unsigned int UreTechEngine::UreTechEngineClass::displayHeight = 1000;
UreTechEngine::UreTechEngineClass* UreTechEngine::UreTechEngineClass::getEngine()
{
    if (c_Instance != nullptr) {
        return c_Instance;
    }
    else {
        c_Instance = new UreTechEngineClass();

		//openGL init
		if (!glfwInit()) {
			std::cout << "GL ERROR!";
			while(1){}
		}

		c_Instance->window = glfwCreateWindow(displayWidth, displayHeight, "UreTechEngine BETA1.0.7-Pre_EDITOR OpenGL3.3", NULL, NULL);
		if (c_Instance->window == NULL) {
			std::cout << "WINDOW ERROR!";
			glfwTerminate();
			while (1) {}
		}
		glfwMakeContextCurrent(c_Instance->window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "GLAD ERROR!";
			while (1) {}
		}

		c_Instance->mainShaderProgram = new ShaderProgram();

		c_Instance->mainShaderProgram->attachShader("shaders/baseVS.glsl", GL_VERTEX_SHADER);
		c_Instance->mainShaderProgram->attachShader("shaders/baseFS.glsl", GL_FRAGMENT_SHADER);
		c_Instance->mainShaderProgram->link();
		c_Instance->mainShaderProgram->addUniform("uColor");
		c_Instance->mainShaderProgram->addUniform("uTranslation");
		c_Instance->mainShaderProgram->addUniform("uRotation");
		c_Instance->mainShaderProgram->addUniform("uScale");
		c_Instance->mainShaderProgram->addUniform("uMtxProj");
		c_Instance->mainShaderProgram->addUniform("uMtxCamPos");
		c_Instance->mainShaderProgram->addUniform("uCamRot");
		c_Instance->mainShaderProgram->addUniform("uMtxCam");
		c_Instance->mainShaderProgram->addUniform("litRender");
		c_Instance->mainShaderProgram->addUniform("lightPos");

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glFrontFace(GL_CW);

		glfwWindowHint(GLFW_SAMPLES, 4);
		glEnable(GL_MULTISAMPLE);
		//******

        c_Instance->defPlayer = new Player;
        return c_Instance;
    }
}

void UreTechEngine::UreTechEngineClass::setKeyCallBackFunc(GLFWkeyfun func,GLFWmousebuttonfun funcM)
{
	glfwSetKeyCallback(c_Instance->window, func);
	glfwSetMouseButtonCallback(c_Instance->window, funcM);
}

UreTechEngine::Player* UreTechEngine::UreTechEngineClass::getPlayer()
{
    return defPlayer;
}

ShaderProgram* UreTechEngine::UreTechEngineClass::getShaderProgram()
{
	return mainShaderProgram;
}

GLFWwindow* UreTechEngine::UreTechEngineClass::getWindow()
{
	return window;
}

UreTechEngine::entity* UreTechEngine::UreTechEngineClass::spawnEntity(entity* _toSpawn)
{
	_toSpawn->init(this);
	_toSpawn->begin();
	sceneEntities[countOfEntity] = _toSpawn;
	countOfEntity++;
	return sceneEntities[countOfEntity-1];
}

UreTechEngine::entity* UreTechEngine::UreTechEngineClass::getEntityWithIndex(unsigned int _index)
{
	return sceneEntities[_index];
}

UreTechEngine::entity* UreTechEngine::UreTechEngineClass::getEntityWithName(std::string _entName)
{
	for (int i = 0; i < countOfEntity; i++) {
		if (sceneEntities[i]->entName == _entName) {
			return sceneEntities[i];
		}
	}
	return nullptr;
}

bool UreTechEngine::UreTechEngineClass::isThisEntNameAvilable(std::string _entName)
{
	for (int i = 0; i < countOfEntity; i++) {
		if (sceneEntities[i]->entName == _entName) {
			return false;
		}
	}
	return true;
}

unsigned int UreTechEngine::UreTechEngineClass::getCountOfEntity()
{
	return countOfEntity;
}

void UreTechEngine::UreTechEngineClass::engineTick()
{
	for (int i = 0; i < countOfEntity; i++) {
		sceneEntities[i]->updateVisual();
	}
}

bool UreTechEngine::UreTechEngineClass::killEntity(entity* _ent)
{
	for (int i = 0; i < countOfEntity; i++) {
		if (sceneEntities[i] == _ent) {
			free(sceneEntities[i]);
			for (int c = i; c < 8; ++c) {
				sceneEntities[c] = sceneEntities[c + 1];
			}
			countOfEntity--;
			return true;
		}
	}
	return false;
}

bool UreTechEngine::UreTechEngineClass::killEntity(std::string _entName)
{
	for (int i = 0; i < countOfEntity; i++) {
		if (sceneEntities[i]->entName == _entName) {
			free(sceneEntities[i]);
			for (int c = i; c < 8; ++c) {
				sceneEntities[c] = sceneEntities[c + 1];
			}
			countOfEntity--;
			return true;
		}
	}
	return false;
}

UreTechEngine::UreTechEngineClass::UreTechEngineClass()
{
}


UreTechEngine::UreTechEngineClass::~UreTechEngineClass()
{
}


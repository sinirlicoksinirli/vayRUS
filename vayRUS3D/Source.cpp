#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION   
#include<stb/stb_image.h>

#include"vertexStructs.hpp"
#include"EngineBase.h"
#include"shaderSystem.hpp"
#include"textureSystem.hpp"
#include"vertexArray.hpp"

vertexArrayManager vao;

#define fpslock 60
using namespace std;
GLFWwindow* window = nullptr;
UreTechEngine::entity* TestDumy = nullptr;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(window,1);
	}
	if (key == GLFW_KEY_W) {
		TestDumy->entityLocation.addY(0.02);
	}
	if (key == GLFW_KEY_S) {
		TestDumy->entityLocation.addY(-0.02);
	}
	if (key == GLFW_KEY_D) {
		TestDumy->entityLocation.addX(0.02);
	}
	if (key == GLFW_KEY_A) {
		TestDumy->entityLocation.addX(-0.02);
	}
}

int main(int argc, char** argv) {
	//init3D object buffers
	initTestCubeVertices();
	//******

	if (!glfwInit()) {
		cout<<"GL ERROR!";
	    return -1;
	}

	TextureManager* textureManager = TextureManager::getInstance();

	window = glfwCreateWindow(800,800,"UreTechEngine BETA1.1 OpenGL3.3",NULL,NULL);

	if (window == NULL) {
		cout << "WINDOW ERROR!";
		glfwTerminate();
		return -1;
	}
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "GLAD ERROR!";
		return -1;
	}

	ShaderProgram mainRenderSystem;
	mainRenderSystem.attachShader("baseVS.glsl", GL_VERTEX_SHADER);
	mainRenderSystem.attachShader("baseFS.glsl", GL_FRAGMENT_SHADER);
	mainRenderSystem.link();

	mainRenderSystem.addUniform("uColor");
	mainRenderSystem.addUniform("uTransform");

	vao.createObject(testCubeVertices[0],size(testCubeVertices), testCubeIndecies[0],size(testCubeIndecies));

	TestDumy = new UreTechEngine::entity(0.0, 0.0, 0.0);
	TestDumy->T_entityMatColor.x = 1;
	glm::mat4 Transform(1);
	float rot = 0;

	unsigned int Texture0 = textureManager->loadTextureFromFile("textures/text.jpg");

	glm::mat4 mtxProj = glm::perspective(glm::radians(90.0f), (800.0f / 800.0f), 0.5f, 1000.0f);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {

		//glm::vec4 color(TestDumy->T_entityMatColor.fx(), TestDumy->T_entityMatColor.fy(), TestDumy->T_entityMatColor.fz(), TestDumy->T_entityMatColor.fw());
		
		glClearColor(0.0f, 0.2f,0.4f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glm::vec3 camPos(1.0f, 1.0f, 1.0f);
		glm::vec3 camLookingPos(0.0f, 0.0f, 0.0f);
		glm::vec3 camUp(0.0f, 1.0f, 0.0f);

		glm::mat4 mtxCam = glm::lookAt(camPos, camLookingPos, camUp);

		mainRenderSystem.use();

		vao.activateBuffer();

		textureManager->applyTexture(GL_TEXTURE0, Texture0);
		rot += 0.01;

		glm::mat4 TransformTransliton = glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.0f, TestDumy->entityLocation.fz()));
		glm::mat4 TransformRotation = glm::rotate(glm::mat4(1), glm::radians(rot),glm::vec3(0.0f, 1.0f, 1.0f));
		glm::mat4 TransformScale = glm::scale(glm::mat4(1), glm::vec3(1.0,1.0,1.0));
		Transform = mtxProj * mtxCam*TransformTransliton * TransformRotation * TransformScale;

		mainRenderSystem.setMat4("uTransform", &Transform);
		glDrawElements(GL_TRIANGLES, size(testCubeIndecies), GL_UNSIGNED_INT,0);

		vao.deactivateBuffer();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}
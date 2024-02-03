#define Editor_Mode true

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION

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
#include"MeshManager.hpp"
#include"mesh.hpp"
#include"3DMath.hpp"
#include"Array.hpp"

#include"UreTechCube.h"
#include"UreTechPyramid.h"

#include"vayrusCube.h"

#include <thread>
#include<map>


vertexArrayObject EngineTestCubeVao;
vertexArrayObject EngineTestPyramidVao;

#define fpslock 60
int display_w, display_h;
bool isEditor = 0;
using namespace std;
using namespace UreTechEngine;

entity* TestDumy = nullptr;

float editorCamRoll=0.0f;
float editorCamYaw = 0.0f;

float editorCamPos[3] = { 0.0f,0.0f,0.0f };

bool rClickL = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	glfwCreateStandardCursor(GLFW_ARROW_CURSOR);

	if (key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(window,1);
	}
	if (key == GLFW_KEY_W && rClickL) {
		
	}
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (rClickL) {
			rClickL = false;
		}
		else {
			rClickL = true;
		}
	}
}

int main(int argc, char** argv) {
	//init engine
	UreTechEngine::UreTechEngineClass* engine = UreTechEngine::UreTechEngineClass::getEngine();//init engine
	GLFWwindow* window = engine->getWindow();
	engine->setKeyCallBackFunc(key_callback, mouse_button_callback);

	UreTechEngine::Player* Player= engine->getPlayer();//get player ref
	TextureManager* textureManager = TextureManager::getInstance();//create texture manager
	MeshManager* meshManager = MeshManager::getInstance();
	int icoW, icoH, icoC;
	unsigned char* icoimg = stbi_load("icon.png", &icoW, &icoH, &icoC, 0);
	GLFWimage icon[1];
	icon[0].width = icoW;
	icon[0].height = icoH;
	icon[0].pixels = icoimg;
	glfwSetWindowIcon(window, 1, icon);
	//******

	//textures
	texture Texture0 = textureManager->loadTextureFromFile("textures/text.jpg");
	texture Texture1 = textureManager->loadTextureFromFile("textures/text2.png");


	EngineTestCubeVao.createObject(testCubeVertices[0],size(testCubeVertices), testCubeIndecies[0],size(testCubeIndecies));
	EngineTestPyramidVao.createObject(testPyramidVertices[0], size(testPyramidVertices), testPyramidIndecies[0], size(testPyramidIndecies));

	mesh* mesh0 = meshManager->importMeshFbx("yes.obj", Texture0);
	mesh cubeMesh(&EngineTestCubeVao, Texture0);
	mesh pyramidMesh(&EngineTestPyramidVao, Texture1);
	pyramidMesh.transform.Location.x = 1.0f;
	cubeMesh.transform.Scale.x = 0.5f;
	cubeMesh.transform.Scale.y = 0.5f;
	cubeMesh.transform.Scale.z = 0.5f;

	Player->CameraTranform.Location.x = 0.0f;
	Player->CameraTranform.Location.y = 0.0f;
	Player->CameraTranform.Location.z = 0.0f;

	Transform3D a(vector3(1.0f, 1.0f, 0.0f), Rotation(0.0f, 0.0f, 0.0f), vector3(1.0f, 1.0f, 1.0f));
	Transform3D b(vector3(-1.0f, 1.0f, 0.0f), Rotation(0.0f, 0.0f, 0.0f), vector3(1.0f, 1.0f, 1.0f));
	Transform3D c(vector3(1.0f, -1.0f, 0.0f), Rotation(0.0f, 0.0f, 0.0f), vector3(1.0f, 1.0f, 1.0f));
	Transform3D d(vector3(-1.0f, -1.0f, 0.0f), Rotation(0.0f, 0.0f, 0.0f), vector3(1.0f, 1.0f, 1.0f));

	TestDumy = engine->spawnEntity(new entity(a.Location,a.Rotation,a.Scale, mesh0,"Dummy1"));
	engine->spawnEntity(new entity(b.Location, b.Rotation, b.Scale, &cubeMesh, "Dummy2"));
	engine->spawnEntity(new entity(c.Location, c.Rotation, c.Scale, &cubeMesh, "Dummy3"));
	engine->spawnEntity(new entity(d.Location, d.Rotation, d.Scale, &cubeMesh, "Dummy4"));

	float rot = 0;

	glEnable(GL_DEPTH_TEST);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();

	Transform3D editorEditTransform(vector3(0.0f, 0.0f, 0.0f), Rotation(0.0f, 0.0f, 0.0f), vector3(1.0f, 1.0f, 1.0f));
	float editorTransformLoc[3] = { 0.0f,0.0f,0.0f };
	float editorTransformRot[3] = { 0.0f,0.0f,0.0f };
	float editorTransformScl[3] = { 1.0f,1.0f,1.0f };

	entity* selectedEntityEngine = nullptr;

	//editor spawnables
	std::map<std::string, std::function<entity* ()>> spawnables;

	spawnables["entity"] = []() { return new entity(); };
	spawnables["vayrusCube"] = []() { return new vayrusCube(); };

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		engine->getShaderProgram()->use();

		double xpos, ypos;
		double lxpos, lypos;

		glfwGetCursorPos(window, &xpos, &ypos);
		if (rClickL) {
			editorCamYaw += lxpos - xpos;
			editorCamRoll += lypos - ypos;
		}
		//end of exec
		lxpos = xpos;
		lypos = ypos;

		Player->CameraTranform.Rotation.roll = editorCamRoll;
		Player->CameraTranform.Rotation.pitch = editorCamYaw;

		Player->CameraTranform.Location.x = editorCamPos[0];
		Player->CameraTranform.Location.y = editorCamPos[1];
		Player->CameraTranform.Location.z = editorCamPos[2];

		Player->updateCamera();


		engine->engineTick();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		//editor UI
		if(Editor_Mode)
			{
			//SPAWN WINDOW
			ImGui::SetNextWindowPos(ImVec2(display_w - 450, display_h - 880));
			ImGui::SetNextWindowSize(ImVec2(450, 80));
			ImGui::Begin("Creator", NULL, ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse);
			char editorSpawnTextInput[150];
			ImGui::Text("Class Name:");
			if (ImGui::InputText("class", editorSpawnTextInput, 150, ImGuiInputTextFlags_EnterReturnsTrue)) {
					auto it = spawnables.find(string(editorSpawnTextInput));
					if (it != spawnables.end()) {
						entity* spawned = engine->spawnEntity(it->second());
					}
				memset(editorSpawnTextInput, 0, 150);
			}

			ImGui::End();
			//SPAWN WINDOW END

			//EXPLORER WINDOW
			ImGui::SetNextWindowPos(ImVec2(display_w - 450, display_h - 800));
			ImGui::SetNextWindowSize(ImVec2(450, 500));
			ImGui::Begin("Explorer", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

			for (int i = 0; i < engine->getCountOfEntity(); i++) {
				ImGui::PushItemWidth(450);
				ImGui::Text(engine->getEntityWithIndex(i)->entName.c_str());
				ImGui::SameLine();
				ImGui::PushID(to_string(i).c_str());
				if (ImGui::Button(string(string("select ") + engine->getEntityWithIndex(i)->entName).c_str())) {
					selectedEntityEngine = engine->getEntityWithIndex(i);
					editorEditTransform = engine->getEntityWithIndex(i)->transform;
					editorTransformLoc[0] = editorEditTransform.Location.fx();
					editorTransformLoc[1] = editorEditTransform.Location.fy();
					editorTransformLoc[2] = editorEditTransform.Location.fz();

					editorTransformRot[0] = editorEditTransform.Rotation.fRoll();
					editorTransformRot[1] = editorEditTransform.Rotation.fPitch();
					editorTransformRot[2] = editorEditTransform.Rotation.fYaw();

					editorTransformScl[0] = editorEditTransform.Scale.fx();
					editorTransformScl[1] = editorEditTransform.Scale.fy();
					editorTransformScl[2] = editorEditTransform.Scale.fz();
				}
				ImGui::SameLine();
				if (ImGui::Button(string(string("destroy ") + engine->getEntityWithIndex(i)->entName).c_str())) {
					engine->killEntity(engine->getEntityWithIndex(i));
					selectedEntityEngine = nullptr;
				}
				ImGui::PopID();
			}
			ImGui::End();
			//EXPLORER WINDOW END

			//TRANSFORM WINDOW
			ImGui::SetNextWindowPos(ImVec2(display_w - 450, display_h - 300));
			ImGui::SetNextWindowSize(ImVec2(450, 300));
			if (selectedEntityEngine == nullptr) {
				ImGui::Begin("Transform", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
			}

			if (selectedEntityEngine != nullptr) {
				ImGui::Begin(string(string("Transform ") + selectedEntityEngine->entName).c_str(), &isEditor, ImGuiWindowFlags_NoMove);
				ImGui::Text("Location");
				ImGui::PushItemWidth(360);
				ImGui::DragFloat3("Location", editorTransformLoc,0.1f);
				ImGui::PushItemWidth(360);
				ImGui::Text("Rotation");
				ImGui::DragFloat3("Rotation", editorTransformRot,2.0f);
				ImGui::PushItemWidth(360);
				ImGui::Text("Scale");
				ImGui::DragFloat3("Scale", editorTransformScl, 0.1f);
			}
			ImGui::End();
			//TRANSFORM WINDOW END
		}
		//editor UI end
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		if (selectedEntityEngine != nullptr) {
			editorEditTransform.Location.x = editorTransformLoc[0];
			editorEditTransform.Location.y = editorTransformLoc[1];
			editorEditTransform.Location.z = editorTransformLoc[2];

			editorEditTransform.Rotation.roll = editorTransformRot[0];
			editorEditTransform.Rotation.pitch = editorTransformRot[1];
			editorEditTransform.Rotation.yaw = editorTransformRot[2];

			editorEditTransform.Scale.x = editorTransformScl[0];
			editorEditTransform.Scale.y = editorTransformScl[1];
			editorEditTransform.Scale.z = editorTransformScl[2];

			selectedEntityEngine->transform = editorEditTransform;
		}

		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		UreTechEngine::UreTechEngineClass::displayWidth = display_w;
		UreTechEngine::UreTechEngineClass::displayHeight = display_h;

		glfwSwapInterval(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}
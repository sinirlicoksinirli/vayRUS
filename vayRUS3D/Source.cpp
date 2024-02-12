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

//networking
#include<WinSock2.h>
#include"network.h"

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

UreTechEngine::Player* player = nullptr;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	glfwCreateStandardCursor(GLFW_ARROW_CURSOR);

	if (key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(window,1);
	}
	if (key == GLFW_KEY_W && rClickL) {
		vector3 change = Math3D::addWithRotation(player->CameraTranform.Rotation, vector3(0.1f, 0.0f, 0.0f), vector3(editorCamPos[0], editorCamPos[1], editorCamPos[2]));
		editorCamPos[0] = change.fx();
		editorCamPos[1] = change.fy();
	}
	if (key == GLFW_KEY_S && rClickL) {
		vector3 change = Math3D::addWithRotation(player->CameraTranform.Rotation, vector3(-0.1f, 0.0f, 0.0f), vector3(editorCamPos[0], editorCamPos[1], editorCamPos[2]));
		editorCamPos[0] = change.fx();
		editorCamPos[1] = change.fy();
	}

	if (key == GLFW_KEY_D && rClickL) {
		vector3 change = Math3D::addWithRotation(player->CameraTranform.Rotation, vector3(0.0f, 0.1f, 0.0f), vector3(editorCamPos[0], editorCamPos[1], editorCamPos[2]));
		editorCamPos[0] = change.fx();
		editorCamPos[1] = change.fy();
	}
	if (key == GLFW_KEY_A && rClickL) {
		vector3 change = Math3D::addWithRotation(player->CameraTranform.Rotation, vector3(0.0f, -0.1f, 0.0f), vector3(editorCamPos[0], editorCamPos[1], editorCamPos[2]));
		editorCamPos[0] = change.fx();
		editorCamPos[1] = change.fy();
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

	player = engine->getPlayer();//get player ref
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
	texture grass01Texture = textureManager->loadTextureFromFile("textures/grass01.jpg");
	texture Texture2 = textureManager->loadTextureFromFile("textures/skysphere01.jpg");

	mesh* mesh0 = meshManager->importMeshFbx("flaty.obj", grass01Texture);
	mesh* mesh1 = meshManager->importMeshFbx("cube.obj", Texture0);
	mesh* mesh2 = meshManager->importMeshFbx("skysphere.obj", Texture2);

	player->CameraTranform.Location.x = -1.0f;
	player->CameraTranform.Location.y = 0.0f;
	player->CameraTranform.Location.z = 1.5f;

	Transform3D a(vector3(0.0f, 0.0f, -1.0f), Rotation(0.0f, 0.0f, 0.0f), vector3(1.0f, 1.0f, 1.0f));
	Transform3D b(vector3(-1.0f, 1.0f, -0.6f), Rotation(0.0f, 0.0f, 0.0f), vector3(0.3f, 0.3f, 0.3f));
	Transform3D c(vector3(1.0f, -1.0f, -0.6f), Rotation(0.0f, 0.0f, 0.0f), vector3(0.3f, 0.3f, 0.3f));
	Transform3D d(vector3(-1.0f, -1.0f, -0.6f), Rotation(0.0f, 0.0f, 0.0f), vector3(0.3f, 0.3f, 0.3f));
	Transform3D e(vector3(0.0f, 0.0f, 0.0f), Rotation(-30.0f, -90.0f, 0.0f), vector3(1.0f, 1.0f, 1.0f));

	if (mesh0 == nullptr) {
		while (1);
		std::cout << "ERROR(engine):null obj file!";
	}

	TestDumy = engine->spawnEntity(new entity(a.Location,a.Rotation,a.Scale, mesh0,"Dummy1"));
	engine->spawnEntity(new entity(b.Location, b.Rotation, b.Scale, mesh1, "Dummy2"));
	engine->spawnEntity(new entity(c.Location, c.Rotation, c.Scale, mesh1, "Dummy3"));
	engine->spawnEntity(new entity(d.Location, d.Rotation, d.Scale, mesh1, "Dummy4"));
	mesh2->changeLitRender(false);
	engine->spawnEntity(new entity(e.Location, e.Rotation, e.Scale, mesh2, "Dummy5"));

	float rot = 0;

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
	if (engine->isServer) {
		networkSystem::getNetworkSystem()->startServer();
	}
	else {
		networkSystem::getNetworkSystem()->connectToServer();
	}
	//editor spawnables
	std::map<std::string, std::function<entity* ()>> spawnables;

	spawnables["entity"] = []() { return new entity(); };
	spawnables["vayrusCube"] = []() { return new vayrusCube(); };

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		engine->getShaderProgram()->use();

		double xpos, ypos;
		double lxpos, lypos;

		glfwGetCursorPos(window, &xpos, &ypos);
		if (rClickL) {
			editorCamYaw += lxpos - xpos;
			editorCamRoll += lypos - ypos;

			if (editorCamRoll > 90.0f) {
				editorCamRoll = 90.0f;
			}else if (editorCamRoll < -90.0f) {
				editorCamRoll = -90.0f;
			}
		}
		//end of exec
		lxpos = xpos;
		lypos = ypos;

		player->CameraTranform.Rotation.roll = editorCamRoll;
		player->CameraTranform.Rotation.pitch = editorCamYaw;

		player->CameraTranform.Location.x = editorCamPos[0];
		player->CameraTranform.Location.y = editorCamPos[1];
		player->CameraTranform.Location.z = editorCamPos[2];

		player->updateCamera();


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

		glfwSwapInterval(1);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}
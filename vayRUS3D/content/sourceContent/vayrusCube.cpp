#include"vayrusCube.h"

#include"../UreTechEngine/shaders/textureSystem.hpp"
#include"../UreTechEngine/shaders/MeshManager.hpp"

#include<iostream>
vayrusCube::vayrusCube(void) {
	//constructor
}
void vayrusCube::begin() {
	//add your begin commands here
	texture tex = TextureManager::getInstance()->loadTextureFromFile("textures/text2.png");
	entityMesh = MeshManager::getInstance()->importMeshFbx("a.obj",tex);
	entName = "vayrusCube";
}

void vayrusCube::tick() {
	//add your loop commands here
}
#include"vayrusCube.h"
#include"textureSystem.hpp"
#include"vertexArray.hpp"
#include"UreTechCube2.h"
#include"MeshManager.hpp"

#include<iostream>
vayrusCube::vayrusCube() {
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
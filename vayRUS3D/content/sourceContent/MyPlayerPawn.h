#pragma once
#ifndef MyPlayerPawn_h
#define MyPlayerPawn_h
#include"../UreTechEngine/entity/entity.h"
#include"../UreTechEngine/utils/baseVector.h"
#include"../UreTechEngine/shaders/shaderSystem.hpp"
using namespace UreTechEngine;
class MyPlayerPawn : public UreTechEngine::entity{
public:
	MyPlayerPawn(void);
	MyPlayerPawn(mesh* _mesh, std::string _entName, UreTechEngine::Transform3D trnsfrm = Transform3D(vector3(0.0f, 0.0f, 0.0f), Rotation(0.0f, 0.0f, 0.0f), vector3(1.0f, 1.0f, 1.0f)));
	void begin();
private:
};

#endif // !MyPlayerPawn_h


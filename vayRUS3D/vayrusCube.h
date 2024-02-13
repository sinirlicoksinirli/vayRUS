#pragma once
#ifndef vayrusCube_h
#define vayrusCube_h

#include"../UreTechEngine/entity/entity.h"

class vayrusCube :public UreTechEngine::entity {
public:
	vayrusCube();
	void begin();
	void tick();
};

#endif


#pragma once
#include <string>
#include"baseVector.h"
namespace UreTechEngine {
	class entity {
	public:
		std::string entName = "NONE";
		vector3 entityLocation;
		vector4 T_entityMatColor;
		entity(double _x = 0.0, double _y = 0.0, double _z = 0.0, std::string entName = "NONE");
	};
}
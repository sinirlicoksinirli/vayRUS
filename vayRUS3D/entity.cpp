#include"entity.h"
namespace UreTechEngine {
	entity::entity(double _x, double _y , double _z , std::string _entName )
	{
		entityLocation = vector3(_x = 0.0, _y = 0.0, _z = 0.0);
		entName = _entName;
	}
}
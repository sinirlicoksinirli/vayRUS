#include"mesh.hpp"
#include"baseVector.h"
#include"entity.h"

#define entity_cpp

void UreTechEngine::entity::updateVisual()
{
	entityMesh->draw(transform);
}

void UreTechEngine::entity::init(UreTechEngineClass* _ptr)
{
	engineRef = _ptr;
}

void UreTechEngine::entity::begin()
{
}

void UreTechEngine::entity::tick()
{
}

UreTechEngine::entity::entity(UreTechEngine::vector3& location,UreTechEngine::Rotation& rot,UreTechEngine::vector3& scale, mesh* _mesh, std::string _entName)
	{
		transform.Location = location;
		transform.Rotation = rot;
		transform.Scale = scale;
		entityMesh = _mesh;
		entName = _entName;
	}

UreTechEngine::entity::entity(UreTechEngine::vector3& location, mesh* _mesh, std::string _entName)
{
	transform.Location = location;
	entityMesh = _mesh;
	entName = _entName;
}

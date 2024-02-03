#include"baseVector.h"
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>

namespace UreTechEngine {
	class Math3D{
		virtual vector3 addWithRotation(Rotation _rot,vector3 _force,vector3 _toAdd) {
			vector3 result = _toAdd;
			/*
			result.x += strafeVector.x;
			result.y += strafeVector.y;
			result.z += strafeVector.z;
			*/

		}
	};
}
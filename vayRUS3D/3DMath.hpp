#include"baseVector.h"
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>

namespace UreTechEngine {
	class Math3D{
	public:
		static vector3 addWithRotation(Rotation _rot,vector3 _force,vector3 _toAdd) {
			vector3 result = _toAdd;

			Rotation absRot = _rot.convertMaxFullAngle();

			double radians = (absRot.pitch-90) * 3.14159f / 180.0f;

			double exactXxChange = _force.x *-1* cos(radians);
			double exactXyChange = _force.x *-1* sin(radians);

			double exactYxChange= _force.y *-1* sin(radians);
			double exactYyChange = _force.y *-1* cos(radians);

			std::cout << absRot.pitch  <<std::endl;

			result.x = exactXxChange+ exactYxChange +_toAdd.x;
			result.y = exactXyChange- exactYyChange + _toAdd.y;

			return result;
		}
	};
}
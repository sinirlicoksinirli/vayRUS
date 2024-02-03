#include"vertexStructs.hpp"

Vertex::Vertex(float x, float y, float z, float tX, float tY)
{
	{
		pos.x = x;
		pos.y = y;
		pos.z = z;

		tex.x = tX;
		tex.y = tY;
	}
}

#include "Maths.h"

void moveVector3(vec3 * vector, vec3 moveBy)
{
	vector->x += moveBy.x;
	vector->y += moveBy.y;
	vector->z += moveBy.z;
}

void rotateVector(vec3 * vector, float rotateBy, int axis)
{

	vec3 axisVec;

	switch (axis)
	{
	case X_AXIS:
		axisVec = vec3(1.0f, 0.0f, 0.0f);
		break;
	case Y_AXIS:
		axisVec = vec3(0.0f, 1.0f, 0.0f);
		break;
	case Z_AXIS:
		axisVec = vec3(0.0f, 0.0f, 1.0f);
		break;
	default:
		return;
		break;
	}

	mat4 rotationMatrix = glm::rotate(rotateBy, axisVec);

	vec3 resultVec = mat3(rotationMatrix) * *(vector);

	vector->x = resultVec.x;
	vector->y = resultVec.y;
	vector->z = resultVec.z;

}

#include "Maths.h"

void moveVector3(glm::vec3 * vector, glm::vec3 moveBy)
{
	vector->x += moveBy.x;
	vector->y += moveBy.y;
	vector->z += moveBy.z;
}

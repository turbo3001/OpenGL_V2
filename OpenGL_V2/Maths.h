#pragma once
//GLM (Used for OpenGL Matrix Maths)
#include "lib\GLM\glm\glm.hpp"
#include "lib\GLM\glm\gtc\matrix_transform.hpp"
#include "lib\GLM\glm\gtc\type_ptr.hpp"
#include "lib\GLM\glm\gtx\rotate_vector.hpp"

using namespace glm;

const int X_AXIS = 0;
const int Y_AXIS = 1;
const int Z_AXIS = 2;

void moveVector3(vec3* vector, vec3 moveBy);

void rotateVector(vec3 * vector, float rotateBy, int axis);
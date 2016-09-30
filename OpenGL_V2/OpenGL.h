#pragma once
//External Includes
#include <math.h>

// Internal Includes
#include "Constants.h"
#include "Globals.h"
#include "Maths.h"
#include "OpenGLDependancies.h"
#include "GLShaderProgram.h"
#include "Camera.h"
#include "ShaderReader.hpp"
#include "UpdateObject.h"
#include "TestObject.h"

class OpenGLScene
{

public:
	OpenGLScene();
	~OpenGLScene();

	void init();
	void update(UpdateObject updateObject);
	void draw();
	void cleanUp();

private:

	/**OPENGL VARIABLES**/
	GLShaderProgram m_shaderProgram;

	/**VARIABLES**/
	Camera m_camera;

	TestObject testObject;

	float eventWriteTimer;
};
#pragma once
//External Includes

// Internal Includes
#include "Constants.h"
#include "Globals.h"
#include "Maths.h"
#include "OpenGLDependancies.h"
#include "GLShaderProgram.h"
#include "ShaderReader.hpp"
#include "UpdateObject.h"

class OpenGL
{

public:
	OpenGL();
	~OpenGL();

	void init();
	void update(UpdateObject updateObject);
	void draw();
	void cleanUp();

private:

	/**OPENGL VARIABLES**/
	GLShaderProgram m_shaderProgram;

	GLuint ref_vertexShader;
	GLuint ref_fragmentShader;
	GLuint ref_shaderProgram;

	GLuint ref_vertexArrayObject;
	GLuint ref_vertexBufferObject;
	GLuint ref_elementBufferObject;

	GLuint ref_textures[2];

	/**VARIABLES**/
	float rotation;
	float scaleAmount;
};
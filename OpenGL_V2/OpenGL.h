#pragma once
//External Includes
// GLEW (Used to for dynamically linking functions in OpenGL for use on different graphics cards/drivers)
#define GLEW_STATIC //Needs to be defined for GLEW
#include <GL/glew.h>
// Simple OpenGL Image Library (Used to load textures to an array)
#include <SOIL.h>

// Internal Includes
#include "Constants.h"
#include "Globals.h"
#include "Maths.h"
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

	/**OPENGL REFERENCES**/
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
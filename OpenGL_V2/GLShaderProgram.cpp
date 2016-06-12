#include "GLShaderProgram.h"

GLShaderProgram::GLShaderProgram()
{
	m_vertexShader = new VertexShader("vertexShader.glsl");
	m_fragmentShader = new FragmentShader("fragmentShader.glsl");
}

GLShaderProgram::~GLShaderProgram()
{

}

GLuint GLShaderProgram::getReference()
{
	return reference;
}

void GLShaderProgram::init()
{
	// Initialse Shaders
	// Vertex Shader
	m_vertexShader->init();

	// Fragment/Pixel Shader
	m_fragmentShader->init();

	// Compile Shader Program
	reference = glCreateProgram();
	glAttachShader(reference, m_vertexShader->getReference());
	glAttachShader(reference, m_fragmentShader->getReference());

	// Let Fragment Shader know where to output
	glBindFragDataLocation(reference, 0, "outColour");

	// Tell OpenGL which program to use.
	glLinkProgram(reference);
	glUseProgram(reference);
}

void GLShaderProgram::cleanUp()
{
	//Delete Shader Program
	glDeleteProgram(reference);
	//Delete Fragment and Vertex Shaders
	m_fragmentShader->cleanUp();
	m_vertexShader->cleanUp();
}

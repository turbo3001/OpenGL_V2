#include "VertexShader.h"

VertexShader::VertexShader(const char * shaderName)
{
	this->shaderName = shaderName;
}

VertexShader::~VertexShader()
{
}

void VertexShader::init()
{
	// Read Shader from File
	std::string vertexSourceStr = readShader(shaderName);
	const char *vertexSource = vertexSourceStr.c_str(); // openGL requires the source to be on char[] rather than std::String

	if (vertexSourceStr == "")
	{
		ExitCode = VERTEX_SHADER_COMPILE_ERROR;
		return;
	}

	reference = glCreateShader(GL_VERTEX_SHADER); // Get a reference to a Vertex Shader

	// Load char[] into and compile shader.
	glShaderSource(reference, 1, &vertexSource, NULL);
	glCompileShader(reference);

	// Handle any shader compile errors
	GLint shaderCompileStatus;
	glGetShaderiv(reference, GL_COMPILE_STATUS, &shaderCompileStatus);
	if (shaderCompileStatus != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(reference, 512, NULL, buffer);
		printf("An Error occurred when compiling vertex shader: %s", buffer);
		ExitCode = VERTEX_SHADER_COMPILE_ERROR;
		return;
	}
}

GLuint VertexShader::getReference()
{
	return reference;
}

void VertexShader::cleanUp()
{
	glDeleteShader(reference);
}

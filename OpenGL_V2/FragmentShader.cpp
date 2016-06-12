#include "FragmentShader.h"



FragmentShader::FragmentShader(char* shaderName)
{
	this->shaderName = shaderName;
}

FragmentShader::~FragmentShader()
{
}

void FragmentShader::init()
{
	//Reader Shader from File
	std::string fragmentSourceStr = readShader(shaderName);
	const char *fragmentSource = fragmentSourceStr.c_str();

	if (fragmentSourceStr == "")
	{
		ExitCode = FRAGMENT_SHADER_COMPILE_ERROR;
		return;
	}

	reference = glCreateShader(GL_FRAGMENT_SHADER); // Get a reference to a Fragment Shader

	//Load char[] into and compile shader.
	GLint shaderCompileStatus;
	glShaderSource(reference, 1, &fragmentSource, NULL);
	glCompileShader(reference);

	// Handle any Shader errors (using previous shaderCompileStatus as if we're here 
	glGetShaderiv(reference, GL_COMPILE_STATUS, &shaderCompileStatus);
	if (shaderCompileStatus != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(reference, 512, NULL, buffer);
		printf("An Error occurred when compiling fragment shader: %s", buffer);
		ExitCode = FRAGMENT_SHADER_COMPILE_ERROR;
		return;
	}
}

GLuint FragmentShader::getReference()
{
	return reference;
}

void FragmentShader::cleanUp()
{
	glDeleteShader(reference);
}

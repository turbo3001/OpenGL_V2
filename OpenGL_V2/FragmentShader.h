#pragma once
#include "IOpenGLObject.h"
#include "Constants.h"
#include "Globals.h"
#include "ShaderReader.hpp"

class FragmentShader : public IOpenGLObject
{
public:
	FragmentShader(char* shaderName);
	~FragmentShader();

	/* Implent IOpenGLObject functions */
	virtual void init();
	virtual GLuint getReference();
	virtual void cleanUp();

private:
	char* shaderName;

};
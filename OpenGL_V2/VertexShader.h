#pragma once
#include "IOpenGLObject.h"
#include "Constants.h"
#include "Globals.h"
#include "ShaderReader.hpp"

class VertexShader : public IOpenGLObject
{
public:
	VertexShader(const char* shaderName);
	~VertexShader();
	
	/* Implent IOpenGLObject functions */
	virtual void init();
	virtual GLuint getReference();
	virtual void cleanUp();


private:
	const char* shaderName;

};
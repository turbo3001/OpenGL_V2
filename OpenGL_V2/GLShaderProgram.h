#pragma once
#include "IOpenGLObject.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderReader.hpp"
#include "UpdateObject.h"
#include "Constants.h"
#include "Globals.h"
#include "Maths.h"

class GLShaderProgram : public IOpenGLObject
{
public:
	GLShaderProgram();
	~GLShaderProgram(); 

	virtual GLuint getReference();
	
	virtual void init();
	virtual void cleanUp();

private:
	VertexShader* m_vertexShader;
	FragmentShader* m_fragmentShader;
};
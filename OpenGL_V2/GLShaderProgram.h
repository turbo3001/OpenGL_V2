#pragma once
#include "IOpenGLObject.h"

class GLShaderProgram : public IOpenGLObject
{
public:
	GLShaderProgram();
	~GLShaderProgram(); 

	virtual GLuint getReference();
	
	virtual void init();
	virtual void cleanUp();

private:

};
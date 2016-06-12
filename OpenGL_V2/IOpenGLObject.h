#pragma once
#include "OpenGLDependancies.h"

class IOpenGLObject
{
	public:
		virtual ~IOpenGLObject() {};

		virtual GLuint getReference() = 0;

		virtual void init() = 0;
		virtual void cleanUp() = 0;

	protected:
		GLuint reference;

	private:
};

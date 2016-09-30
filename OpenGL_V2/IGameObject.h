#pragma once
// External Includes
// SDL (Used for Window and Context)
#include <SDL.h>
// Internal Includes
#include "UpdateObject.h"
#include "GLShaderProgram.h"

class IGameObject
{
public:
	virtual ~IGameObject() {};

	virtual void init(GLShaderProgram graphics) = 0;
	virtual void handleInput(SDL_Event inputEvent) = 0;
	virtual void update(UpdateObject updateObject) = 0;
	virtual void draw(GLShaderProgram graphics) = 0;
	virtual void cleanUp() = 0;

private:

};
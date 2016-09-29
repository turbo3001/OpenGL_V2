#pragma once
// External Includes
// SDL (Used for Window and Context)
#include <SDL.h>
// Internal Includes
#include "Constants.h"
#include "Globals.h"
#include "OpenGL.h"
#include "UpdateObject.h"

class Context
{
public:
	Context();
	~Context();

	void init();
	void handleInput(UpdateObject forUpdate);
	void update(UpdateObject update);
	void draw();
	void cleanUp();

private:
	SDL_Window* m_window; // SDL Window
	SDL_GLContext m_context; // SDL Context
	SDL_Event m_windowEvent; // Create SDL_Event object, this will listen for window events later.
	
	OpenGLScene m_openGL; // openGL Object

};
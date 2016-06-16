#include "Context.h"


Context::Context()
{
	m_openGL = OpenGL();
}

Context::~Context()
{
	m_openGL.~OpenGL();
}

void Context::init()
{
	// Inialise SDL Window and Context
	SDL_Init(SDL_INIT_VIDEO); //Initialise SDL

							  // Tell SDL we want a OpenGL context.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	// Create the window
	m_window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

	// Contain mouse in screen
	//sSDL_SetRelativeMouseMode(SDL_TRUE);

	// Create the context
	m_context = SDL_GL_CreateContext(m_window);

	m_openGL.init();
}

void Context::update(UpdateObject update)
{
	// Poll window for Events
	while (SDL_PollEvent(&m_windowEvent))
	{
		bool bool_exit = false;

		// Handle Quit Event(s)
		if (m_windowEvent.type == SDL_QUIT) bool_exit = true;
		if (m_windowEvent.type == SDL_KEYUP)
		{
			if (m_windowEvent.key.keysym.sym == SDLK_ESCAPE) bool_exit = true;
		}

		if (m_windowEvent.type == SDL_KEYDOWN)
		{
			if (m_windowEvent.key.keysym.sym == SDLK_a)
			{
				update.pushEvent(new Event("HandleAKey"));
			}
			if (m_windowEvent.key.keysym.sym == SDLK_d)
			{
				update.pushEvent(new Event("HandleDKey"));
			}
			if (m_windowEvent.key.keysym.sym == SDLK_w)
			{
				update.pushEvent(new Event("HandleWKey"));
			}
			if (m_windowEvent.key.keysym.sym == SDLK_s)
			{
				update.pushEvent(new Event("HandleSKey"));
			}
			if (m_windowEvent.key.keysym.sym == SDLK_LSHIFT)
			{
				update.pushEvent(new Event("HandleLeftShiftKey"));
			}
			if (m_windowEvent.key.keysym.sym == SDLK_LCTRL)
			{
				update.pushEvent(new Event("HandleLeftControlKey"));
			}

		}

		//TODO: Handle Other Window Events


		if (bool_exit) {
			ExitCode = NORMAL_EXIT;
		}
	}

	m_openGL.update(update);

	SDL_GL_SwapWindow(m_window);
}

void Context::draw()
{
	m_openGL.draw();
}

void Context::cleanUp()
{
	//Clean OpenGL
	m_openGL.cleanUp();

	//Clean Context
	SDL_GL_DeleteContext(m_context);

	// Close SDL Window
	SDL_Quit();
}

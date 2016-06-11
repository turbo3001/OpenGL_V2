#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_Window* window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

	SDL_GLContext context = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	glewInit();

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	
	printf("%u\n", vertexBuffer);

	SDL_Event windowEvent;

	while (true) 
	{
		if (SDL_PollEvent(&windowEvent))
		{
			bool exit = false;

			if (windowEvent.type == SDL_QUIT) exit = true;
			
			if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE) exit = true;

			if (exit) {
				break;
			}
		}

		SDL_GL_SwapWindow(window);

	}

	SDL_GL_DeleteContext(context);

	SDL_Quit();

	return 0;
}
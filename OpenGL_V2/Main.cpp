#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL.h>
#include <stdio.h>
#include <chrono>

#include "ShaderReader.hpp"

const int VERTEX_SHADER_COMPILE_ERROR = 1;
const int FRAGMENT_SHADER_COMPILE_ERROR = 2;

int main(int argc, char *argv[])
{

	auto t_start = std::chrono::high_resolution_clock::now();

	int ExitCode = 0;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_Window* window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

	SDL_GLContext context = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	glewInit();

	SDL_Event windowEvent;

	std::string vertexSourceStr = readShader("vertexShader.glsl");
	const char *vertexSource = vertexSourceStr.c_str();

	GLuint ref_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(ref_vertexShader, 1, &vertexSource, NULL);

	glCompileShader(ref_vertexShader);

	GLint shaderCompileStatus;
	glGetShaderiv(ref_vertexShader, GL_COMPILE_STATUS, &shaderCompileStatus);

	if (shaderCompileStatus != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(ref_vertexShader, 512, NULL, buffer);
		printf("An Error occurred when compiling vertex shader: %s", buffer);
		ExitCode = VERTEX_SHADER_COMPILE_ERROR;
	}

	std::string fragmentSourceStr = readShader("fragmentShader.glsl");
	const char *fragmentSource = fragmentSourceStr.c_str();

	GLuint ref_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(ref_fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(ref_fragmentShader);

	glGetShaderiv(ref_fragmentShader, GL_COMPILE_STATUS, &shaderCompileStatus);

	if (shaderCompileStatus != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(ref_fragmentShader, 512, NULL, buffer);
		printf("An Error occurred when compiling fragment shader: %s", buffer);
		ExitCode = FRAGMENT_SHADER_COMPILE_ERROR;
	}

	GLuint ref_shaderProgram = glCreateProgram();
	glAttachShader(ref_shaderProgram, ref_vertexShader);
	glAttachShader(ref_shaderProgram, ref_fragmentShader);

	glBindFragDataLocation(ref_shaderProgram, 0, "outColour");

	glLinkProgram(ref_shaderProgram);

	glUseProgram(ref_shaderProgram);

	GLuint ref_vertexArrayObject;
	glGenVertexArrays(1, &ref_vertexArrayObject);

	glBindVertexArray(ref_vertexArrayObject);

	while (ExitCode == 0) 
	{
		auto t_frame = std::chrono::high_resolution_clock::now();
		float deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(t_frame - t_start).count();

		if (SDL_PollEvent(&windowEvent))
		{
			bool exit = false;

			if (windowEvent.type == SDL_QUIT) exit = true;
			
			if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE) exit = true;

			//TODO: Handle Other Window Events

			if (exit) {
				break;
			}
		}

		//TODO: Draw Code

		float vertices[] = {
			0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,		// Vertex 1 (X, Y, Z) : Red
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,	// Vretex 2 (X, Y, Z) : Green
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	// Vertex 3 (X, Y, Z) : Blue
		};

		GLuint ref_vertexBufferObject;
		glGenBuffers(1, &ref_vertexBufferObject);
		
		glBindBuffer(GL_ARRAY_BUFFER, ref_vertexBufferObject);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		GLint posAttrib = glGetAttribLocation(ref_shaderProgram, "position");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,
								6*sizeof(float), 0);

		GLint colAttrib = glGetAttribLocation(ref_shaderProgram, "colour");
		glEnableVertexAttribArray(colAttrib);
		glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
								6 * sizeof(float), (void*)(3 * sizeof(float)));

		glDrawArrays(GL_TRIANGLES, 0, 3);

		GLint uniColour = glGetUniformLocation(ref_shaderProgram, "triangleColour");
		glUniform3f(uniColour, (sin(deltaTime * 4.0f) + 1.0f) / 2.0f, (sin(deltaTime * 2.0f) + 1.0f) / 2.0f, (sin(deltaTime * 8.0f) + 1.0f) / 2.0f);

		SDL_GL_SwapWindow(window);

	}

	SDL_GL_DeleteContext(context);

	SDL_Quit();

	return ExitCode;
}
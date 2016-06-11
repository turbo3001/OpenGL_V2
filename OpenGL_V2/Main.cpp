#define GLEW_STATIC
#include <GL/glew.h>
#include <SOIL.h>
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
		//	Position				Colour				Texture Co-ords
			-0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// Top-left
			0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,		// Top-right
			0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,		// Bottom-right
			-0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f		// Bottom-left
		};

		GLuint elements[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLuint ref_vertexBufferObject;
		glGenBuffers(1, &ref_vertexBufferObject);
		
		glBindBuffer(GL_ARRAY_BUFFER, ref_vertexBufferObject);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		GLuint ref_elementBufferObject;
		glGenBuffers(1, &ref_elementBufferObject);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ref_elementBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			sizeof(elements), elements, GL_STATIC_DRAW);

		GLuint ref_texture;
		glGenTextures(1, &ref_texture);

		glBindTexture(GL_TEXTURE_2D, ref_texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height;
		unsigned char* image =
			SOIL_load_image("sample.png", &width, &height, 0, SOIL_LOAD_RGB);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

		glGenerateMipmap(GL_TEXTURE_2D);

		GLint posAttrib = glGetAttribLocation(ref_shaderProgram, "position");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,
								8*sizeof(float), 0);

		GLint colAttrib = glGetAttribLocation(ref_shaderProgram, "colour");
		glEnableVertexAttribArray(colAttrib);
		glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
								8 * sizeof(float), (void*)(3 * sizeof(float)));

		GLint texAttrib = glGetAttribLocation(ref_shaderProgram, "texcoord");
		glEnableVertexAttribArray(texAttrib);
		glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
								8 * sizeof(float), (void*)(6 * sizeof(float)));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		SDL_GL_SwapWindow(window);

	}

	SDL_GL_DeleteContext(context);

	SDL_Quit();

	return ExitCode;
}
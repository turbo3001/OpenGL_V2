/**INCLUDES**/

// External Includes
// GLEW (Used to for dynamically linking functions in OpenGL for use on different graphics cards/drivers)
#define GLEW_STATIC //Needs to be defined for GLEW
#include <GL/glew.h>
// Simple OpenGL Image Library (Used to load textures to an array)
#include <SOIL.h>
// SDL (Used for Window and Context)
#include <SDL.h>
// Standard Input and Output (Used to write to Console)
#include <stdio.h>
// Chrono (Used for time related purposes)
#include <chrono>
//GLM (Used for OpenGL Matrix Maths)
#include "lib\GLM\glm\glm.hpp"
#include "lib\GLM\glm\gtc\matrix_transform.hpp"
#include "lib\GLM\glm\gtc\type_ptr.hpp"

//Internal Includes
#include "ShaderReader.hpp"

/**CONSTANTS**/
// Error Constants
const int MAIN_RETURN = -1; // The code should never return from main dirctly if it does something has gone a little wrong!
const int NORMAL_EXIT = 0; // Regular Exit from the Program
const int VERTEX_SHADER_COMPILE_ERROR = 1; // Vertex Shader has compiled incorrectly.
const int FRAGMENT_SHADER_COMPILE_ERROR = 2; // Fragment Shader has compiled incorrectly.

const int fadeTime = 2000; // The time in which to change the images (in milliseconds)
const float rotationPerSecond = 10.0f; // The rotation per Second in degrees

/**VARIABLES**/
float rotation = 0.0f;

/**FUNCTIONS**/
void exitProgram(int exitCode) {
	//TODO: Clean Up used contexts etc.
	exit(exitCode);
}

int main(int argc, char *argv[])
{

	// Get program start time (used for deltaTime Calculations)
	auto t_start = std::chrono::high_resolution_clock::now();

	// Set Up Exit Code (Used for debugging)
	int ExitCode = NORMAL_EXIT;	//See Constants for possible Errors.

	// Inialise SDL Window and Context
	SDL_Init(SDL_INIT_VIDEO); //Initialise SDL

	// Tell SDL we want a OpenGL context.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	// Create the window
	SDL_Window* window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

	// Create the context
	SDL_GLContext context = SDL_GL_CreateContext(window);
	
	// Create SDL_Event object, this will listen for window events later.
	SDL_Event windowEvent;

	// Initialise GLEW (NOTE: This has to be done after Window and Context created!) 
	glewExperimental = GL_TRUE;
	glewInit();

	// Initialse Shaders
	// Vertex Shader
	
	// Read Shader from File
	std::string vertexSourceStr = readShader("vertexShader.glsl");	
	const char *vertexSource = vertexSourceStr.c_str(); // openGL requires the source to be on char[] rather than std::String

	GLuint ref_vertexShader = glCreateShader(GL_VERTEX_SHADER); // Get a reference to a Vertex Shader
	
	// Load char[] into and compile shader.
	glShaderSource(ref_vertexShader, 1, &vertexSource, NULL); 
	glCompileShader(ref_vertexShader);

	// Handle any shader compile errors
	GLint shaderCompileStatus;
	glGetShaderiv(ref_vertexShader, GL_COMPILE_STATUS, &shaderCompileStatus);
	if (shaderCompileStatus != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(ref_vertexShader, 512, NULL, buffer);
		printf("An Error occurred when compiling vertex shader: %s", buffer);
		exitProgram(VERTEX_SHADER_COMPILE_ERROR);
	}

	// Fragment/Pixel Shader

	//Reader Shader from File
	std::string fragmentSourceStr = readShader("fragmentShader.glsl");
	const char *fragmentSource = fragmentSourceStr.c_str();

	GLuint ref_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Get a reference to a Fragment Shader

	//Load char[] into and compile shader.
	glShaderSource(ref_fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(ref_fragmentShader);

	// Handle any Shader errors (using previous shaderCompileStatus as if we're here 
	glGetShaderiv(ref_fragmentShader, GL_COMPILE_STATUS, &shaderCompileStatus);
	if (shaderCompileStatus != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(ref_fragmentShader, 512, NULL, buffer);
		printf("An Error occurred when compiling fragment shader: %s", buffer);
		exitProgram(FRAGMENT_SHADER_COMPILE_ERROR);
		
	}

	// Compile Shader Program
	GLuint ref_shaderProgram = glCreateProgram();
	glAttachShader(ref_shaderProgram, ref_vertexShader);
	glAttachShader(ref_shaderProgram, ref_fragmentShader);

	// Let Fragment Shader know where to output
	glBindFragDataLocation(ref_shaderProgram, 0, "outColour");

	// Tell OpenGL which program to use.
	glLinkProgram(ref_shaderProgram);
	glUseProgram(ref_shaderProgram);

	// Create Verticies
	float vertices[] = {
	//	Position				Colour				Texture Co-ords
		-0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// Top-left
		0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,		// Top-right
		0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,		// Bottom-right
		-0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f		// Bottom-left
	};

	// Create Element Array (Index Array)
	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	// Create a reference to the Vertex Array.
	GLuint ref_vertexArrayObject;
	glGenVertexArrays(1, &ref_vertexArrayObject);
	glBindVertexArray(ref_vertexArrayObject);

	// Create a reference to the Vertex Buffer
	GLuint ref_vertexBufferObject;
	glGenBuffers(1, &ref_vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, ref_vertexBufferObject);

	// Push verticies onto Vertex Buffer.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create a reference to the Element Buffer (Index Buffer)
	GLuint ref_elementBufferObject;
	glGenBuffers(1, &ref_elementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ref_elementBufferObject);

	// Push elements onto Element Buffer.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(elements), elements, GL_STATIC_DRAW);

	// Let OpenGL know how our shader should handle the incoming Vertex data.
	// Position
	GLint posAttrib = glGetAttribLocation(ref_shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,
		8 * sizeof(GLfloat), 0);
	// Colour
	GLint colAttrib = glGetAttribLocation(ref_shaderProgram, "colour");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
		8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	// Texture Co-ordinate
	GLint texAttrib = glGetAttribLocation(ref_shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
		8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

	// Initialise Texture(s)
	// Create a Reference to Texture(s)
	GLuint ref_textures[2];
	glGenTextures(2, ref_textures);

	int width, height;
	unsigned char* image;

	// You can have multiple textures loaded into GRAM glActiveTexture switches between them.
	glActiveTexture(GL_TEXTURE0); // Set Texture 0
	glBindTexture(GL_TEXTURE_2D, ref_textures[0]);
		//Load Texture Image
		image = SOIL_load_image("sample.png", &width, &height, 0, SOIL_LOAD_RGB); // Load picture using SOIL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image); // Load into GRAM
		SOIL_free_image_data(image); // Once it's been loaded into GRAM it's no longer needed in RAM
	glUniform1i(glGetUniformLocation(ref_shaderProgram, "texKitten"), 0); // Let OpenGL know which shader variable to set it to.

	// Set Wrapping Options.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set Filtering Options
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	// Set Texture 1
	glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, ref_textures[1]);
		image = SOIL_load_image("sample2.png", &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	glUniform1i(glGetUniformLocation(ref_shaderProgram, "texPuppy"), 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glm::mat4 view = glm::lookAt(
			glm::vec3(1.2f, 1.2f, 1.2f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 1.0f)
		);
	glUniformMatrix4fv(glGetUniformLocation(ref_shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);
	glUniformMatrix4fv(glGetUniformLocation(ref_shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	// Program Loop
	while (ExitCode == 0) 
	{
		// Calculate deltaTime
		auto t_frame = std::chrono::high_resolution_clock::now();
		float time_since_start = std::chrono::duration_cast<std::chrono::duration<float>>(t_frame - t_start).count();

		// Poll window for Events
		if (SDL_PollEvent(&windowEvent))
		{
			bool exit = false;

			// Handle Quit Event(s)
			if (windowEvent.type == SDL_QUIT) exit = true;
			if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE) exit = true;

			//TODO: Handle Other Window Events

			if (exit) {
				break;
			}
		}

		//TODO: Draw Code

		// Clear the screen to cornflower blue
		glClearColor(0.6f, 0.003f, 0.922f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUniform1f(glGetUniformLocation(ref_shaderProgram, "time"), time_since_start);
		glUniform1f(glGetUniformLocation(ref_shaderProgram, "fadeTime"), fadeTime);

		rotation = rotationPerSecond * time_since_start;

		while (rotation >= 360.0f)
		{
			rotation -= 360.0f;
		}

		printf("Rotation: %f\n", rotation);

		glm::mat4 transform;
		transform = glm::rotate(transform,  glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		glUniformMatrix4fv(glGetUniformLocation(ref_shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(transform));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		SDL_GL_SwapWindow(window);

	}
	
	// Delete Texture References
	glDeleteTextures(2, ref_textures);

	//Delete Shader Program
	glDeleteProgram(ref_shaderProgram);
	//Delete Fragment and Vertex Shaders
	glDeleteShader(ref_fragmentShader);
	glDeleteShader(ref_vertexShader);

	// Delete Index and Vertex Buffers
	glDeleteBuffers(1, &ref_elementBufferObject);
	glDeleteBuffers(1, &ref_vertexBufferObject);

	// Delete Vertex Array
	glDeleteVertexArrays(1, &ref_vertexArrayObject);
	
	//Clean Context
	SDL_GL_DeleteContext(context);
	
	// Close SDL Window
	SDL_Quit();

	exitProgram(ExitCode);
	
	return MAIN_RETURN;
}
#include "OpenGL.h"


/**CONSTANTS**/
const int fadeTime = 2000; // The time in which to change the images (in milliseconds)
const float rotationPerSecond = 45.0f; // The rotation per Second in degrees

OpenGL::OpenGL()
{
	m_shaderProgram = GLShaderProgram();
}

OpenGL::~OpenGL()
{
}

void OpenGL::init()
{
	// Initialise GLEW (NOTE: This has to be done after Window and Context created!) 
	glewExperimental = GL_TRUE;
	glewInit();

	// Initialse Shaders
	// Vertex Shader

	m_shaderProgram.init();

	// Create Verticies
	float vertices[] = {
		//	Position				Colour				Texture Co-ords
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f,	1.0f,	0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,	1.0f, 1.0f,	1.0f,	1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,	1.0f, 1.0f,	1.0f,	1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,	1.0f, 1.0f,	1.0f,	1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	0.0f, 0.0f,
		0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		0.5f,  0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
		0.5f,  0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
		-0.5f,  0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,	0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,	1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,		1.0f, 1.0f, 1.0f,	0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,	0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,	0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f,

		-1.0f, -1.0f, -0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		1.0f, -1.0f, -0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		1.0f,  1.0f, -0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		1.0f,  1.0f, -0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		-1.0f,  1.0f, -0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		-1.0f, -1.0f, -0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f
	};

	// Create Element Array (Index Array)
	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	// Create a reference to the Vertex Array.
	glGenVertexArrays(1, &ref_vertexArrayObject);
	glBindVertexArray(ref_vertexArrayObject);

	// Create a reference to the Vertex Buffer
	glGenBuffers(1, &ref_vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, ref_vertexBufferObject);

	// Push verticies onto Vertex Buffer.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create a reference to the Element Buffer (Index Buffer)
	glGenBuffers(1, &ref_elementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ref_elementBufferObject);

	// Push elements onto Element Buffer.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(elements), elements, GL_STATIC_DRAW);

	// Let OpenGL know how our shader should handle the incoming Vertex data.
	// Position
	GLint posAttrib = glGetAttribLocation(m_shaderProgram.getReference(), "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,
		8 * sizeof(GLfloat), 0);
	// Colour
	GLint colAttrib = glGetAttribLocation(m_shaderProgram.getReference(), "colour");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
		8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	// Texture Co-ordinate
	GLint texAttrib = glGetAttribLocation(m_shaderProgram.getReference(), "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
		8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

	// Initialise Texture(s)
	// Create a Reference to Texture(s)
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
	glUniform1i(glGetUniformLocation(m_shaderProgram.getReference(), "texKitten"), 0); // Let OpenGL know which shader variable to set it to.

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
	glUniform1i(glGetUniformLocation(m_shaderProgram.getReference(), "texPuppy"), 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glm::mat4 view = glm::lookAt(
		glm::vec3(2.5f, 2.5f, 2.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
		);
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram.getReference(), "view"), 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram.getReference(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glEnable(GL_DEPTH_TEST);
}

void OpenGL::update(UpdateObject updateObject)
{
	glUniform1f(glGetUniformLocation(m_shaderProgram.getReference(), "time"), updateObject.getTimeSinceStart());
	glUniform1f(glGetUniformLocation(m_shaderProgram.getReference(), "fadeTime"), fadeTime);
	
	scaleAmount = sin(updateObject.getTimeSinceStart() * 5.0f) * 0.25f + 0.75f;
	
	rotation = rotationPerSecond * updateObject.getTimeSinceStart();

	while (rotation >= 360.0f)
	{
		rotation -= 360.0f;
	}
}

void OpenGL::draw()
{
	glClearColor(0.6f, 0.003f, 0.922f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glm::mat4 model;
	model = glm::scale(model, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

	GLuint ref_modelLocation = glGetUniformLocation(m_shaderProgram.getReference(), "model");
	glUniformMatrix4fv(ref_modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	// Draw Cube
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glEnable(GL_STENCIL_TEST);

	// Draw Floor
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilMask(0xFF);
	glDepthMask(GL_FALSE);
	glClear(GL_STENCIL_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 36, 6);


	// Draw Cube Reflection
	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDepthMask(GL_TRUE);

	model = glm::scale(
		glm::translate(model, glm::vec3(0, 0, -1)),
		glm::vec3(1, 1, -1)
		);
	glUniformMatrix4fv(ref_modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	GLuint ref_overrideColour = glGetUniformLocation(m_shaderProgram.getReference(), "overrideColour");
	GLuint ref_reflection = glGetUniformLocation(m_shaderProgram.getReference(), "reflection");

	glUniform1i(ref_reflection, 1);
	glUniform3f(ref_overrideColour, 0.3f, 0.3f, 0.3f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glUniform3f(ref_overrideColour, 1.0f, 1.0f, 1.0f);
	glUniform1i(ref_reflection, 0);

	glDisable(GL_STENCIL_TEST);
}

void OpenGL::cleanUp()
{

	// Delete Texture References
	glDeleteTextures(2, ref_textures);

	m_shaderProgram.cleanUp();

	// Delete Index and Vertex Buffers
	glDeleteBuffers(1, &ref_elementBufferObject);
	glDeleteBuffers(1, &ref_vertexBufferObject);

	// Delete Vertex Array
	glDeleteVertexArrays(1, &ref_vertexArrayObject);
}
#include "TestObject.h"

TestObject::TestObject()
{
}

TestObject::~TestObject()
{
}

void TestObject::init(GLShaderProgram graphics)
{
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
	GLint posAttrib = glGetAttribLocation(graphics.getReference(), "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,
		8 * sizeof(GLfloat), 0);
	// Colour
	GLint colAttrib = glGetAttribLocation(graphics.getReference(), "colour");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
		8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	// Texture Co-ordinate
	GLint texAttrib = glGetAttribLocation(graphics.getReference(), "texcoord");
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
	image = SOIL_load_image(kittenTexture, &width, &height, 0, SOIL_LOAD_RGB); // Load picture using SOIL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image); // Load into GRAM
	SOIL_free_image_data(image); // Once it's been loaded into GRAM it's no longer needed in RAM
	glUniform1i(glGetUniformLocation(graphics.getReference(), "texKitten"), 0); // Let OpenGL know which shader variable to set it to.

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
	image = SOIL_load_image(puppyTexture, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glUniform1i(glGetUniformLocation(graphics.getReference(), "texPuppy"), 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void TestObject::handleInput(SDL_Event inputEvent)
{
}

void TestObject::update(UpdateObject updateObject)
{
	scaleAmount = 1.0f;

	//scaleAmount = sin(updateObject.getTimeSinceStart() * 5.0f) * 0.25f + 0.75f;

	rotation = rotationPerSecond * updateObject.getTimeSinceStart();

	while (rotation >= 360.0f)
	{
		rotation -= 360.0f;
	}
}

void TestObject::draw(GLShaderProgram graphics)
{
	glm::mat4 model;
	model = glm::scale(model, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

	GLuint ref_modelLocation = glGetUniformLocation(graphics.getReference(), "model");
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

	GLuint ref_overrideColour = glGetUniformLocation(graphics.getReference(), "overrideColour");
	GLuint ref_reflection = glGetUniformLocation(graphics.getReference(), "reflection");

	glUniform1i(ref_reflection, 1);
	glUniform3f(ref_overrideColour, 0.3f, 0.3f, 0.3f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glUniform3f(ref_overrideColour, 1.0f, 1.0f, 1.0f);
	glUniform1i(ref_reflection, 0);

	glDisable(GL_STENCIL_TEST);
}

void TestObject::cleanUp()
{
	// Delete Texture References
	glDeleteTextures(2, ref_textures);

	// Delete Index and Vertex Buffers
	glDeleteBuffers(1, &ref_elementBufferObject);
	glDeleteBuffers(1, &ref_vertexBufferObject);

	// Delete Vertex Array
	glDeleteVertexArrays(1, &ref_vertexArrayObject);
}


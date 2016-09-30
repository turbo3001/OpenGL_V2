#pragma once
#include "IGameObject.h"

class TestObject : public IGameObject
{
public:
	TestObject();
	~TestObject();
	
	// Inherited via IGameObject
	virtual void init(GLShaderProgram graphics) override;

	virtual void handleInput(SDL_Event inputEvent) override;

	virtual void update(UpdateObject updateObject) override;

	virtual void draw(GLShaderProgram graphics) override;

	virtual void cleanUp() override;

private:
	// Create Verticies
	float vertices[336] = {
		//	Position				Colour				Texture Co-ords
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f,	1.0f,	0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f,	1.0f,	1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 1.0f,	1.0f,	1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 1.0f,	1.0f,	1.0f, 1.0f,
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
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,	0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,	0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f,

		-1.0f, -1.0f, -0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		1.0f, -1.0f, -0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		1.0f,  1.0f, -0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		1.0f,  1.0f, -0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		-1.0f,  1.0f, -0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		-1.0f, -1.0f, -0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f
	};

	// Create Element Array (Index Array)
	GLuint elements[6] = {
		0, 1, 2,
		2, 3, 0
	};

	char* kittenTexture = "sample.png";
	char* puppyTexture = "sample2.png";

	float rotation;
	float scaleAmount;

	float rotationPerSecond = 45.0f; // The rotation per Second in degrees


	GLuint ref_vertexArrayObject;
	GLuint ref_vertexBufferObject;
	GLuint ref_elementBufferObject;

	GLuint ref_textures[2];

};
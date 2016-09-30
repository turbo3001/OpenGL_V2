#include "OpenGL.h"


/**CONSTANTS**/
const float fadeTime = 2000.0f; // The time in which to change the images (in milliseconds)
const float rotationPerSecond = 45.0f; // The rotation per Second in degrees

const float cameraSpeed = 10.0f;

OpenGLScene::OpenGLScene()
{
	eventWriteTimer = 0.0f;

	m_shaderProgram = GLShaderProgram();
	m_camera = Camera();
}

OpenGLScene::~OpenGLScene()
{
}

void OpenGLScene::init()
{
	// Initialise GLEW (NOTE: This has to be done after Window and Context created!) 
	glewExperimental = GL_TRUE;
	glewInit();

	// Initialse Shaders
	// Vertex Shader

	m_shaderProgram.init();

	// Set up camera
	// View Matrix Variables
	m_camera.setPosition(0.0f, 5.0f, 2.0f);
	m_camera.setLookAt(0.0f, 0.0f, 0.0f);
	m_camera.setUp(0.0f, 0.0f, 1.0f);

	// Perspective Matrix Variables
	m_camera.setFOV(45.0f);
	m_camera.setAspectRatio(800.0f / 600.0f);
	m_camera.setNearPlane(1.0f);
	m_camera.setFarPlane(10.0f);

	testObject.init(m_shaderProgram);

	
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram.getReference(), "view"), 1, GL_FALSE, glm::value_ptr(m_camera.getViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram.getReference(), "projection"), 1, GL_FALSE, glm::value_ptr(m_camera.getProjetcionMatrix()));

	glEnable(GL_DEPTH_TEST);
}

void OpenGLScene::update(UpdateObject updateObject)
{

	glUniform1f(glGetUniformLocation(m_shaderProgram.getReference(), "time"), updateObject.getTimeSinceStart());
	glUniform1f(glGetUniformLocation(m_shaderProgram.getReference(), "fadeTime"), fadeTime);

	glm::vec3 updatedCameraPosition = m_camera.getPosition();
	glm::vec3 updatedCameraUp = m_camera.getUp();

	

	bool writeOutEvent = false;
	
	if (eventWriteTimer >= 1.0f)
	{
		writeOutEvent = true;
		eventWriteTimer = 0.0f;
	}
	else {
		eventWriteTimer += updateObject.getDeltaTime();
	}


	for (auto & currEvent : updateObject.getEvents())
	{

		if (writeOutEvent)
		{
			printf("Event: %s\n", currEvent.getEventType().c_str());
		}

		if (currEvent.getEventType() == "HandleQKey")
		{
			rotateVector(&updatedCameraUp, (updateObject.getDeltaTime() * cameraSpeed) * 9000.0f, Y_AXIS);
		}

		if (currEvent.getEventType() == "HandleQKey")
		{
			rotateVector(&updatedCameraUp, -((updateObject.getDeltaTime() * cameraSpeed) * 9000.0f), Y_AXIS);
		}

		if (currEvent.getEventType() == "HandleAKey")
		{
			updatedCameraPosition.x += updateObject.getDeltaTime() * cameraSpeed;
			m_camera.moveLookAt(updateObject.getDeltaTime() * cameraSpeed, 0.0f, 0.0f);
		}

		if (currEvent.getEventType() == "HandleDKey")
		{
			updatedCameraPosition.x -= updateObject.getDeltaTime() * cameraSpeed;
			m_camera.moveLookAt(-(updateObject.getDeltaTime() * cameraSpeed), 0.0f, 0.0f);
		}

		if (currEvent.getEventType() == "HandleWKey")
		{
			updatedCameraPosition.y -= updateObject.getDeltaTime() * cameraSpeed;
			m_camera.moveLookAt(0.0f, -(updateObject.getDeltaTime() * cameraSpeed), 0.0f);
		}

		if (currEvent.getEventType() == "HandleSKey")
		{
			updatedCameraPosition.y += updateObject.getDeltaTime() * cameraSpeed;
			m_camera.moveLookAt(0.0f, (updateObject.getDeltaTime() * cameraSpeed), 0.0f);
		}

		if (currEvent.getEventType() == "HandleLeftShiftKey")
		{
			updatedCameraPosition.z += updateObject.getDeltaTime() * cameraSpeed;
			m_camera.moveLookAt(0.0f, 0.0f, updateObject.getDeltaTime() * cameraSpeed);
		}

		if (currEvent.getEventType() == "HandleLeftControlKey")
		{
			updatedCameraPosition.z -= updateObject.getDeltaTime() * cameraSpeed;
			if (updatedCameraPosition.z < 0.0f) updatedCameraPosition.z = 0.0f;
			m_camera.moveLookAt(0.0f, 0.0f, -(updateObject.getDeltaTime() * cameraSpeed));
		}
	}

	printf("Camera Position: %f, %f, %f\n", updatedCameraPosition.x, updatedCameraPosition.y, updatedCameraPosition.z);
	printf("Camera Look At: %f, %f, %f\n", m_camera.getLookAt().x, m_camera.getLookAt().y, m_camera.getLookAt().z);
	printf("Camera Up: %f, %f, %f\n", updatedCameraUp.x, updatedCameraUp.y, updatedCameraUp.z);

	m_camera.setUp(updatedCameraUp);
	m_camera.setPosition(updatedCameraPosition);
	
	float newFOV = (sin(updateObject.getTimeSinceStart() * 0.125) + 1.0f) * 180.0f;

	//m_camera.setFOV(newFOV);

	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram.getReference(), "view"), 1, GL_FALSE, glm::value_ptr(m_camera.getViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram.getReference(), "projection"), 1, GL_FALSE, glm::value_ptr(m_camera.getProjetcionMatrix()));
	
	testObject.update(updateObject);
}

void OpenGLScene::draw()
{
	glClearColor(0.6f, 0.003f, 0.922f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	testObject.draw(m_shaderProgram);
}

void OpenGLScene::cleanUp()
{
	m_shaderProgram.cleanUp();

	testObject.cleanUp();
}

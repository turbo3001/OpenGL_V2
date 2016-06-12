#pragma once
#include "OpenGLDependancies.h"
#include "Maths.h"

class Camera
{
public:
	Camera();
	~Camera();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjetcionMatrix();

	void setPosition(float x, float y, float z);
	void setPosition(glm::vec3 position);

	void movePosition(float x, float y, float z);
	void movePosition(glm::vec3 moveVector);

	void setLookAt(float x, float y, float z);
	void setLookAt(glm::vec3 lookAt);

	void moveLookAt(float x, float y, float z);
	void moveLookAt(glm::vec3 moveVector);

	void setUp(float x, float y, float z);
	void setUp(glm::vec3 up);

	void moveUp(float x, float y, float z);
	void moveUp(glm::vec3 moveVector);

	void setFOV(float fov);
	void setAspectRatio(float aspectRatio);
	void setNearPlane(float nearPlane);
	void setFarPlane(float farPlane);

private:
	glm::vec3 m_position;
	glm::vec3 m_lookAt;
	glm::vec3 m_up;

	float m_fov;
	float m_aspectRatio;
	float m_nearPlane;
	float m_farPlane;
};
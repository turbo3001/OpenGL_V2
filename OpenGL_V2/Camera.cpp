#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(
		m_position,
		m_lookAt,
		m_up
		);
}

glm::mat4 Camera::getProjetcionMatrix()
{
	return glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);;
}

void Camera::setPosition(float x, float y, float z)
{
	glm::vec3 newPosition = glm::vec3(x, y, z);
	setPosition(newPosition);
}

void Camera::setPosition(glm::vec3 position)
{
	this->m_position = position;
}

void Camera::movePosition(float x, float y, float z)
{
	glm::vec3 moveVector = glm::vec3(x, y, z);
	movePosition(moveVector);
}

void Camera::movePosition(glm::vec3 moveVector)
{
	moveVector3(&m_position, moveVector);
}

void Camera::setLookAt(float x, float y, float z)
{
	glm::vec3 newLookAt = glm::vec3(x, y, z);
	setLookAt(newLookAt);
}

void Camera::setLookAt(glm::vec3 lookAt)
{
	this->m_lookAt = lookAt;
}

void Camera::moveLookAt(float x, float y, float z)
{
	glm::vec3 moveVector = glm::vec3(x, y, z);
	moveLookAt(moveVector);
}

void Camera::moveLookAt(glm::vec3 moveVector)
{
	moveVector3(&m_lookAt, moveVector);
}

void Camera::setUp(float x, float y, float z)
{
	glm::vec3 newUp = glm::vec3(x, y, z);
	setUp(newUp);
}

void Camera::setUp(glm::vec3 up)
{
	this->m_up = up;
}

void Camera::moveUp(float x, float y, float z)
{
	glm::vec3 moveVector = glm::vec3(x, y, z);
	moveUp(moveVector);
}

void Camera::moveUp(glm::vec3 moveVector)
{
	moveVector3(&m_up, moveVector);
}

void Camera::setFOV(float fov)
{
	this->m_fov = fov;
}

void Camera::setAspectRatio(float aspectRatio)
{
	this->m_aspectRatio = aspectRatio;
}

void Camera::setNearPlane(float nearPlane)
{
	this->m_nearPlane = nearPlane;
}

void Camera::setFarPlane(float farPlane)
{
	this->m_farPlane = farPlane;
}

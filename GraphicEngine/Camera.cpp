#include "stdafx.h"
#include "Camera.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


Camera* Camera::mainCamera = nullptr;

Camera::Camera()
{
	// position
	position = glm::vec3(0, 0, 5);
	direction = glm::vec3(0, 0, 0);
	// Initial Field of View
	initialFoV = 45.0f;

	horizontalAngle = 3.14f;
	verticalAngle = 0;

	speed = 0.0f; // 3 units / second
	mouseSpeed = 0.00f;

	right = glm::vec3(
		sin(this->horizontalAngle - 3.14f / 2.0f),
		0,
		cos(this->horizontalAngle - 3.14f / 2.0f)
	);

	//Dont work for some reason
	up = glm::cross(right, direction);

	if (Camera::mainCamera == nullptr)
	{
		mainCamera = this;
	}

	Projection = glm::perspective(glm::radians(initialFoV), 4.0f / 3.0f, 0.1f, 100.0f);
	//Projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
	updateView();
	// Our ModelViewProjection : multiplication of our 3 matrices
	VP = Projection * View; // Remember, matrix multiplication is the other way around

}

void Camera::addHorAndVer(float horizontalAngle, float verticalAngle)
{
	this->verticalAngle += verticalAngle;
	this->horizontalAngle += horizontalAngle;
	direction.x = cos(this->verticalAngle) * sin(this->horizontalAngle);
	direction.y = sin(this->verticalAngle);
	direction.z = cos(this->verticalAngle) * cos(this->horizontalAngle);

	right = glm::vec3(
		sin(this->horizontalAngle - 3.14f / 2.0f),
		0,
		cos(this->horizontalAngle - 3.14f / 2.0f)
	);

	//Dont work for some reason
	up = glm::cross(right, direction);

	updateView();
	
}

glm::mat4 Camera::getViewProject()
{
	return VP;
}

void Camera::setFOV(float FOV)
{

	initialFoV = FOV;
	// Projection matrix : 45Åã Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	Projection = glm::perspective(glm::radians(initialFoV), 4.0f / 3.0f, 0.1f, 100.0f);
	//Projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	// Our ModelViewProjection : multiplication of our 3 matrices
	VP = Projection * View; // Remember, matrix multiplication is the other way around
}

float Camera::getFoV()
{
	return initialFoV;
}

void Camera::setPosition(glm::vec3 position)
{
	this->position = position;
	updateView();
}

void Camera::addPosition(glm::vec3 position)
{
	this->position += position;
	updateView();
}

void Camera::updateView()
{
	// Camera matrix
	View = glm::lookAt(
		this->position, // Camera is at (4,3,3), in World Space
		this->position + direction, // and looks at the origin
		up  // Head is up (set to 0,-1,0 to look upside-down)
	);

	// Our ModelViewProjection : multiplication of our 3 matrices
	VP = Projection * View; // Remember, matrix multiplication is the other way around
}


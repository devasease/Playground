#pragma once
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x2.hpp>

class Camera
{
public:
	Camera();
	~Camera() = default;

	void addHorAndVer(float horizontalAngle, float verticalAngle);

	glm::mat4 getViewProject();
	void setFOV(float FOV);
	float getFoV();
	void setPosition(glm::vec3 position);
	void addPosition(glm::vec3 position);



	float speed;
	float mouseSpeed;






	//Makes it easier to access the main camera
	//But if live texture need to be implement later then update Sprite::render to also have the option to take VP
	static Camera* mainCamera;
private:
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 right;
	glm::vec3 up;
	glm::mat4 Projection, View, VP;
	float initialFoV;
	float verticalAngle, horizontalAngle;

	void updateView();
};


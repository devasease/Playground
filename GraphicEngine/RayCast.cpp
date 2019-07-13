#include "stdafx.h"
#include "RayCast.h"
#include "Camera.h"
#include "window.h"
#include <glm/ext/scalar_constants.inl>

glm::vec3 RayCast::ScreenToWorld(glm::vec2 screenPos, float length)
{
	//SideA = sideC*sin(cornerA) / sin(cornerC)
	float cornerC = Camera::mainCamera->getFoV() / 360.0f*(glm::pi<float>() * 2);
	float cornerB = 90.0f/360.0f*(glm::pi<float>()*2);
	float cornerA = (180.0f - cornerC - cornerB) / 360.0f*(glm::pi<float>() * 2);
	float sideC = plg_gl::window::mainWindow->getWindowSize().x;
	float sideA = sideC * sin(cornerA) / sin(cornerC);



	return glm::vec3{0.0f};
}

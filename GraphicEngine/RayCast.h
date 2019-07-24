#pragma once
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
//https://www.calculator.net/triangle-calculator.html?vc=45&vx=&vy=&va=45&vz=300&vb=90&angleunits=d&x=57&y=17
class RayCast
{
public:
	RayCast() = delete;
	~RayCast() = delete;

	static glm::vec3 ScreenToWorld(glm::vec2 screenPos, float length);
};


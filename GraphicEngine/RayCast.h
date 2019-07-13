#pragma once
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

class RayCast
{
public:
	RayCast() = delete;
	~RayCast() = delete;

	static glm::vec3 ScreenToWorld(glm::vec2 screenPos, float length);
};


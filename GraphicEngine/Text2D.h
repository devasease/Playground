#pragma once
#include <string>
#include "shader.h"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

class Text2D
{
public:
	Text2D(std::string text);
	~Text2D();

	void updateText(std::string text);

	void render();

private:
	std::string text;
	Shader shader_;
	GLuint VAO, VBO;
	GLfloat scale;
	glm::vec3 color;
	glm::vec2 position;
	std::vector<GLfloat[6][4]> charVertices;
};


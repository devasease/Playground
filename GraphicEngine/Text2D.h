#pragma once
#include "../Snake/Apple.h"

class Text2D
{
public:
	Text2D();
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


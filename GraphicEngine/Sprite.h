#pragma once
#include <GL/glew.h>
#include <glm/mat4x2.hpp>

class Sprite
{
public:
	Sprite();
	Sprite(Sprite& sprite) = default;
	Sprite(Sprite&& sprite) =default;

	~Sprite() = default;

	void setPosition(float x, float y, float z);
	void setScale(float x, float y, float z);
	void setRotation(float x, float y, float z);
	glm::vec3 getPosition();
	glm::vec3 getScale();
	glm::vec3 getRotation();

	void render();
	::Sprite& operator=(const Sprite& sprite);


private:
	GLuint VertexArrayID{};
	GLuint programID;
	GLuint MatrixID;
	GLuint Texture;
	GLuint TextureID;
	GLuint uvbuffer{};
	GLuint vertexbuffer{};
	glm::vec3 scale, position, rotation;
	glm::mat4 modelScale, modelPosition, modelRotation;
	//2 tries to create a square plane for the Sprite texture
	const GLfloat g_vertex_buffer_data[18] = {
			-1, 1, 0,
			1, 1, 0,
			-1, -1, 0,
			-1, -1, 0,
			1, -1, 0,
			1, 1, 0
	};

	const GLfloat g_uv_buffer_data[12] = {
		0,1,
		1,1,
		0,0,
		0,0,
		1,0,
		1,1
	};
};


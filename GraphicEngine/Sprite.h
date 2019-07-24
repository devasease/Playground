#pragma once
#include <GL/glew.h>
#include <glm/mat4x2.hpp>
#include <atomic>
#include "shader.h"

class Sprite
{
public:
	Sprite();
	Sprite(Sprite& sprite) = default;
	Sprite(Sprite&& sprite) =default;

	~Sprite() = default;

	void setPosition(float x, float y, float z);
	void addPosition(float x, float y, float z);
	void setScale(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setTexture(GLuint texture);
	glm::vec3 getPosition();
	glm::vec3 getScale();
	glm::vec3 getRotation();

	void render();
	::Sprite& operator=(const Sprite& sprite);


private:
	GLuint VertexArrayID{};
	Shader shader_;
	GLuint MatrixID;
	GLuint Texture;
	GLuint TextureID;
	GLuint uvbuffer{};
	GLuint vertexbuffer{};
	glm::vec3 scale, position, rotation;
	glm::mat4 modelScale, modelPosition, modelRotation;
	//2 tries to create a square plane for the Sprite texture
	//using a half to make it easier to create sprite with the correct pixel size
	//As if it was 1 then the sides would be 2 long with 0.5 they are 1 long
	const GLfloat g_vertex_buffer_data[18] = {
			-0.5f, 0.5f, 0,
			0.5f, 0.5f, 0,
			-0.5f, -0.5f, 0,
			-0.5f, -0.5f, 0,
			0.5f, -0.5f, 0,
			0.5f, 0.5f, 0
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


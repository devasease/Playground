#include "stdafx.h"
#include "Sprite.h"
#include "shader.h"
#include "ImageLoader.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.inl>
#include "Time.h"
#include "Camera.h"


Sprite::Sprite(): modelRotation(), rotation()
{
	scale = { 1.0f,1.0f, 1.0f };
	position = { 0.0f,0.0f, 0.0f };
	modelPosition= glm::translate(glm::mat4(1.0f), position);
	modelScale = glm::scale(glm::mat4(1.0f), scale);
	//rotation = glm::rotate(glm::mat4(1.0f), { 0.0f,0.0f, 0.0f });
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	// Load the texture using any two methods
	//GLuint Texture = loadBMP_custom("uvtemplate.bmp");
	Texture = ResourceLoader::CreateWhite(126,126,126);



	// Get a handle for our "myTextureSampler" uniform
	TextureID = glGetUniformLocation(programID, "myTextureSampler");

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);
}

void Sprite::setPosition(float x, float y, float z)
{

}

void Sprite::setScale(float x, float y, float z)
{
}

void Sprite::setRotation(float x, float y, float z)
{

}

glm::vec3 Sprite::getPosition()
{
	return position;
}

glm::vec3 Sprite::getScale()
{
	return scale;
}

glm::vec3 Sprite::getRotation()
{
	return rotation;
}

void Sprite::render()
{
	// Use our shader
	glUseProgram(programID);
	position.x += Time::deltaTime*0.1;
	glm::mat4 MVP = Camera::mainCamera->getViewProject() * (position*scale);

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	// Use our shader
	glUseProgram(programID);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 3rd attribute buffer : uv
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 6 * 3); // 3 indices starting at 0 -> 1 triangle
}

::Sprite& Sprite::operator=(const Sprite& sprite)
{
	return *this;
}

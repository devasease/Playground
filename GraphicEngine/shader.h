#pragma once
#include <gl/glew.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
	Shader(const char * vertex_file_path, const char * fragment_file_path);
	~Shader() = default;

	void use();
	GLint getProgramID();

private:
	void LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

	GLint programID;
};




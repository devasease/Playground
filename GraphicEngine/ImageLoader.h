#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include <gl/glew.h>
#include <GLFW/glfw3.h>

namespace ResourceLoader {

	GLuint loadBMP_custom(const char * imagepath);

	GLuint loadJPG_custom(const char * imagepath);

	GLuint CreateWhite(int red, int green, int blue);

	

}
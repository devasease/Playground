#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include <gl/glew.h>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <map>
#include <vector>

class ResourceLoader {
public:
	struct Character {
		GLuint     TextureID;  // ID handle of the glyph texture
		glm::ivec2 Size;       // Size of glyph
		glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
		GLuint     Advance;    // Offset to advance to next glyph
	};

	static std::vector<Character*>* Characters;

	static void loadOTF(const char* font_path);
};

#include "stdafx.h"
#include "FontLoader.h"
#include <map>
#include <iostream>
#include <ft2build.h>
#include <freetype/freetype.h>




struct CMAP
{
	unsigned short int version;
	unsigned short int numTables;
	unsigned short int platformID;
	unsigned short int encodingID;
	unsigned int offset;

};
std::vector<ResourceLoader::Character*>* ResourceLoader::Characters = new std::vector<Character*>();

void ResourceLoader::loadOTF(const char* font_path)
{
	/*unsigned char segment[12];

	

	// Open the file
	FILE * file = fopen(font_path, "rb");
	if (!file)
	{
		printf("font could not be opened\n");
		return 0;
	}

	//Read 54 bytes to the header variable
	if (fread(segment, 1, 12, file) != 12) { // If not 54 bytes read : problem
		printf("Not a correct otf file\n");
		return false;
	}

	unsigned int sfntVersion = *(unsigned int*)&(segment[0x00]);
	//0x4F54544F == "OTTO
	if (sfntVersion != 0x4F54544F)
	{
		printf("Not correct sfnt version\n");
		return false;
	}
	unsigned short int numTables = *(unsigned short int*)&(segment[0x04]);
	unsigned short int searchRange = *(unsigned short int*)&(segment[0x06]);
	unsigned short int entrySelector = *(unsigned short int*)&(segment[0x08]);
	unsigned short int rangeShift = *(unsigned short int*)&(segment[0x0A]);

	CMAP cmap{};
	fread(segment, 4, 32, file);
	switch (*(unsigned int*)&(segment[0x00]))
	{
		//0x43464620 == cmap
		case 0x636D6170:
			cmap.version = *(unsigned short int*)&(segment[0x04]);
			cmap.numTables = *(unsigned short int*)&(segment[0x06]);
			cmap.platformID = *(unsigned short int*)&(segment[0x08]);
			cmap.encodingID = *(unsigned short int*)&(segment[0x0A]);
			cmap.offset = *(unsigned int*)&(segment[0x0C]);
			break;
	}*/

	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return;
	}
		

	FT_Face face;
	if (FT_New_Face(ft, font_path, 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return;
	}
		

	FT_Set_Pixel_Sizes(face, 0, 42);

	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
	{
		std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
		return;
	}

	/*glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	unsigned char * data = new unsigned char[2048*2048];

	for (GLubyte c = 30; c < 60; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		if(face->glyph->bitmap.buffer == NULL)
		{
			continue;
		}
		data[c*(128 * 128)] = *face->glyph->bitmap.buffer;

	}

	// Generate texture
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RED,
		2048,
		2048,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		data
	);
	// Set texture options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character* character = new Character{
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(GLuint)face->glyph->advance.x
		};
		Characters->push_back(character);
		
	}
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	
}


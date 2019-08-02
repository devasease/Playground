// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <glm/vec2.hpp>
#include "../GraphicEngine/window.h"
#include "../GraphicEngine/FontLoader.h"
#include "SnakeObject.h"

int main()
{
	
	const int width = 800, height = 600;
	std::cout << "Setuping Snake game";
	plg_gl::window window{ glm::vec2{width, height} };
	ResourceLoader::loadOTF("Salmon White - Personal Use.otf");
	window.setup_keys(std::vector<int>{GLFW_KEY_ESCAPE, GLFW_KEY_A, GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_D});
	SnakeObject snake {&window};
	//Apple apple{ };
	Text2D text2{ "Testing" };
	window.addText(&text2);
	/*Sprite sprite1 = Sprite();
	window.addSprite(&sprite1);*/
	//sprite1.setTexture(ResourceLoader::Characters->at('c')->TextureID);

	do {
		
		window.update();
		snake.Update();


	} // Check if the ESC key was pressed or the window was closed
	while (window.closeWindow());
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

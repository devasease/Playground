#include "stdafx.h"
#include "window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Time.h"
#include "Text2D.h"
using namespace glm;
#include <iostream>
#include <vector>
#include "Sprite.h"

namespace plg_gl{
	window* window::mainWindow = nullptr;
	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	// One color for each vertex. They were generated randomly.
	//Interpelate the color from the cornors of the trie
	static const GLfloat g_color_buffer_data[] = {
		0.0f,  0.0f,  1.0f,
		1.0f,  0.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  0.0f,  1.0f,
		1.0f,  0.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  0.0f,  1.0f,
		1.0f,  0.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  0.0f,  1.0f,
		1.0f,  0.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  0.0f,  1.0f,
		1.0f,  0.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  0.0f,  1.0f,
		1.0f,  0.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  0.0f,  1.0f,
		1.0f,  0.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  0.0f,  1.0f,
		1.0f,  0.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		1.0f,  0.0f,  0.0f,//
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  0.0f,//
		1.0f,  0.0f,  0.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		1.0f,  0.0f,  0.0f,
		0.0f,  0.0f,  0.0f
	};

	static const GLfloat g_uv_buffer_data[] = {
	0.000059f, 1.0f - 0.000004f,
	0.000103f, 1.0f - 0.336048f,
	0.335973f, 1.0f - 0.335903f,
	1.000023f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.336024f, 1.0f - 0.671877f,
	0.667969f, 1.0f - 0.671889f,
	1.000023f, 1.0f - 0.000013f,
	0.668104f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.000059f, 1.0f - 0.000004f,
	0.335973f, 1.0f - 0.335903f,
	0.336098f, 1.0f - 0.000071f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.336024f, 1.0f - 0.671877f,
	1.000004f, 1.0f - 0.671847f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.668104f, 1.0f - 0.000013f,
	0.335973f, 1.0f - 0.335903f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.668104f, 1.0f - 0.000013f,
	0.336098f, 1.0f - 0.000071f,
	0.000103f, 1.0f - 0.336048f,
	0.000004f, 1.0f - 0.671870f,
	0.336024f, 1.0f - 0.671877f,
	0.000103f, 1.0f - 0.336048f,
	0.336024f, 1.0f - 0.671877f,
	0.335973f, 1.0f - 0.335903f,
	0.667969f, 1.0f - 0.671889f,
	1.000004f, 1.0f - 0.671847f,
	0.667979f, 1.0f - 0.335851f
	};

	window::window(glm::vec2 reselution) 
	{
		
		// Initialise GLFW
		if (!glfwInit())
		{
			fprintf(stderr, "Failed to initialize GLFW\n");
			getchar();
			return ;
		}
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
#endif
		


		// Open a window and create its OpenGL context
		if (window::mainWindow == nullptr)
		{
			window::mainWindow = this;
		}
		
		window_ = glfwCreateWindow(800, 600, "Tutorial 02 - Red triangle", NULL, NULL);

		if (window_ == NULL) {
			fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
			getchar();
			glfwTerminate();
			return ;
		}
		glfwMakeContextCurrent(window_);

		//Config global opengl state
		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Initialize GLEW
		glewExperimental = true; // Needed for core profile
		if (glewInit() != GLEW_OK) {
			fprintf(stderr, "Failed to initialize GLEW\n");
			getchar();
			glfwTerminate();
			return ;
		}
		glClearColor(0.3f, 0, 0.4f, 0);
		// Ensure we can capture the escape key being pressed below
		glfwSetInputMode(window_, GLFW_STICKY_KEYS, GL_TRUE);


		mouse_pos_ = mouse_pos();
		camera_ = Camera();
		glfwSetCursorPos(window_, reselution.x / 2, reselution.y / 2);
	}


	window::~window()
	{
	}

	void window::update()
	{
		process_input();
		Time::updateTime();

#pragma region  camera code
		// Reset mouse position for next frame
		//glfwSetCursorPos(window_, 800 / 2, 600 / 2);

		camera_.addHorAndVer(
			camera_.mouseSpeed * Time::deltaTime * float(800 / 2 - mouse_pos_.xpos),
			camera_.mouseSpeed * Time::deltaTime * float(600 / 2 - mouse_pos_.ypos)
		);


		/*// Move forward
		if (glfwGetKey(window_, GLFW_KEY_UP) == GLFW_PRESS) {
			camera_.addPosition(camera_.direction * Time::deltaTime * camera_.speed);
		}
		// Move backward
		if (glfwGetKey(window_, GLFW_KEY_DOWN) == GLFW_PRESS) {
			camera_.addPosition(camera_.direction * Time::deltaTime * camera_.speed);
		}
		// Strafe right
		if (glfwGetKey(window_, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			camera_.addPosition(camera_.right * Time::deltaTime * camera_.speed);
		}
		// Strafe left
		if (glfwGetKey(window_, GLFW_KEY_LEFT) == GLFW_PRESS) {
			camera_.addPosition(camera_.right * Time::deltaTime * camera_.speed);
		}*/

#pragma endregion
		
		
		

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//
		//text2.render("testing", 40, 40, 40.0f, { 250,0,250 });

		for (Sprite* sprite : gameobject)
		{
			sprite->render();
		}

		

		glDisableVertexAttribArray(0);

		

		// Swap buffers
		glfwSwapBuffers(window_);
		glfwPollEvents();
	}

	bool window::closeWindow()
	{
		return glfwWindowShouldClose(window_) == 0;
	}

#pragma region input

	void window::process_key_input(const int key)
	{
		if (glfwGetKey(window_, key) == GLFW_PRESS)
		{
			if (key_statuses_->at(key) == KeyStatus::unpressed || key_statuses_->at(key) == KeyStatus::lifted)
			{
				key_statuses_->at(key) = KeyStatus::pressed;
			}
			else
			{
				key_statuses_->at(key) = KeyStatus::hold;
			}
		}
		else if (key_statuses_->at(key) == KeyStatus::hold || key_statuses_->at(key) == KeyStatus::pressed)
		{
			key_statuses_->at(key) = KeyStatus::lifted;
		}
		else
		{
			key_statuses_->at(key) = KeyStatus::unpressed;
		}
	}

	void window::setup_keys(const std::vector<int>& enabled_keys)
	{
		key_statuses_ = new std::map<int, KeyStatus>();
		for (auto keycode : enabled_keys) {
			key_statuses_->emplace(std::pair<int, KeyStatus>(keycode, KeyStatus::unpressed));
		}
	}

	void window::addSprite(Sprite* sprite)
	{
		gameobject.push_back(sprite);
	}

	KeyStatus window::get_input_state(const int key)
	{
		return key_statuses_->at(key);
	}

	bool window::get_key_pressed(const int key)
	{
		return get_input_state(key) == KeyStatus::pressed;
	}

	bool window::get_key_hold(const int key)
	{
		return get_input_state(key) == KeyStatus::pressed || get_input_state(key) == KeyStatus::hold;
	}

	bool window::get_key_lift(const int key)
	{
		return get_input_state(key) == KeyStatus::lifted;
	}

	glm::vec2 window::getWindowSize() const
	{
		int width, height;
		glfwGetWindowSize(window_, &width, &height);
		return glm::vec2{ width,height };
	}


	void window::process_input()
	{
		glfwGetCursorPos(window_, &mouse_pos_.xpos, &mouse_pos_.ypos);
		if (key_statuses_ != NULL)
		{
			for (auto key : *key_statuses_)
			{
				process_key_input(key.first);
			}
		}
		
	}



#pragma endregion

}

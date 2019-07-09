#include "stdafx.h"
#include "window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#include <iostream>
#include <vector>
#include "shader.h"

namespace plg_gl{
	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

	window::window()
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
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Open a window and create its OpenGL context
		window_ = glfwCreateWindow(800, 600, "Tutorial 02 - Red triangle", NULL, NULL);
		if (window_ == NULL) {
			fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
			getchar();
			glfwTerminate();
			return ;
		}
		glfwMakeContextCurrent(window_);

		// Initialize GLEW
		glewExperimental = true; // Needed for core profile
		if (glewInit() != GLEW_OK) {
			fprintf(stderr, "Failed to initialize GLEW\n");
			getchar();
			glfwTerminate();
			return ;
		}

		// Ensure we can capture the escape key being pressed below
		glfwSetInputMode(window_, GLFW_STICKY_KEYS, GL_TRUE);
	
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		// Create and compile our GLSL program from the shaders
		programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
		
		


		// Get a handle for our "MVP" uniform
		MatrixID = glGetUniformLocation(programID, "MVP");

		// Projection matrix : 45Åã Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		Projection = glm::perspective(glm::radians(90.0f), 4.0f / 3.0f, 0.1f, 100.0f);
		// Or, for an ortho camera :
		//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

		// Camera matrix
		View = glm::lookAt(
			glm::vec3(0, 0, 3), // Camera is at (4,3,3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
		// Model matrix : an identity matrix (model will be at the origin)
		Model = glm::mat4(1.0f);
		// Our ModelViewProjection : multiplication of our 3 matrices
		MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	}


	window::~window()
	{
	}

	void window::update()
	{
		process_input();
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

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

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

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


	void window::process_input()
	{
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

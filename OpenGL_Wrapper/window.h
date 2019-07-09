#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <vector>
#include "KeyStatus.h"
#include <glm/glm.hpp>

namespace plg_gl {
	class window
	{
	public:
		window();
		~window();

		void update();

		bool closeWindow();

		void setup_keys(const std::vector<int>& enabled_keys);

		KeyStatus get_input_state(int key);
		bool get_key_pressed(int key);
		bool get_key_hold(int key);
		bool get_key_lift(int key);

		void process_input();
		
	private:
		GLFWwindow* window_;
		std::map<int, KeyStatus>* key_statuses_;

		// identify our vertex buffer
		GLuint vertexbuffer;
		GLuint VertexArrayID;
		GLuint programID;
		GLuint MatrixID;
		glm::mat4 Projection, View, MVP, Model;

		void process_key_input(int key);

	};
}


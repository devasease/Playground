#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <vector>
#include "KeyStatus.h"
#include "Camera.h"
#include "Sprite.h"

namespace plg_gl {
	struct mouse_pos
	{
		mouse_pos()
		{
			xpos = 0;
			ypos = 0;
		}
		double xpos, ypos;
	};

	class window
	{
	public:
		window(glm::vec2 reselution);
		~window();

		void update();

		bool closeWindow();

		void setup_keys(const std::vector<int>& enabled_keys);

		KeyStatus get_input_state(int key);
		bool get_key_pressed(int key);
		bool get_key_hold(int key);
		bool get_key_lift(int key);
		glm::vec2 getWindowSize() const;
		void process_input();

		static window* mainWindow;
	private:
		GLFWwindow* window_;
		std::map<int, KeyStatus>* key_statuses_;
		mouse_pos mouse_pos_;

		Camera camera_;

		// identify our vertex buffer
		GLuint vertexbuffer;
		GLuint VertexArrayID;
		GLuint programID;
		GLuint MatrixID;
		GLuint colorbuffer;
		GLuint uvbuffer;
		GLuint Texture;
		GLuint TextureID;

		std::vector<Sprite*> gameobject;

		void process_key_input(int key);

	};
}


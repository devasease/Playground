#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <vector>
#include "KeyStatus.h"
#include "Camera.h"
#include "Sprite.h"
#include "../CommonLib/Event.h"
#include "Text2D.h"

//Help since tutorial is not up to date
//https://www.glfw.org/docs/3.0/moving.html
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
		void addSprite(Sprite*);
		void addText(Text2D*);
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

		//Grapich2D::Text2D text2;
		
		Event<GLFWwindow*, int, int> window_resize_event_;
		std::vector<Sprite*> gameobject;
		std::vector<Text2D*> textElements;

		void process_key_input(int key);
	};
}


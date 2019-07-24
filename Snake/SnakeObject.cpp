#include "pch.h"
#include "SnakeObject.h"
#include "../GraphicEngine/Time.h"
#include "../GraphicEngine/window.h"
#include "../GraphicEngine/ImageLoader.h"


SnakeObject::SnakeObject(plg_gl::window* window)
{
	window_ = window;
	snake_parts.push_back(Sprite());
	head_pointer = 0;
	window_->addSprite(&snake_parts[0]);
	snake_vector[0] = 0;
	snake_vector[1] = 0;
	snake_parts[0].setScale(8.0f / 300.0f, 8.0f / 300.0f, 8.0f / 300.0f);
	snake_parts[0].setTexture(ResourceLoader::CreateSolidTexture(255, 0, 0));
	timer = 0.0f;
	tick_rate = 10;
}


SnakeObject::~SnakeObject()
{
}

void SnakeObject::Update()
{
	timer += Time::deltaTime;
	if (window_->get_key_pressed(GLFW_KEY_A))
	{
		snake_vector[0] = -1 * (window_->getWindowSize().x / 80);
		snake_vector[1] = 0;
	}
	if (window_->get_key_pressed(GLFW_KEY_W))
	{
		snake_vector[0] = 0;
		snake_vector[1] = (window_->getWindowSize().y / 60);
	}
	if (window_->get_key_pressed(GLFW_KEY_S))
	{
		snake_vector[0] = 0;
		snake_vector[1] = -1 * (window_->getWindowSize().y / 60);
	}
	if (window_->get_key_pressed(GLFW_KEY_D))
	{
		snake_vector[0] = (window_->getWindowSize().x / 80);
		snake_vector[1] = 0;
	}
	if (timer > 1.0f / tick_rate)
	{
		timer -= 1.0f / tick_rate;
		snake_parts[0].addPosition(snake_vector[0] / 300.0f, snake_vector[1] / 300.0f, 0.0f);
	}
}

void SnakeObject::CreateSnakePart()
{

}

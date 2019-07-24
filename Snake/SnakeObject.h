#pragma once
#include "../GraphicEngine/window.h"
class SnakeObject
{
public:
	SnakeObject(plg_gl::window*);
	~SnakeObject();
	void Update();

private:
	void CreateSnakePart();

	int snake_vector[2];
	float timer;
	float tick_rate;
	std::vector<Sprite> snake_parts;
	int head_pointer;
	plg_gl::window* window_;
};


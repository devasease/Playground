#pragma once
#include <vector>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "KeyStatus.h"

class Input
{
public:
	Input() = delete;

	Input(const Input&) = delete;
	Input(Input&&) = delete;
	Input& operator=(const Input&) = delete;
	Input& operator=(Input&&) = delete;

	~Input() = delete;

	static void init(const std::vector<int>& enabled_keys);

	KeyStatus get_input_state(int key);
	bool get_key_pressed(int key);
	bool get_key_hold(int key);
	bool get_key_lift(int key);

	void process_input(GLFWwindow* window);
	void process_key_input(int key, GLFWwindow* window);

private:
	std::map<int, KeyStatus> key_statuses_;
};


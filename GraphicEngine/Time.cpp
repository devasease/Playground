#include "stdafx.h"
#include "Time.h"
#include <GLFW/glfw3.h>


float Time::lastFrame = glfwGetTime();
float Time::deltaTime = glfwGetTime();

void Time::updateTime()
{
	//TODO maybe add time mutliplier to changes speed dynamicly



	double currentTime = glfwGetTime();
	Time::deltaTime = float(currentTime - Time::lastFrame);
	Time::lastFrame = currentTime;
}

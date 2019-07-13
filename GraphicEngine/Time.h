#pragma once
class Time
{
public:
	Time() = delete;
	~Time() = delete;

	static void updateTime();

	static float lastFrame;
	static float deltaTime;
};


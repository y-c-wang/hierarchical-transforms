#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "cube.h"
#include "stb_image.h"

enum class Action
{
	Jump,
	Crouch,
	Sprint,
	Hi
};

class Robot
{
	std::map<char, Action> actionByChar = {
		{' ', Action::Jump},
		{'c', Action::Crouch},
		{'w', Action::Sprint},
		{'h', Action::Hi}
	};
	std::map<Action, int> actions = {
		{Action::Sprint, -1},
		{Action::Crouch, -1},
		{Action::Jump, -1},
		{Action::Hi, -1}
	};

	void rotate(std::string component, float degree_x, float degree_y, float degree_z);
	void translate(glm::vec3 vec);

public:
	const std::string componentNames[10] = {
		"head", "body", "arm_li", "arm_lo", "arm_ri",
		"arm_ro", "leg_li", "leg_lo", "leg_ri", "leg_ro"
	};
	std::map<std::string, glm::vec3> INIT_SCALES = {
		{ "head", glm::vec3(1.0f, 1.0f, 1.0f) },
		{ "body", glm::vec3(1.6f, 4.0f, 1.0f) },
		{ "arm_li", glm::vec3(0.6f, 2.2f, 0.6f) },
		{ "arm_lo", glm::vec3(0.4f, 1.4f, 0.4f) },
		{ "arm_ri", glm::vec3(0.6f, 2.2f, 0.6f) },
		{ "arm_ro", glm::vec3(0.4f, 1.4f, 0.4f) },
		{ "leg_li", glm::vec3(0.6f, 2.2f, 0.6f) },
		{ "leg_lo", glm::vec3(0.4f, 1.4f, 0.4f) },
		{ "leg_ri", glm::vec3(0.6f, 2.2f, 0.6f) },
		{ "leg_ro", glm::vec3(0.4f, 1.4f, 0.4f) },
	};
	std::map<std::string, glm::vec3> INIT_CENTER_POSITIONS = {
		{ "head", glm::vec3(0.0f, 2.5f, 0.0f) },
		{ "body", glm::vec3(0.0f, 0.0f, 0.0f) },
		{ "arm_li", glm::vec3(-1.1f, 0.9f, 0.0f) },
		{ "arm_lo", glm::vec3(-1.1f, -0.7f, 0.0f) },
		{ "arm_ri", glm::vec3(1.1f, 0.9f, 0.0f) },
		{ "arm_ro", glm::vec3(1.1f, -0.7f, 0.0f) },
		{ "leg_li", glm::vec3(-0.5f, -3.1f, 0.0f) },
		{ "leg_lo", glm::vec3(-0.5f, -4.7f, 0.0f) },
		{ "leg_ri", glm::vec3(0.5f, -3.1f, 0.0f) },
		{ "leg_ro", glm::vec3(0.5f, -4.7f, 0.0f) },
	};
	std::map<std::string, glm::vec3> INIT_COLORS = {
		{ "head", glm::vec3(0.4f, 0.4f, 0.8f) },
		{ "body", glm::vec3(0.2f, 0.2f, 0.4f) },
		{ "arm_li", glm::vec3(0.3f, 0.3f, 0.6f) },
		{ "arm_lo", glm::vec3(0.4f, 0.4f, 0.8f) },
		{ "arm_ri", glm::vec3(0.3f, 0.3f, 0.6f) },
		{ "arm_ro", glm::vec3(0.4f, 0.4f, 0.8f) },
		{ "leg_li", glm::vec3(0.3f, 0.3f, 0.6f) },
		{ "leg_lo", glm::vec3(0.4f, 0.4f, 0.8f) },
		{ "leg_ri", glm::vec3(0.3f, 0.3f, 0.6f) },
		{ "leg_ro", glm::vec3(0.4f, 0.4f, 0.8f) },
	};
	std::map<std::string, glm::vec3> INIT_DIRECTIONS = {
		{ "head", glm::vec3(0.0f, -1.0f, 0.0f) },
		{ "body", glm::vec3(0.0f, -1.0f, 0.0f) },
		{ "arm_li", glm::vec3(0.0f, -1.0f, 0.0f) },
		{ "arm_lo", glm::vec3(0.0f, -1.0f, 0.0f) },
		{ "arm_ri", glm::vec3(0.0f, -1.0f, 0.0f) },
		{ "arm_ro", glm::vec3(0.0f, -1.0f, 0.0f) },
		{ "leg_li", glm::vec3(0.0f, -1.0f, 0.0f) },
		{ "leg_lo", glm::vec3(0.0f, -1.0f, 0.0f) },
		{ "leg_ri", glm::vec3(0.0f, -1.0f, 0.0f) },
		{ "leg_ro", glm::vec3(0.0f, -1.0f, 0.0f) },
	};
	std::map<std::string, float> INIT_SHAFT_PERCENTS = {
		{ "head", 90.0f },
		{ "body", 0.0f },
		{ "arm_li", 0.0f },
		{ "arm_lo", 0.0f },
		{ "arm_ri", 0.0f },
		{ "arm_ro", 0.0f },
		{ "leg_li", 0.0f },
		{ "leg_lo", 0.0f },
		{ "leg_ri", 0.0f },
		{ "leg_ro", 0.0f },
	};
	std::map<std::string, float> INIT_ROTATE_DEGREES = {
		{ "head", 0.0f },
		{ "body", 0.0f },
		{ "arm_li", 0.0f },
		{ "arm_lo", 0.0f },
		{ "arm_ri", 0.0f },
		{ "arm_ro", 0.0f },
		{ "leg_li", 0.0f },
		{ "leg_lo", 0.0f },
		{ "leg_ri", 0.0f },
		{ "leg_ro", 0.0f },
	};
	
	std::map<std::string, Cube*> components;

	Robot();
	~Robot();

	void exportToCubes(std::vector<Cube*>& vec);

	void setActions(std::vector<char> press);
	void action();

	void jump();
	void crouch();
	void sprint();
	void hi();
};

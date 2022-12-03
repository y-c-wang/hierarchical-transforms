#pragma once
#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "stb_image.h"

const glm::vec3 INIT_SCALES = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 INIT_POSITION = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 INIT_COLOUR = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 INIT_DIRECTION = glm::vec3(0.0f, -1.0f, 0.0f);
const float INIT_SHAFT_PERCENT = 0.0f;
const float INIT_ROTATE_DEGREE = 0.0f;

class Cube
{
	void update();
public:
	unsigned int VAO, VBO;
	glm::vec3 scales;
	glm::vec3 center_position;
	glm::mat4 model;
	glm::vec3 direction;
	float shaft_percent;
	float rotate_degree_x;
	float rotate_degree_y;
	float rotate_degree_z;

	unsigned int* textures;
	bool added_texture;

	Cube(
		glm::vec3 scales = INIT_SCALES,
		glm::vec3 center_position = INIT_POSITION,
		glm::vec3 colour = INIT_COLOUR,
		glm::vec3 direction = INIT_DIRECTION,
		float shaft_percent = INIT_SHAFT_PERCENT,
		float rotate_degree_x = INIT_ROTATE_DEGREE,
		float rotate_degree_y = INIT_ROTATE_DEGREE,
		float rotate_degree_z = INIT_ROTATE_DEGREE
	);
	~Cube();

	void draw();
	void setTexture(const char* filePath);
	void updateDirection();

	void translate(glm::vec3 vector);
	void scale(float scalar);
	void rotate(float degree_x, float degree_y, float degree_z, Cube* moveCube = nullptr);
};
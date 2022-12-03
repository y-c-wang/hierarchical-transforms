#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "cube.h"
#include "robot.h"

const unsigned int SCREEN_WIDTH = 1024;
const unsigned int SCREEN_HEIGHT = 768;

Camera camera(
	glm::vec3(-10.0f, 7.0f, 10.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
	-60.0f,
	-45.0f
);

// refer to official site of glfw: https://www.glfw.org/docs/3.3/window_guide.html
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

std::vector<char> processInput(GLFWwindow* window);
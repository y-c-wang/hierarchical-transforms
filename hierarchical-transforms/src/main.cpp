#include "main.h"

int main() {
	#pragma region init
	#pragma region gl init
	#pragma region glfw init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetCursorPosCallback(window, mouse_callback);
	//glfwSetScrollCallback(window, scroll_callback);
	#pragma endregion
	#pragma region glad init
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	#pragma endregion
	glEnable(GL_DEPTH_TEST);
	#pragma endregion
	#pragma region shader init
	Shader shader("assets/shaders/sprite.vs", "assets/shaders/sprite.fs");
	shader.GLUseProgram();
	#pragma endregion

	Robot* robot = new Robot();
	#pragma endregion
	while (!glfwWindowShouldClose(window)) {
		#pragma region action
		std::vector<char> pressList = processInput(window);
		robot->setActions(pressList);
		robot->action();
		#pragma endregion
		#pragma region setup
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.GLUseProgram();

		glm::mat4 view = camera.GetLookAt();
		shader.setMat4("view", view);

		glm::mat4 project = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		shader.setMat4("projection", project);
		#pragma endregion
		#pragma region draw robot
		std::vector<Cube*> cubes;
		robot->exportToCubes(cubes);
		for (Cube* cube : cubes) {
			shader.setBool("textured", cube->added_texture);
			shader.setMat4("model", cube->model);
			cube->draw();
		}
		#pragma endregion
		#pragma region draw floor
		Cube* cube;
		cube = new Cube(
			glm::vec3(10.0f, 1.0f, 10.0f),
			glm::vec3(0.0f, -5.9f, 0.0f),
			glm::vec3(0.5f, 0.5f, 0.5f)
		);
		shader.setBool("textured", cube->added_texture);
		shader.setMat4("model", cube->model);
		cube->draw();
		delete cube;
		#pragma endregion
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

std::vector<char> processInput(GLFWwindow* window) {
	std::vector<char> ret;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
		return ret;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		ret.push_back(' ');
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		ret.push_back('c');
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		ret.push_back('w');
	}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
		ret.push_back('h');
	}
	return ret;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

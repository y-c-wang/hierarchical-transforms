#include "cube.h"

Cube::Cube(
	glm::vec3 scales,
	glm::vec3 center_position,
	glm::vec3 colour,
	glm::vec3 direction,
	float shaft_percent,
	float rotate_degree_x,
	float rotate_degree_y,
	float rotate_degree_z
)
{
	this->scales = scales;
	this->center_position = center_position;
	this->added_texture = false;
	this->direction = direction;
	this->shaft_percent = shaft_percent;
	this->rotate_degree_x = rotate_degree_x;
	this->rotate_degree_y = rotate_degree_y;
	this->rotate_degree_z = rotate_degree_z;
	this->update();

	glGenVertexArrays(1, &(this->VAO));
	glGenBuffers(1, &(this->VBO));
	glBindVertexArray(VAO);

	float vertex_list[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  colour.x, colour.y, colour.z,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  colour.x, colour.y, colour.z,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  colour.x, colour.y, colour.z,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  colour.x, colour.y, colour.z,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  colour.x, colour.y, colour.z,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  colour.x, colour.y, colour.z,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  colour.x, colour.y, colour.z,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  colour.x, colour.y, colour.z,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  colour.x, colour.y, colour.z,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  colour.x, colour.y, colour.z,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  colour.x, colour.y, colour.z,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  colour.x, colour.y, colour.z,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  colour.x, colour.y, colour.z,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  colour.x, colour.y, colour.z,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  colour.x, colour.y, colour.z,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  colour.x, colour.y, colour.z,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  colour.x, colour.y, colour.z,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  colour.x, colour.y, colour.z,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  colour.x, colour.y, colour.z,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  colour.x, colour.y, colour.z,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  colour.x, colour.y, colour.z,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  colour.x, colour.y, colour.z,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  colour.x, colour.y, colour.z,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  colour.x, colour.y, colour.z,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  colour.x, colour.y, colour.z,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  colour.x, colour.y, colour.z,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  colour.x, colour.y, colour.z,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  colour.x, colour.y, colour.z,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  colour.x, colour.y, colour.z,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  colour.x, colour.y, colour.z,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  colour.x, colour.y, colour.z,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  colour.x, colour.y, colour.z,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  colour.x, colour.y, colour.z,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  colour.x, colour.y, colour.z,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  colour.x, colour.y, colour.z,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  colour.x, colour.y, colour.z
	};
	glBindBuffer(GL_ARRAY_BUFFER, (this->VBO));
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_list), vertex_list, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Cube::~Cube() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Cube::draw() {
	if (this->added_texture) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *(this->textures));
	}
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::setTexture(const char* filePath) {
	int w, h, nrChannels;
	glGenTextures(1, this->textures);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *(this->textures));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filePath, &w, &h, &nrChannels, 0);
	if (!data) {
		std::cerr << "Load texture failed" << std::endl;
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);
	this->added_texture = true;
}

void Cube::updateDirection() {
	glm::mat4 rotationMat(1);
	rotationMat = glm::rotate(rotationMat, glm::radians(this->rotate_degree_x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationMat = glm::rotate(rotationMat, glm::radians(this->rotate_degree_y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMat = glm::rotate(rotationMat, glm::radians(this->rotate_degree_z), glm::vec3(0.0f, 0.0f, 1.0f));
	this->direction = glm::vec3(rotationMat * glm::vec4(INIT_DIRECTION, 1.0));
}

void Cube::translate(glm::vec3 vector) {
	this->center_position += vector;
	update();
}

void Cube::scale(float scalar) {
	this->scales *= scalar;
	update();
}

void Cube::rotate(float degree_x, float degree_y, float degree_z, Cube* moveCube) {
	this->rotate_degree_x += degree_x;
	this->rotate_degree_y += degree_y;
	this->rotate_degree_z += degree_z;
	glm::vec3 shaft_position = this->center_position + (this->shaft_percent - 50) / 100 * this->direction;
	glm::vec3 org_moveCube_border_position = shaft_position + (100 - this->shaft_percent) / 100 * this->direction;
	updateDirection();
	this->center_position = shaft_position + (50 - this->shaft_percent) / 100 * this->direction;
	update();
	if (moveCube) {
		glm::vec3 new_moveCube_border_position = shaft_position + (100 - this->shaft_percent) / 100 * this->direction;
		glm::vec3 moveCube_vector = new_moveCube_border_position - org_moveCube_border_position;
		moveCube->translate(moveCube_vector);
	}
}

void Cube::update() {
	this->model = glm::mat4(1.0f);
	this->model = glm::translate(this->model, this->center_position);
	this->model = glm::rotate(this->model, glm::radians(this->rotate_degree_x), glm::vec3(1.0f, 0.0f, 0.0f));
	this->model = glm::rotate(this->model, glm::radians(this->rotate_degree_y), glm::vec3(0.0f, 1.0f, 0.0f));
	this->model = glm::rotate(this->model, glm::radians(this->rotate_degree_z), glm::vec3(0.0f, 0.0f, 1.0f));
	this->model = glm::scale(this->model, this->scales);
}
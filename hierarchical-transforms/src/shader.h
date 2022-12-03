#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
	void GLCompileShader(GLuint shader);
	void GLLinkProgram();
public:
	GLuint ID;

	Shader(const char* vs_filepath, const char* fs_filepath);
	void GLUseProgram();
	void setBool(const char* varName, bool val);
	void setInt(const char* varName, int val);
	void setFloat(const char* varName, float val);
	void setMat4(const char* varName, glm::mat4 val);
};
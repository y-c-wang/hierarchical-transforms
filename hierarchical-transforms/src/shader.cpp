#include "shader.h"

Shader::Shader(const char* vs_filepath, const char* fs_filepath) {
	std::string vs_code_str;
	std::string fs_code_str;
	std::ifstream vs_file_path;
	std::ifstream fs_file_path;
	vs_file_path.exceptions(
		std::ifstream::failbit | 
		std::ifstream::badbit
	);
	fs_file_path.exceptions(
		std::ifstream::failbit | 
		std::ifstream::badbit
	);
	try	{
		std::stringstream vs_sstream;
		vs_file_path.open(vs_filepath);
		vs_sstream << vs_file_path.rdbuf();
		vs_file_path.close();
		vs_code_str = vs_sstream.str();

		std::stringstream fs_sstream;
		fs_file_path.open(fs_filepath);
		fs_sstream << fs_file_path.rdbuf();
		fs_file_path.close();
		fs_code_str = fs_sstream.str();
	}
	catch (std::ifstream::failure e) {
		std::cerr << "Failed to load shader files" << std::endl;
	}

	GLuint vs;
	const char* vs_code_cstr = vs_code_str.c_str();
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vs_code_cstr, NULL);
	GLCompileShader(vs);

	GLuint fs;
	const char* fs_code_cstr = fs_code_str.c_str();
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fs_code_cstr, NULL);
	GLCompileShader(fs);

	this->ID = glCreateProgram();
	glAttachShader(this->ID, vs);
	glAttachShader(this->ID, fs);
	this->GLLinkProgram();

	glDeleteShader(vs);
	glDeleteShader(fs);
}
void Shader::GLUseProgram() {
	glUseProgram(this->ID);
}
void Shader::setBool(const char* varName, bool val) {
	glUniform1i(
		glGetUniformLocation(ID, varName),
		(int)val
	);
}
void Shader::setInt(const char* varName, int val) {
	glUniform1i(
		glGetUniformLocation(ID, varName),
		val
	);
}
void Shader::setFloat(const char* varName, float val) {
	glUniform1f(
		glGetUniformLocation(ID, varName),
		val
	);
}
void Shader::setMat4(const char* varName, glm::mat4 val) {
	glUniformMatrix4fv(
		glGetUniformLocation(ID, varName),
		1,
		GL_FALSE,
		glm::value_ptr(val)
	);
}
void Shader::GLCompileShader(GLuint shader) {
	int success;
	char logger[1024];
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 1024, NULL, logger);
		std::cerr << "Compile shader failed: " << logger << std::endl;
	}
}
void Shader::GLLinkProgram() {
	GLint success;
	char logger[1024];
	glLinkProgram(this->ID);
	glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->ID, 1024, NULL, logger);
		std::cerr << "Link Shader failed: " << logger << std::endl;
	}
}

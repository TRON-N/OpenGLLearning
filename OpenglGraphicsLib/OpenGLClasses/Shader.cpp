//
// Created by Leonard on 2018/08/29.
//

#include <glad/glad.h>
#include <iostream>
#include <glm/vec4.hpp>
#include "../Includes/Shader.hpp"
#include "../Includes/openGLFunctionCallErrorManagementWrapper.hpp"

Shader::Shader(const std::string &vertexShaderSource, const std::string &fragmentShaderSource) {
	unsigned int vertexShader_id = createShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShader_id = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	this->checkShaderErrors(vertexShader_id, GL_COMPILE_STATUS);
	this->checkShaderErrors(fragmentShader_id, GL_COMPILE_STATUS);

	GL_ERROR_WRAPPER(this->m_shaderId = glCreateProgram());
	GL_ERROR_WRAPPER(glAttachShader(this->m_shaderId, vertexShader_id));
	GL_ERROR_WRAPPER(glAttachShader(this->m_shaderId, fragmentShader_id));
	GL_ERROR_WRAPPER(glLinkProgram(this->m_shaderId));

	this->checkProgramErrors(this->m_shaderId, GL_LINK_STATUS);

	glDeleteShader(vertexShader_id);
	glDeleteShader(fragmentShader_id);
}

Shader::~Shader() {
	std::cout << "Shader Destructor called" << std::endl;
	GL_ERROR_WRAPPER(glDeleteProgram(this->m_shaderId));
}

unsigned int Shader::createShader(unsigned int shaderType, const std::string &sourceString) {
	unsigned int shader_id;
	GL_ERROR_WRAPPER(shader_id = glCreateShader(shaderType));

	const char* shaderSource = sourceString.c_str();
	GL_ERROR_WRAPPER(glShaderSource(shader_id, 1, &shaderSource, nullptr));
	GL_ERROR_WRAPPER(glCompileShader(shader_id));

	return shader_id;
}

void Shader::checkShaderErrors(unsigned int shader_id, unsigned int shaderErrorType) {
	int success;
	GL_ERROR_WRAPPER(glGetShaderiv(shader_id, shaderErrorType, &success));
	if (!success) {
		const int INFO_SIZE = 512;
		char infoLog[INFO_SIZE];
		GL_ERROR_WRAPPER(glGetShaderInfoLog(shader_id, INFO_SIZE, nullptr, infoLog));
		std::cout << infoLog << std::endl;
	}
}

void Shader::checkProgramErrors(unsigned int shaderProgram_id, unsigned int shaderProgramErrorType) {
	int success;
	GL_ERROR_WRAPPER(glGetProgramiv(shaderProgram_id, shaderProgramErrorType, &success));
	if (!success) {
		const int INFO_SIZE = 512;
		char infoLog[INFO_SIZE];
		GL_ERROR_WRAPPER(glGetProgramInfoLog(shaderProgram_id, INFO_SIZE, nullptr, infoLog));
		std::cout << infoLog << std::endl;
	}
}

void Shader::bind() {
	GL_ERROR_WRAPPER(glUseProgram(this->m_shaderId));
}

void Shader::unbind() {
	GL_ERROR_WRAPPER(glUseProgram(0));
}

int Shader::getUniformLocation(const std::string &name) {
	if (this->m_uniformLocationCache.find(name) == this->m_uniformLocationCache.end()) {
		GL_ERROR_WRAPPER(int location = glGetUniformLocation(this->m_shaderId, name.c_str()));
		if (location == -1)
			std::cout << "Warning: uniform " << name << " does not exist!!" << std::endl;
		this->m_uniformLocationCache[name] = location;
	}
	return this->m_uniformLocationCache[name];
}

void Shader::setUniform4f(const std::string &name, glm::vec4 values) {
	GL_ERROR_WRAPPER(glUniform4f(this->getUniformLocation(name), values[0], values[1], values[2], values[3]));
}

void Shader::setUniformMatrix4fv(const std::string &name, const float *data, bool shouldTranspose) {
	GL_ERROR_WRAPPER(glUniformMatrix4fv(this->getUniformLocation(name), 1, shouldTranspose ? GL_TRUE : GL_FALSE, data));
}

void Shader::setUniformInt(const std::string &name, int value) {
	GL_ERROR_WRAPPER(glUniform1i(this->getUniformLocation(name), value));
}

void Shader::setUniform3f(const std::string &name, glm::vec3 values) {
	GL_ERROR_WRAPPER(glUniform3f(this->getUniformLocation(name), values[0], values[1], values[2]));
}

Shader::Shader() {
}

Shader::Shader(const Shader &obj) {
	std::cout << "ERROR: Shader objects cannot be copied" << std::endl;
	*this = obj;
	assert(false);
}

Shader &Shader::operator=(const Shader &obj) {
	std::cout << "ERROR: Shader objects cannot be copied" << std::endl;
	this->m_shaderId = obj.m_shaderId;
	assert(false);
	return *this;
}




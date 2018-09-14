//
// Created by Leonard on 2018/08/29.
//

#include <glad/glad.h>
#include <iostream>
#include "Shader.hpp"
#include "openGLFunctionCallErrorManagementWrapper.hpp"

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

void Shader::setUniform4f(const std::string &name, float f0, float f1, float f2, float f3) {
	GL_ERROR_WRAPPER(glUniform4f(this->getUniformLocation(name), f0, f1, f2, f3));
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

void Shader::setUniformMatrix4fv(const std::string &name, const float *data, bool shouldTranspose) {
	glUniformMatrix4fv(this->getUniformLocation(name), 1, shouldTranspose ? GL_TRUE : GL_FALSE, data);
}

void Shader::setUniformInt(const std::string &name, int value) {
	glUniform1i(this->getUniformLocation(name), value);
}

Shader::Shader() {

}

Shader::Shader(const Shader &obj) {
	std::cout << "ERROR: Shader objects cannot be copied" << std::endl;
	assert(&obj == nullptr);
}

Shader &Shader::operator=(const Shader &obj) {
	std::cout << "ERROR: Shader objects cannot be copied" << std::endl;
	assert(&obj == nullptr);
	return *this;
}



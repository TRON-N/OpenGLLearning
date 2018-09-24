//
// Created by Leonard on 2018/08/29.
//

#ifndef LEARNINGOPENGL_SHADER_HPP
#define LEARNINGOPENGL_SHADER_HPP

#include <string>
#include <unordered_map>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class Shader {
public:
	Shader(const std::string &vertexShaderSource, const std::string &fragShaderSource);
	Shader();
	Shader(const Shader &obj);
	Shader &operator=(const Shader &obj);
	~Shader();

	void bind();
	void unbind();

	void setUniform4f(const std::string &name, glm::vec4 values);
	void setUniformMatrix4fv(const std::string &name, const float *data, bool shouldTranspose = false);
	void setUniformInt(const std::string &name, int value);
	void setUniform3f(const std::string &name, glm::vec3 values);



private:
	unsigned int createShader(unsigned int shaderType, const std::string &sourceString);
	void checkShaderErrors(unsigned int shader_id, unsigned int shaderErrorType);
	void checkProgramErrors(unsigned int shaderProgram_id, unsigned int shaderProgramErrorType);
	int getUniformLocation(const std::string &name);
	std::unordered_map<std::string, int> m_uniformLocationCache;
	unsigned int m_shaderId;
};


#endif //LEARNINGOPENGL_SHADER_HPP

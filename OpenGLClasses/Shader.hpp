//
// Created by Leonard on 2018/08/29.
//

#ifndef LEARNINGOPENGL_SHADER_HPP
#define LEARNINGOPENGL_SHADER_HPP

#include <string>
#include <unordered_map>

class Shader {
public:
	Shader(const std::string &vertexShaderSource, const std::string &fragShaderSource);
	Shader();
	Shader(const Shader &obj);
	Shader &operator=(const Shader &obj);
	~Shader();

	void bind();
	void unbind();

	void setUniform4f(const std::string &name, float f0, float f1, float f2, float f3);
	void setUniformMatrix4fv(const std::string &name, const float *data, bool shouldTranspose = false);
	void setUniformInt(const std::string &name, int value);



private:
	unsigned int createShader(unsigned int shaderType, const std::string &sourceString);
	void checkShaderErrors(unsigned int shader_id, unsigned int shaderErrorType);
	void checkProgramErrors(unsigned int shaderProgram_id, unsigned int shaderProgramErrorType);
	int getUniformLocation(const std::string &name);
	std::unordered_map<std::string, int> m_uniformLocationCache;
	unsigned int m_shaderId;
};


#endif //LEARNINGOPENGL_SHADER_HPP

//
// Created by Leonard VAN GEND on 2018/09/17.
//

#include <glad/glad.h>
#include <SDL_video.h>
#include <iostream>
#include "../Includes/Renderer.hpp"
#include "../Includes/openGLFunctionCallErrorManagementWrapper.hpp"

const char *Renderer::m_vertexShaderSource = "#version 330 core\n"
											 "layout (location = 0) in vec3 aPos;\n"
											 "layout (location = 1) in vec3 aNormal;\n"
											 "layout (location = 2) in vec2 atexCoord;\n"

											 "uniform mat4 model;\n"
											 "uniform mat4 view;\n"
											 "uniform mat4 projection;\n"

											 "out vec2 texCoord;\n"
											 "void main()\n"
											 "{\n"
											 "	gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
											 "	texCoord = atexCoord;\n"
											 "}\0";

const char *Renderer::m_fragmentShaderSource = "#version 330 core\n"
											   "\n"
											   "out vec4 FragColor;\n"
											   "in vec2 texCoord;\n"
											   "\n"
											   "// texture sampler\n"
											   "uniform sampler2D texture_diffuse1;\n"
											   "uniform sampler2D texture2;\n"
											   "\n"
											   "void main()\n"
											   "{\n"
											   "	FragColor = texture(texture_diffuse1, texCoord);\n"
											   "}\0";


Renderer::Renderer(SDL_Window *window) {


	this->m_window = window;
	this->m_glContext = SDL_GL_CreateContext(this->m_window);

	if (!gladLoadGLLoader((SDL_GL_GetProcAddress))) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}
	this->m_shaderProgram = new Shader(m_vertexShaderSource, m_fragmentShaderSource);
	GL_ERROR_WRAPPER(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	GL_ERROR_WRAPPER(glEnable(GL_DEPTH_TEST));
}

void Renderer::update() {
	SDL_GL_SwapWindow(this->m_window);
	GL_ERROR_WRAPPER(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

Renderer::~Renderer() {
	delete m_shaderProgram;
	SDL_GL_DeleteContext(this->m_glContext);
}

Renderer::Renderer() {

}

Renderer::Renderer(const Renderer &obj) {
	std::cout << "ERROR: Renderer objects cannot be copied" << std::endl;
	assert(&obj == nullptr);
}

Renderer &Renderer::operator=(const Renderer &obj) {
	std::cout << "ERROR: Renderer objects cannot be copied" << std::endl;
	assert(&obj == nullptr);
	return *this;
}

void Renderer::notify(void *arg) {
	unsigned int *resolution = (unsigned int *) arg;

	GL_ERROR_WRAPPER(glViewport(0, 0, resolution[0], resolution[1]));
}

Shader &Renderer::getShaderProgram() {
	return *this->m_shaderProgram;
}

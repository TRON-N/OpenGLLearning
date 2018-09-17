//
// Created by Leonard VAN GEND on 2018/09/17.
//

#include <glad/glad.h>
#include <SDL_video.h>
#include <iostream>
#include "Renderer.hpp"
#include "openGLFunctionCallErrorManagementWrapper.hpp"

Renderer::Renderer(SDL_Window *window) {
	this->m_window = window;

	this->m_glContext = SDL_GL_CreateContext(this->m_window);

	if (!gladLoadGLLoader((SDL_GL_GetProcAddress))) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}
	GL_ERROR_WRAPPER(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	GL_ERROR_WRAPPER(glEnable(GL_DEPTH_TEST));
}

void Renderer::update() {
	SDL_GL_SwapWindow(this->m_window);
	GL_ERROR_WRAPPER(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

Renderer::~Renderer() {
	SDL_GL_DeleteContext(this->m_glContext);
}

//
// Created by Leonard VAN GEND on 2018/09/17.
//

#include <SDL.h>
#include <iostream>
#include "Window.hpp"

Window::Window() {

}

Window::Window(const Window &obj) {
	std::cout << "ERROR: Window objects cannot be copied" << std::endl;
	assert(&obj == nullptr);
}

Window &Window::operator=(const Window &obj) {
	std::cout << "ERROR: Window objects cannot be copied" << std::endl;
	assert(&obj == nullptr);
	return *this;
}

Window::~Window() {
	SDL_DestroyWindow(this->m_window);
	SDL_Quit();
}

SDL_Window *Window::getWindowPtr() {
	return this->m_window;
}

std::vector<std::vector<int>> Window::getValidResolutionList() {
	return this->m_validResolutionList;
}

void Window::setResolution(unsigned int i) {
	assert(i < this->m_validResolutionList.size());
	SDL_SetWindowSize(this->m_window, this->m_validResolutionList[i][0], this->m_validResolutionList[i][1]);
}

void Window::toggleFullScreen() {

}

void Window::populateValidResolutionList() {
	for (int i = 0; i < SDL_GetNumDisplayModes(0); i++) {
		SDL_DisplayMode mode;
		SDL_GetDisplayMode(0, i, &mode);
		this->m_validResolutionList.push_back({mode.w, mode.h});
	}
}

Window::Window(bool isFullScreen, unsigned int resolutionSetting) {
	this->m_isFullScreen = isFullScreen;
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	this->populateValidResolutionList();

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	this->m_window = SDL_CreateWindow("SDL GL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_UNDEFINED,
									  this->m_validResolutionList[resolutionSetting][0],
									  this->m_validResolutionList[resolutionSetting][1], SDL_WINDOW_OPENGL);
}

//
// Created by Leonard VAN GEND on 2018/09/17.
//

#include <SDL.h>
#include <iostream>
#include "../Includes/Window.hpp"
#include <cassert>

Window::Window() {

}

Window::Window(const Window &obj) : Observable() {
	std::cout << "ERROR: Window objects cannot be copied" << std::endl;
	*this = obj;
	assert(false);
}

Window &Window::operator=(const Window &obj) {
	std::cout << "ERROR: Window objects cannot be copied" << std::endl;
	this->m_window = obj.m_window;
	assert(false);
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
	this->m_resolutionIndex = i;
	if (this->m_isFullScreen == false)
		SDL_SetWindowSize(this->m_window, this->m_validResolutionList[i][0], this->m_validResolutionList[i][1]);
	else {
		SDL_DisplayMode desiredDisplayMode;
		desiredDisplayMode.w = this->m_validResolutionList[i][0];
		desiredDisplayMode.h = this->m_validResolutionList[i][1];

		SDL_DisplayMode closestMatch;
		SDL_SetWindowDisplayMode(this->m_window, &desiredDisplayMode);
		SDL_GetCurrentDisplayMode(0, &closestMatch);
		SDL_SetWindowSize(this->m_window, this->m_validResolutionList[i][0], this->m_validResolutionList[i][1]);
	}
	this->notifyObservers();
}

void Window::toggleFullScreen() {
	this->m_isFullScreen = !this->m_isFullScreen;
	if (this->m_isFullScreen) {
		SDL_SetWindowFullscreen(this->m_window, SDL_WINDOW_FULLSCREEN);
	}
	else
		SDL_SetWindowFullscreen(this->m_window, 0);
	this->setResolution(this->m_resolutionIndex);
}

void Window::populateValidResolutionList() {
	int previousResolution[] = {0, 0};
	for (int i = 0; i < SDL_GetNumDisplayModes(0); i++) {
		SDL_DisplayMode mode;
		SDL_GetDisplayMode(0, i, &mode);
		if (mode.w != previousResolution[0] || mode.h != previousResolution[1]) {
			this->m_validResolutionList.push_back({mode.w, mode.h});
			previousResolution[0] = mode.w;
			previousResolution[1] = mode.h;
		}
	}
}

Window::Window(bool isFullScreen, unsigned int resolutionSetting) {
	this->m_isFullScreen = isFullScreen;
	this->m_resolutionIndex = resolutionSetting;
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	this->populateValidResolutionList();

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	this->m_window = SDL_CreateWindow("SDL GL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_UNDEFINED,
									  this->m_validResolutionList[resolutionSetting][0],
									  this->m_validResolutionList[resolutionSetting][1], SDL_WINDOW_OPENGL |
																						 SDL_WINDOW_ALLOW_HIGHDPI);
}

void Window::notifyObservers() {
	for (i_Observer *observer: this->m_observerList) {
		observer->notify(this->m_window);
	}
}

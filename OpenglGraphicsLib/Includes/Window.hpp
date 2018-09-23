//
// Created by Leonard VAN GEND on 2018/09/17.
//

#ifndef LEARNINGOPENGL_WINDOW_HPP
#define LEARNINGOPENGL_WINDOW_HPP


#include <SDL_video.h>
#include <vector>
#include "Observable.hpp"

class Window : public Observable {
public:
	Window();

	Window(bool isFullScreen, unsigned int resolutionSetting);
	Window(const Window &obj);
	Window &operator=(const Window &obj);
	~Window();

	SDL_Window *getWindowPtr();
	std::vector<std::vector<int>> getValidResolutionList();
	std::vector<int> getCurrentResolution();
	void setResolution(unsigned int i);
	void toggleFullScreen();

	void notifyObservers() override;

private:
	void populateValidResolutionList();

	SDL_Window *m_window;
	std::vector<std::vector<int>> m_validResolutionList;
	bool m_isFullScreen;
	unsigned int m_resolutionIndex;
};


#endif //LEARNINGOPENGL_WINDOW_HPP

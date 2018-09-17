//
// Created by Leonard VAN GEND on 2018/09/17.
//

#ifndef LEARNINGOPENGL_RENDERER_HPP
#define LEARNINGOPENGL_RENDERER_HPP


#include "ObserverPattern/i_Observer.hpp"

class Renderer : public i_Observer {
public:
	Renderer(SDL_Window *window);

	Renderer();

	Renderer(const Renderer &obj);

	Renderer &operator=(const Renderer &obj);
	~Renderer();

	void update();

	void notify(void *arg) override;

private:
	SDL_Window *m_window;
	SDL_GLContext m_glContext;
};


#endif //LEARNINGOPENGL_RENDERER_HPP
